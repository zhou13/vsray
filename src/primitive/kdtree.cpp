#include "primitive/kdtree.hpp"
#include "shape/meshset.hpp"
#include "shape/mesh.hpp"

VSRAY_NAMESPACE_BEGIN

const real T_SECT = 60;
const real T_TRAV = 1;
const real EMPTY_BONUS = 0.5f;
const int KDTREE_LEAF = 3;

const int MASK2 = 0x3;
const int MASK30 = 0x3FFFFFFF;

const int STACK_SIZE = 30;

KdTree::KdTree(Meshset *meshset): time(0)
{
    for (int i = 0; i < (int)meshset->size(); ++i)
        addPrimitive((*meshset)[i]);
}

void KdTree::initialize()
{
    visited.resize(items.size(), 0);
    vector<BBox> primBBox;
    int maxDepth = (int)ceil(8.f + 1.3f * log2((real)items.size()));
    for (auto p: items) {
        BBox b = p->getBBox();
        box = box.merge(b);
        primBBox.push_back(b);
    }

    vector<uint32_t> prims;
    for (uint32_t i = 0; i < items.size(); ++i)
        prims.push_back(i);

    buildKdTree(prims, primBBox, box, maxDepth);
}

void KdTree::buildKdTree(
        vector<uint32_t> &prims,
        vector<BBox> &primBBox,
        BBox cbox, int depth)
{
    if (prims.size() == 1 || depth == 0) {
        addLeafNode(prims);
        return;
    }

    int dim = cbox.maxExtent();
    for (int attempt = 0; attempt < 3; ++attempt) {
        int dim0 = (dim + 1) % 3;
        int dim1 = (dim + 2) % 3;

        vector<tuple<real, bool, uint32_t>> line;
        for (uint32_t p: prims) {
            real v0 = cbox.v0[dim];
            real v1 = cbox.v1[dim];
            line.push_back(make_tuple(v0, true , p));
            line.push_back(make_tuple(v1, false, p));
        }
        sort(line.begin(), line.end());

        int n0 = 0;
        int n1 = (int)prims.size();
        real invArea = 1.f / cbox.area();

        real bestCost = T_SECT * (real)prims.size();
        real cutPosition = 0.f;
        int cutIndex = -1;

        for (size_t i = 0; i < line.size(); ++i) {
            real v = std::get<0>(line[i]);
            bool b = std::get<1>(line[i]);

            if (!b)
                --n1;

            if (cbox.v0[dim] <= v && v <= cbox.v1[dim]) {
                real x  = cbox.v1[dim0] - cbox.v0[dim0];
                real y  = cbox.v1[dim1] - cbox.v0[dim1];
                real z0 = v - cbox.v0[dim];
                real z1 = cbox.v1[dim] - v;
                real area0 = (x * y + z0 * (x + y));
                real area1 = (x * y + z1 * (x + y));
                real bonus = (n0 == 0 || n1 == 0) ? (1 - EMPTY_BONUS) : 1;
                real cost = T_TRAV + T_SECT * bonus *
                    (area0 * (real)n0 + area1 * (real)n1) * invArea;

                if (cost < bestCost) {
                    bestCost = cost;
                    cutIndex = (int)i;
                    cutPosition = v;
                }
            }

            if (b)
                ++n0;
        }

        vector<uint32_t> prim0;
        vector<uint32_t> prim1;
        if (cutIndex != -1) {
            for (size_t i = 0; i < (size_t)cutIndex; ++i)
                if (!std::get<1>(line[i]))
                    prim0.push_back(std::get<2>(line[i]));
            for (size_t i = cutIndex+1; i < line.size(); ++i)
                if (std::get<1>(line[i]))
                    prim1.push_back(std::get<2>(line[i]));

            KdTreeNode currNode;
            BBox nbox0 = cbox; nbox0.v1[dim] = cutPosition;
            BBox nbox1 = cbox; nbox1.v0[dim] = cutPosition;

            size_t index = tree.size();
            currNode.split = cutPosition;
            currNode.flag = dim & MASK2;
            currNode.child = 0;
            tree.push_back(currNode);

            buildKdTree(prim0, primBBox, nbox0, depth-1);
            if (!prim0.empty() && !prim1.empty())
                tree[index].child = (uint32_t)tree.size() & MASK30;
            buildKdTree(prim1, primBBox, nbox1, depth-1);

            return;
        }
        dim = (dim+1) % 3;
    }

    addLeafNode(prims);
}

void KdTree::addLeafNode(vector<uint32_t> &prims)
{
    KdTreeNode currNode;
    currNode.flag = KDTREE_LEAF;
    currNode.itemID = (uint32_t)primID.size();
    currNode.itemCnt = (uint32_t)prims.size() & MASK30;

    for(uint32_t p: prims)
        primID.push_back(p);

    tree.push_back(currNode);
}

BBox KdTree::getBBox() const
{
    return box;
}

bool KdTree::intersect(const Ray &ray, Intersection *is, real epilson) const
{
    ++time;
    if (time == UINT32_MAX) {
        time = 1;
        fill(visited.begin(), visited.end(), 0u);
    }

    auto node = &tree[0];
    tuple<real, real, decltype(node)> stack[STACK_SIZE];
    int top = 0;

    real minT = 0, maxT = ray.maxT;
    if (is)
        minT = epilson;

    real invD[3] = { 1.f / ray.d.x, 1.f / ray.d.y, 1.f / ray.d.z };
    for (;;) {
        if (minT >  ray.maxT)
            break;
        if (node->flag == KDTREE_LEAF) {
            for (uint32_t i = node->itemID; i < node->itemID + node->itemCnt; ++i) {
                if (visited[primID[i]] == time)
                    continue;
                visited[primID[i]] = time;
                if (items[primID[i]]->intersect(ray, is, epilson))
                    return true;
            }
            if (top == 0)
                break;

            --top;
            minT = std::get<0>(stack[top]);
            maxT = std::get<1>(stack[top]);
            node = std::get<2>(stack[top]);
        } else {
            int dim = node->flag;
            real split = node->split;
            real splitT = (node->split - ray.o[dim]) * invD[dim];
            bool leftFirst = (ray.o[dim] <  split || (ray.o[dim] == split &&
                                                      ray.d[dim] > 0));
            decltype(node) next0, next1;
            if (leftFirst) {
                next0 = node + 1;
                next1 = &tree[node->child];
            } else {
                next0 = &tree[node->child];
                next1 = node + 1;
            }
            if (splitT > maxT || splitT <= 0)
                node = next0;
            else if (splitT < minT)
                node = next1;
            else {
                node = next0;
                stack[top++] = make_tuple(splitT, maxT, next1);
            }
        }
    }
    
    return false;
}

VSRAY_NAMESPACE_END

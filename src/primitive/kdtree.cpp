#include "primitive/kdtree.hpp"
#include "shape/meshset.hpp"
#include "shape/mesh.hpp"

#include <atomic>

VSRAY_NAMESPACE_BEGIN

const real T_SECT = 80;
const real T_TRAV = 1;
const real EMPTY_BONUS = 0.5f;
const int KDTREE_LEAF = 3;

const int MASK2 = 0x3;
const int MASK30 = 0x3FFFFFFF;

const int STACK_SIZE = 30;
const size_t NODE_SIZE = 3;

std::atomic_uint time(0);

KdTree::KdTree() { }

KdTree::KdTree(const Meshset &meshset)
{
    for (int i = 0; i < (int)meshset.size(); ++i) {
        addPrimitive(meshset[i]);
    }
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
    // pobj(box);

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
    if (prims.size() <= NODE_SIZE || depth == 0) {
        addLeafNode(prims);
        return;
    }

    int dim = cbox.maxExtent();
    for (int attempt = 0; attempt < 3; ++attempt) {
        int dim0 = (dim + 1) % 3;
        int dim1 = (dim + 2) % 3;

        vector<tuple<real, bool, uint32_t>> line;
        for (uint32_t p: prims) {
            real v0 = primBBox[p].v0[dim];
            real v1 = primBBox[p].v1[dim];
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

            if (cbox.v0[dim] < v && v < cbox.v1[dim]) {
                real x  = cbox.v1[dim0] - cbox.v0[dim0];
                real y  = cbox.v1[dim1] - cbox.v0[dim1];
                real z0 = v - cbox.v0[dim];
                real z1 = cbox.v1[dim] - v;
                real area0 = 2 * (x * y + z0 * (x + y));
                real area1 = 2 * (x * y + z1 * (x + y));
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
                if (std::get<1>(line[i]))
                    prim0.push_back(std::get<2>(line[i]));
            for (size_t i = cutIndex + 1; i < line.size(); ++i)
                if (!std::get<1>(line[i]))
                    prim1.push_back(std::get<2>(line[i]));

            KdTreeNode currNode;
            BBox nbox0 = cbox; nbox0.v1[dim] = cutPosition;
            BBox nbox1 = cbox; nbox1.v0[dim] = cutPosition;

            size_t index = tree.size();
            currNode.split = cutPosition;
            currNode.flag = dim & MASK2;
            tree.push_back(currNode);

            buildKdTree(prim0, primBBox, nbox0, depth-1);
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

void KdTree::printTree(int index, int indent)
{
    auto node = &tree[index];
    if (node->flag == KDTREE_LEAF) {
        for (uint32_t i = node->itemID; i < node->itemID + node->itemCnt; ++i) {
            for (int k = 0; k < indent; ++k)
                printf(" ");
            printf("| %s\n", ((Mesh *)(items[primID[i]]))->toString().c_str());
        }
        for (int k = 0; k < indent; ++k)
            printf(" ");
        puts("| <LEAF NODE>");
        return;
    }

    for (int k = 0; k < indent; ++k)
        printf(" ");
    if (node->flag == 0)
        printf("split at x: %.3f\n", node->split);
    else if (node->flag == 1)
        printf("split at y: %.3f\n", node->split);
    else if (node->flag == 2)
        printf("split at z: %.3f\n", node->split);
    printTree(index+1, indent + 4);
    printTree(node->child, indent + 4);
}

BBox KdTree::getBBox() const
{
    return box;
}

bool KdTree::intersect(const Ray &ray, Intersection *is, real epilson) const
{
    real minT = is ? epilson : 0;
    real maxT = ray.maxT;

    if (!box.intersect(ray, &minT, &maxT))
        return false;
    // if (is) {
    //     bool found = false;
    //     for (auto p: items)
    //         if (p->intersect(ray, is, epilson))
    //             found = true;
    //     return found;
    // }

    uint32_t localTime = ++time;
    if (localTime == UINT32_MAX) {
        time = 1;
        fill(visited.begin(), visited.end(), 0u);
    }

    auto node = &tree[0];
    tuple<real, real, decltype(node)> stack[STACK_SIZE];
    int top = 0;

    real invD[3] = { 1.f / ray.d.x, 1.f / ray.d.y, 1.f / ray.d.z };
    bool found = false;
    for (;;) {
        if (minT >  ray.maxT)
            break;
        if (node->flag == KDTREE_LEAF) {
            for (uint32_t i = node->itemID; i < node->itemID + node->itemCnt; ++i) {
                if (visited[primID[i]] == localTime)
                    continue;
                visited[primID[i]] = localTime;
                assert(primID[i] < items.size());
                if (items[primID[i]]->intersect(ray, is, epilson))
                    found = true;
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
            bool leftFirst = ((ray.o[dim] <  split) ||
                              (ray.o[dim] == split && ray.d[dim] < 0));
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
                stack[top++] = make_tuple(splitT, maxT, next1);
                node = next0;
                maxT = splitT;
            }
        }
    }

    return found;
}

VSRAY_NAMESPACE_END

#pragma once

#include "primitive/agglomerate.hpp"

VSRAY_NAMESPACE_BEGIN

class KdTreeNode {
public:
    union {
        real split;
        uint32_t itemID;
    };
    struct {
        uint32_t flag: 2;
        union {
            uint32_t child: 30;
            uint32_t itemCnt: 30;
        };
    };
};

class Meshset;

class KdTree : public Agglomerate {
public:
    KdTree(Meshset *meshset);

    void initialize();
    virtual BBox getBBox() const;
    virtual bool intersect(const Ray &ray, Intersection *is, real epilson) const;

private:
    BBox box;
    vector<KdTreeNode> tree;
    vector<uint32_t> primID;

    mutable vector<uint32_t> visited;
    mutable uint32_t time;

    void buildKdTree(
            vector<uint32_t> &prims,
            vector<BBox> &primBBox,
            BBox cbox, int depth);
    void addLeafNode(vector<uint32_t> &prims);
};

VSRAY_NAMESPACE_END


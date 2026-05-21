
#include "../include/dawg.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <set>
#include <vector>

void remove_from_vector(std::vector<DawgNode *> *vec, DawgNode *item) {
        std::vector<DawgNode *>::iterator pos =
            std::find(vec->begin(), vec->end(), item);
        if (pos !=
            vec->end()) // == myVector.end() means the element was not found
                vec->erase(pos);
}

DawgNode::DawgNode(Tile t) {
        parents = std::vector<DawgNode *>();
        children = std::vector<DawgNode *>();
        parents_set = std::set<DawgNode *>();
        children_set = std::set<DawgNode *>();
        this->t = t;
}

bool DawgNode::equivalent(DawgNode *other) {
        return children_set == other->children_set;
}

void DawgNode::add_child(DawgNode *child) {
        if (children_set.contains(child)) {
                return;
        }
        children_set.insert(child);
        children.push_back(child);
}

void DawgNode::add_parent(DawgNode *parent) {
        if (parents_set.contains(parent)) {
                return;
        }
        parents_set.insert(parent);
        parents.push_back(parent);
}

void DawgNode::remove_child(DawgNode *child) {
        if (!children_set.contains(child)) {
                return;
        }
        children_set.erase(child);
        remove_from_vector(&children, child);
}

void DawgNode::remove_parent(DawgNode *parent) {
        if (!parents_set.contains(parent)) {
                return;
        }
        parents_set.erase(parent);
        remove_from_vector(&parents, parent);
}

bool DawgNode::has_child(DawgNode *child) {
        return children_set.contains(child);
}

bool DawgNode::has_parent(DawgNode *parent) {
        return parents_set.contains(parent);
}


void DawgNode::replace(DawgNode *sub){
        for(DawgNode *parent : this->parents){
                parent->remove_child(this);
                parent->add_child(sub);
                this->remove_parent(parent);
                sub->add_parent(parent);
        }

        for(DawgNode *child : this->children){
                child->remove_parent(this);
                child->add_parent(sub);
                this->remove_child(child);
                sub->add_child(child);
        }
}

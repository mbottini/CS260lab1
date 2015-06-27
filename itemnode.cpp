// itemnode.cpp
// Michael Bottini
// Created for CS260
// June 25, 2015
// Implementation file for linked list node.

#include "itemnode.h"

itemNode::itemNode() {
    _count = 0;
    _next = NULL;
    return;
}

itemNode::itemNode(item newItem) {
    _item = newItem;
    _count = 0;
    _next = NULL;
    return;
}

itemNode::itemNode(const itemNode& originalNode) {
    *this = originalNode;
    return;
}

itemNode& itemNode::operator =(const itemNode& originalNode) {
    _item = originalNode.getItem();
    _count = originalNode.getCount();
    _next = NULL; // We cannot pass the pointer to the new node because
                  // it will link it to the original linked list.
    return *this;
}

char* itemNode::getName() const {
    return _item.getName();
}

double itemNode::getWeight() const {
    return _item.getWeight();
}

const item& itemNode::getItem() const {
    return this->_item;
}

int itemNode::getCount() const {
    return _count;
}

itemNode* itemNode::getNext() const {
    return _next;
}

void itemNode::setItem(const item& newItem) {
    _item = newItem;
    return;
}

void itemNode::setCount(int newCount) {
    _count = newCount;
    return;
}

void itemNode::setNext(itemNode* newPtr) {
    _next = newPtr;
    return;
}

void itemNode::incrementCount() {
    _count++;
    return;
}

void itemNode::decrementCount() {
    _count--;
    return;
}

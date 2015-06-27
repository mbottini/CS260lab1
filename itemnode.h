// itemnode.h
// Michael Bottini
// Created for CS260
// June 25, 2015
// Defines item linked list node.

#ifndef ITEMNODE_H
#define ITEMNODE_H
#include "item.h"
#include <iostream>

class itemNode {
    private:
        item _item;
        int _count;
        itemNode *_next;

    public:
        itemNode();
        itemNode(item newItem);

        itemNode(const itemNode& originalNode);
        itemNode& operator =(const itemNode& originalNode);

        char* getName() const;
        double getWeight() const;
        const item& getItem() const;
        int getCount() const;
        itemNode* getNext() const;

        void setItem(const item& newItem);
        void setCount(int newCount);
        void setNext(itemNode* newPtr);

        void incrementCount();
        void decrementCount();
};
#endif

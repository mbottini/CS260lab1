// inventory.h
// Michael Bottini
// Created for CS260
// June 25, 2015
// Defines inventory class.

#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include "item.h"
#include "itemnode.h"

class inventory {
    private:
        itemNode *_head;
        double _weight;
        int _count;
        double _maxWeight;

    public:
        void init();
        inventory(int maxWeight = 100);
        inventory(const inventory& originalInventory);
        inventory& operator =(const inventory& originalInventory);
        void chainDelete();
        ~inventory();

        double getWeight() const;
        int getCount() const;
        itemNode* getHead() const;

        void AddItem(const item& newItem);
        void addWeightAndCount(itemNode* node, const item& newItem);
        void subtractWeightAndCount(const item& newItem);
        void RemoveItem(const char* name);
        void PrintInventory();
};

#endif

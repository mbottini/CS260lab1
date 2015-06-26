// item.h
// Michael Bottini
// Created for CS260
// June 22, 2014

// Header file for "item" class, which will be used in an inventory
// manager.

#ifndef ITEM_H
#define ITEM_H
#include <cstring>
#include <iostream>

class item {
    private:
        char* _name;
        double _weight;

    public:
        item(const char* newName = "", double newWeight = 0);
        item(const item& originalItem);
        item& operator =(const item& originalItem);
        ~item();

        char* getName() const; 
        double getWeight() const;

        void setName(const char* newName);
        void setWeight(double newWeight);
        void printSuccess() const;
        void printFailure() const;

        bool operator <(const item& other) const;
        bool operator >(const item& other) const;
        bool operator ==(const item& other) const;
        bool operator !=(const item& other) const;
        bool operator <=(const item& other) const;
};

int CIstrcmp(const char* str1, const char* str2);
void toLower(char* str);

char* makeAndCopy(const char* newName);
#endif

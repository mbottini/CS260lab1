// item.cpp
// Michael Bottini
// Created for CS260
// June 22, 2015

// Implementation file for item class.

#include "item.h"

// Set by default to "" and 0, respectively.
item::item(const char* newName, double newWeight) {
    _name = makeAndCopy(newName);
    _weight = newWeight;
    return;
}

// Uses the overloaded = operator right below. I used this method for all
// of the copy constructors.
item::item(const item& originalItem) {
    _name = NULL;
    *this = originalItem;
    return;
}

item& item::operator =(const item& originalItem) {
    if(_name) { // Avoids memory leaks if _name is already defined.
        delete [] _name;
    }

    _name = makeAndCopy(originalItem.getName());
    _weight = originalItem.getWeight();
    return *this;
}

item::~item() {
    if(_name) {
        delete [] _name;
    }
    _weight = 0;
    return;
}

char* item::getName() const {
    return _name;
}

double item::getWeight() const {
    return _weight;
}

void item::setName(const char* newName) {
    if (_name) {
        delete [] _name;
    }

    _name = makeAndCopy(newName);

    return;
}

void item::setWeight(double newWeight) {
    _weight = newWeight;
    return;
}

void item::printSuccess() const {
    std::cout << "You picked up a " << _name << ".\n";
    return;
}

void item::printFailure() const {
    std::cout << "You're not strong enough to pick up the "
              << _name
              << " with everything else you're carrying.\n";
    return;
}

bool item::operator <(const item& other) const {
    return (CIstrcmp(_name, other.getName()) < 0);
}

bool item::operator >(const item& other) const {
    return (CIstrcmp(_name, other.getName()) > 0);
}

bool item::operator ==(const item& other) const {
    return (CIstrcmp(_name, other.getName()) == 0);
}

bool item::operator !=(const item& other) const {
    return (!(_name == other.getName()));
}

bool item::operator <=(const item& other) const {
    return _name < other.getName() || _name == other.getName();
}

int CIstrcmp(const char* str1, const char* str2) {
    int returnValue = 0;
    char *insensitiveStr1 = makeAndCopy(str1);
    char *insensitiveStr2 = makeAndCopy(str2);
    toLower(insensitiveStr1);
    toLower(insensitiveStr2);

    returnValue = strcmp(insensitiveStr1, insensitiveStr2);
    
    delete [] insensitiveStr1;
    delete [] insensitiveStr2;
    return returnValue;
}

void toLower(char* str) {
    for(int i = 0; str[i]; i++) { // Will end when str[i] == \0.
        str[i] = tolower(str[i]);
    }

    return;
}

// Takes a C-string, allocates a new space for it to go to, copies it over,
// and returns the new pointer. Used to deep-copy strings.
char* makeAndCopy(const char* newName) {
    char *newPtr = new char[strlen(newName) + 1];

    if(newPtr) {
        strncpy(newPtr, newName, strlen(newName) + 1);
    }

    return newPtr; // Returns NULL if memory failure.
}

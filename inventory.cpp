#include "inventory.h"

inventory::inventory(int maxWeight) {
    _head = NULL;
    _weight = 0;
    _count = 0;
    _maxWeight = maxWeight;
    return;
}

inventory::inventory(const inventory& originalInventory) {
    _head = NULL;
    *this = originalInventory;
    return;
}

inventory& inventory::operator =(const inventory& originalInventory) {
    itemNode *tempNode;
    itemNode *otherNode = originalInventory.getHead();
    itemNode *currentNode = _head;
    
    // Delete the list that was there before.
    chainDelete();

    _head = NULL;
    tempNode = NULL;

    while(otherNode) {
        currentNode = new itemNode;

        if(currentNode) {
            *currentNode = *otherNode; // Using overloaded itemNode operator
                                       // on dereferenced pointers.
        }

        if(_head == NULL) {
            _head = currentNode;
        }

        if(tempNode) {
            tempNode->setNext(currentNode);
        }

        tempNode = currentNode;
        otherNode = otherNode->getNext();
    }

    _weight = originalInventory.getWeight();
    _count = originalInventory.getCount();

    return *this;
}

void inventory::chainDelete() {
    itemNode *currentNode = _head;
    itemNode *tempNode;

    while(currentNode) {
        tempNode = currentNode->getNext();
        delete currentNode;
        currentNode = tempNode;
    }

    _head = NULL;
    _weight = 0;
    _count = 0;
    return;
}

inventory::~inventory() {
    chainDelete();
    return;
}

itemNode* inventory::getHead() const {
    return _head;
}

double inventory::getWeight() const {
    return _weight;
}

int inventory::getCount() const {
    return _count;
}

void inventory::AddItem(const item& newItem) {
    // We start by checking the weight to see if it will overload us.
    // If so, we don't do anything and can immediately return.

    if(newItem.getWeight() + _weight > _maxWeight) {
        newItem.printFailure();
        return;
    }

    itemNode *newNode = new itemNode;
    
    if(newNode) {
        newNode->setItem(newItem);
        itemNode *currentNode = _head;
        itemNode *previousNode = NULL;

        // Go to the first node that is greater than newItem.
        // previousNode will either be NULL, (in which case it's
        // at the head of the list) equal to newItem,
        // (in which case it will be incremented)
        // or less than newItem (in which case newNode will be
        // put between previousNode and currentNode).

        while(currentNode && newItem >= currentNode->getItem()) {
            previousNode = currentNode;
            currentNode = currentNode->getNext();
        }

        if(previousNode == NULL) {
            newNode->setNext(_head);
            _head = newNode;
            addWeightAndCount(newNode, newItem);
        }

        else if(newItem == previousNode->getItem()) {
            addWeightAndCount(previousNode, newItem);
            delete newNode;
        }

        else {
            previousNode->setNext(newNode);
            newNode->setNext(currentNode);
            addWeightAndCount(newNode, newItem);
        }
    }

    return;
}

void inventory::addWeightAndCount(itemNode* node, const item& newItem) {
    if(newItem.getWeight() == node->getWeight()) {
        node->incrementCount();
        _weight += newItem.getWeight();
        _count++;
        newItem.printSuccess();
    }

    else {
        std::cout << "ERROR: tried to add a duplicate item "
                  << "with wrong weight!\n";
    }
    return;
}

void inventory::subtractWeightAndCount(const item& newItem) {
    _weight -= newItem.getWeight();
    _count--;
}
    
void inventory::RemoveItem(const char* name) {
    itemNode *currentNode = _head;
    itemNode *previousNode = NULL;

    // Loop through the linked list, looking for a match. We store
    // the previous node in case we have to entirely remove a node.

    while(currentNode && 
          CIstrcmp(name, currentNode->getName()) > 0) {
        previousNode = currentNode;
        currentNode = currentNode->getNext();
    }

    // We're either at the end of the list, at a match, or beyond the point
    // where there could be a match.

    if(currentNode == NULL || 
        CIstrcmp(name, currentNode->getName()) != 0) {
        std::cout << "You don't have a " << name << " in your inventory.\n";
    }

    else {
        std::cout << "You dropped a " << name << ".\n";
        currentNode->decrementCount();
        subtractWeightAndCount(currentNode->getItem());

        // Now we test to see if we have to delete the node.

        if(currentNode->getCount() == 0) {
            if(previousNode == NULL) { // If it's at the head,
                _head = _head->getNext(); // delete the head.
            }

            else { // Otherwise, we delete the link in the middle.
                previousNode->setNext(currentNode->getNext());
            }
            delete currentNode;
        }
    }

    return;
}

void inventory::PrintInventory() {
    itemNode *currentNode = _head;

    std::cout << "\nCurrent inventory:\n";

    if(currentNode == NULL) {
        std::cout << "\t(no items)\n";
    }

    else {
        while(currentNode) {
            std::cout << "\t[" << currentNode->getCount() << "] "
                      << currentNode->getName() << "\n";
            currentNode = currentNode->getNext();
        }
        std::cout << "Total items: " << _count << "\n";
        std::cout << "Total weight: " << _weight << "\n";
    }
    std::cout << "\n";

    return;
}

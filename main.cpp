#include <iostream>
#include "item.h"
#include "inventory.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

using namespace std;

void AddItem(inventory& inv,char* name,double weight)
{
	cout << "Adding " << name << " with a weight of " << weight << "." << endl;
	inv.AddItem(item(name,weight));
}

void RemoveItem(inventory& inv,char* name)
{
	cout << "Removing " << name << "." << endl;
	inv.RemoveItem(name);
}

void doTestBasic() 
{
	inventory inv;

	// Make sure printing an empty inventory works
	inv.PrintInventory();

	// Make sure adding the first one works
	AddItem(inv,"helmet",5);
	inv.PrintInventory();

	// Add some more items
	AddItem(inv,"bracelet of power",1);
	AddItem(inv,"red potion",2);
	inv.PrintInventory();

	// Add some duplicates
	AddItem(inv,"bracelet of power",1);
	AddItem(inv,"red potion",2);
	inv.PrintInventory();

	// Add some heavy stuff
	AddItem(inv,"bag of gold coins",50);
	AddItem(inv,"bag of gold coins",50);

	// Now some removes
	RemoveItem(inv,"short sword");
	RemoveItem(inv,"helmet");
	RemoveItem(inv,"bracelet of power");
	inv.PrintInventory();
}

void doTestAdvanced() 
{
	inventory inv;

	// Add items in reverse order
	AddItem(inv,"yellow potion",0.5);
	AddItem(inv,"trident",1.0);
	AddItem(inv,"helmet",1.0);
	AddItem(inv,"amulet",1.0);
	inv.PrintInventory();

	// Add items at the beginning, middle, end
	AddItem(inv,"aardvark skin",5.0);
	AddItem(inv,"newt's eye",0.1);
	AddItem(inv,"zebra feather",0.1);
	inv.PrintInventory();

	// Remove items at the beginning, middle, end
	RemoveItem(inv,"aardvark skin");
	RemoveItem(inv,"newt's eye");
	RemoveItem(inv,"zebra feather");
	inv.PrintInventory();

	// Add items with different case
	AddItem(inv,"helmet",1.0);
	AddItem(inv,"Helmet",1.0);
	AddItem(inv,"HELMET",1.0);
	inv.PrintInventory();

	// Remove items with case insensitivity
	RemoveItem(inv,"HELMET");
	inv.PrintInventory();

}

void doTestBadData() 
{
	inventory inv(50);

	// Adding too much
	AddItem(inv,"bag of gold coins",50);	// should work
	AddItem(inv,"feather",0.1);				// should fail
	inv.PrintInventory();
	RemoveItem(inv,"bag of gold coins");	// should work
	inv.PrintInventory();

	// Using long strings
	AddItem(inv,"this is such a long item and nothing should have a name thing long but we have no guarantee that some crazy person wouldn't make such an item and then we need to make sure our program doesn't break.  Hint: don't use char[] to store data.  Only use char*.",1.0);
	inv.PrintInventory();
	
	// Same item with wrong weight
	AddItem(inv,"helmet",1.0);
	AddItem(inv,"helmet",10.0);
	inv.PrintInventory();
}

int main() {

	doTestBasic();
	doTestAdvanced();
	doTestBadData();

#ifdef _WIN32
	if (_CrtDumpMemoryLeaks()) {
		cout << "Memory leaks!" << endl;
	}
#endif

	return 0;
}
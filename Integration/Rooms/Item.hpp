#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;
using std::string;

class Item{
	private:
		string itemName;
		string itemDescription;
		bool canGrab;
		bool visible;
		Item * heldItem;
	public:
		Item(string name, string desc, bool grab, bool isVisible){
			itemName = name;
			itemDescription = desc;
			canGrab = grab;
			visible = isVisible;
			heldItem = NULL;
		}
		string getItemName(){ return itemName; }
		string getItemDescription(){ return itemDescription; }
		bool getCanGrab() { return canGrab; }
		Item * getHeldItem() { return heldItem; }
		void setHeldItem(Item * item) { heldItem = item; }
		void removeHeldItem() { heldItem = NULL; }
		void makeVisible() { visible = true; }
		bool isVisible() { return visible; }
		void setItemDescription(string desc) { itemDescription = desc; }
};

#endif

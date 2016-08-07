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
	public:
		Item(string name, string desc){
			itemName = name;
			itemDescription = desc;
		}
		string getItemName(){ return itemName; }
		string getItemDescription(){ return itemDescription; }
};

#endif

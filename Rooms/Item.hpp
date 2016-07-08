#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Item{
	private:
		string itemName;
		string itemDescription;
		vector<string> usageVerbs;
		std::unordered_map<string, vector<string> > usageResults;
	public:
		Item(string name, string desc, vector<string> verbs, std::unordered_map<string, vector<string> > results){
			itemName = name;
			itemDescription = desc;
			usageVerbs = verbs;
			usageResults = results;
		}
		string getItemName(){ return itemName; }
		string getitemDescription(){ return itemDescription; }
		vector<string> getUsageVerbs(){ return usageVerbs; }
		vector<string> processUsage(string & verb);

};

#endif

#include "Item.hpp"

vector<string> Item::processUsage(string & verb){
	unordered_map<string, vector<string> >::iterator it; 
	for(it = usageResults.begin(); it != usageResults.end(); ++it){
		if(it->first == verb){
			return it->second;
		}
	}
}

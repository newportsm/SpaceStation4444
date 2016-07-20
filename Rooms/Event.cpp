#include "Event.hpp"

vector<string> Event::processEvent(string & option){
	unordered_map<string, vector<string> >::iterator it; 
	for(it = resultDescriptions.begin(); it != resultDescriptions.end(); ++it){
		if(it->first == option){
			return it->second;
		}
	}
	vector<string> empty{"NoOptions"};
	return empty;
}


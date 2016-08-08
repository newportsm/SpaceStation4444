#include "Event.hpp"

//This function simply takes a string and looks through 
//unordered_map to find a matching key.
//Will return vector of strings with "NoOptions" if it doesn't find
//a match (this shouldn't happen though, because we check options
//before starting search).
vector<string> Event::processEvent(string option){
	unordered_map<string, vector<string> >::iterator it; 
	for(it = resultDescriptions.begin(); it != resultDescriptions.end(); ++it){
		if(it->first == option){
			return it->second;
		}
	}
	vector<string> empty{"NoOptions"};
	return empty;
}


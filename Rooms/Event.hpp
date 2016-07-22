#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;

class Event{
	private:
		bool active;
		string eventName;
		string eventDescription;
		vector<string> eventOptions;
		std::unordered_map<string, vector<string> > resultDescriptions;
	public:
		Event(const string & name, const string & desc, const vector<string> & options, const std::unordered_map<string, vector<string> > & results){
			active = true;
			eventName = name;
			eventDescription = desc;
			eventOptions = options;
			resultDescriptions = results;
		}
		bool getStatus() { return active; }
		void changeStatus() { active = !active; }
		string getEventName() { return eventName; }
		string getEventDescription() { return eventDescription; }
		const vector<string> * getEventOptions() { return & eventOptions; }
		
		vector<string> processEvent(string option);

};

#endif

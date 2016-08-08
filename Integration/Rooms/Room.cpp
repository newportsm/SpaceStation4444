#include "Room.hpp"
#include <fstream>
#include <string>

//Loops through pointer to Item vector and erases that item if found
void Room::removeItem(Item * item) {
	vector<Item *>::iterator it;
	it = items.begin();
	for(;it < items.end(); ++it){
		if(*it == item){
			delete ((*it));
			items.erase(it);
			break;
		}
	}
}

//Loops through pointer to Room vector and erases that item if found
void Room::removeRoom(Room * room) {
	vector<Room *>::iterator it;
	it = connectedRooms.begin();
	for(;it < connectedRooms.end(); ++it){
		if(*it == room){
			delete ((*it));
			connectedRooms.erase(it);
			break;
		}
	}
}

//Loops through pointer to Event vector and erases that event if found
void Room::removeEvent(Event * event) {
	vector<Event *>::iterator it;
	it = events.begin();
	for(;it < events.end(); ++it){
		if(*it == event){
			delete ((*it));
			events.erase(it);
			break;
		}
	}
}

//Looks through vector of events and returns pointer to event for
//first event found with active = true
Event * Room::getFirstActiveEvent(){
	vector<Event *>::iterator it;
	for(it = events.begin(); it < events.end(); ++it){
		if((*it)->getStatus()){
			return *it;
		}
	}
	return NULL;
}

#include "Room.hpp"
#include <fstream>
#include <string>

void Room::removeItem(Item * item) {
	vector<Item *>::iterator it;
	it = items.begin();
	for(;it < items.end(); ++it){
		if(*it == item){
			free (*it);
			items.erase(it);
			break;
		}
	}
}

void Room::removeRoom(Room * room) {
	vector<Room *>::iterator it;
	it = connectedRooms.begin();
	for(;it < connectedRooms.end(); ++it){
		if(*it == room){
			connectedRooms.erase(it);
			break;
		}
	}
}

void Room::removeEvent(Event * event) {
	vector<Event *>::iterator it;
	it = events.begin();
	for(;it < events.end(); ++it){
		if(*it == event){
			events.erase(it);
			break;
		}
	}
}

Event * Room::getFirstActiveEvent(){
	vector<Event *>::iterator it;
	for(it = events.begin(); it < events.end(); ++it){
		std::cout << (*it)->getEventName() << std::endl;
		if((*it)->getStatus()){
			return *it;
		}
	}
	return NULL;
}

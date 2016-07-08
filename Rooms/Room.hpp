#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "Event.hpp"
#include "Item.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Room{
	private:
		string roomName;
		string longDescription;
		string shortDescription;
		vector<Room *> connectedRooms;
		vector<Event *> events;
		vector<Item *> items;
		bool visited;
	public:
		Room(string name, string longDesc, string shortDesc){
			roomName = name;
			longDescription = longDesc;
			shortDescription = shortDesc;
			visited = false;
		}
		
		void addRoom(Room * newRoom) { connectedRooms.push_back(newRoom); }
		void addItem(Item * newItem) { items.push_back(newItem); }
		void addEvent(Event * newEvent) { events.push_back(newEvent); }

		void changeVisited() { visited = !visited; }
		bool getVisited() { return visited; }
		
		string getRoomName() { return roomName; }
		string getLongDescription() { return longDescription; }
		string getShortDescription() { return shortDescription; }
		
		void removeItem(Item * item);
		void removeRoom(Room * room);
		void removeEvent(Event * event);
		
		const vector<Item *> getCurrentItems(){ return items; }
		const vector<Room *> getCurrentRooms(){ return connectedRooms; }
		const vector<Event *> getCurrentEvents(){ return events; }

		Event * getFirstActiveEvent();

};

#endif 

#include "Room.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Event.hpp"
#include "factories.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;

int main(){

	/*string name = "Room1";
	string longD = "longDescription";
	string shortD = "shortDescription";
	string evName = "event";
	string evDesc = "event desc";

	vector<string> strings { "one", "two" };
	//vector< vector<string> > results {vector<string>{"one", "two"}, vector<string>{"three", "four"}};
	unordered_map< string, vector<string> > results {{"one", {"a", "b"}}, {"two", {"c", "d"}}};

	Room newRoom(name, longD, shortD);
	Event newEvent(evName, evDesc, strings, results);
	
	vector<string> opts;

	newRoom.addEvent(&newEvent);

	Event * curEvent;

	cout << newRoom.getFirstActiveEvent()->getEventName() << endl;

	string desc = newRoom.getFirstActiveEvent()->getEventDescription();
	cout << desc << endl;

	cout << newRoom.getFirstActiveEvent()->getEventOptions()[0] << endl;

	string opt = newRoom.getFirstActiveEvent()->getEventOptions()[0];

	vector<string> returned = newRoom.getFirstActiveEvent()->processEvent(opt);

	cout << returned[0] << endl;

	Player player;

	string flash = "flashlight";
	Item item(flash, longD, strings, results);

	player.addItem(&item);

	cout << player.getCurrentItems()[0]->getItemName() << endl;*/

	vector<Room *> roomz;
	roomFactory(&roomz);
	vector<Room *> connectedRoomz;

	for(int z = 0; z < roomz.size(); z++){
		cout << roomz[z]->getRoomName() << endl;
		cout << roomz[z]->getLongDescription() << endl;
		cout << roomz[z]->getShortDescription() << endl;
		connectedRoomz = roomz[z]->getCurrentRooms();
		cout << "Connected rooms: " ;
		std::vector<Room *>::iterator it;
		for(it = connectedRoomz.begin(); it != connectedRoomz.end(); ++it)
			cout << (*it)->getRoomName() << "  ";
		cout << endl << " *** " << endl;
	}

	return 0;
}

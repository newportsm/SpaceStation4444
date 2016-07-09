#include "factories.hpp"



Room * getVectorPosition(string room, vector<Room *> * rooms){
	vector<Room *>::iterator it;
	for(it = rooms->begin(); it != rooms->end(); ++it){
		if((*it)->getRoomName() == room) return (*it);
	}
}

int stringToVector(string input, vector<string> *resultVector){
	int oldPos = 0;
	string newString;
	for(int pos = 0; pos < input.length(); pos++){
		if(input[pos] == ';' || input[pos] == '*'){
			newString = input.substr(oldPos, pos - oldPos);
			oldPos = pos + 1;
			resultVector->push_back(newString);
		}
	}
	return 1;
}

int stringToMap(string input, std::unordered_map<string, vector<string>> *resultMap){
	int oldPos = 0;
	string key;
	string newString;
	vector<string> value;
	for(int pos = 0; pos < input.length(); pos++){
		if(input[pos] == ':'){
			key = input.substr(oldPos, pos - oldPos);
			oldPos = pos + 1;
		}
		if(input[pos] == ',' || input[pos] == '*'){
			newString = input.substr(oldPos, pos - oldPos);
			oldPos = pos + 1;
			value.push_back(newString);
		}
	}
	std::pair<string, vector<string> > newPair(key, value);
	resultMap->insert(newPair);
}

int roomFactory(vector<Room *> * rooms){
	if(rooms == NULL) return 0;
	string name;
	string longDesc;
	string shortDesc; 
	string fileName;
	int count = 1;
	fileName = "rooms/room" + std::to_string(count);
	std::fstream roomFile;
	roomFile.open(fileName, std::fstream::in);
	while(roomFile.is_open()){
		std::getline(roomFile, name);	
		std::getline(roomFile, longDesc);
		std::getline(roomFile, shortDesc);
		Room * newRoom = new Room(name, longDesc, shortDesc);
		rooms->push_back(newRoom);
		roomFile.close();
		count++;
		fileName = "rooms/room" + std::to_string(count);
		roomFile.open(fileName, std::fstream::in);
	}
	fileName = "rooms/roomsconnected";
	roomFile.open(fileName, std::fstream::in);
	string input;
	while(getline(roomFile, input)){
		string curRoom;
		int pos = 0;
		int oldPos = 0;
		Room * curRoomPtr;
		Room * roomToAdd;
		while(input[pos] != ',') pos++;
		curRoom = input.substr(oldPos, pos);
		curRoomPtr = getVectorPosition(curRoom, rooms);
		oldPos = pos + 1;
		while(input[pos] != '*'){
			pos++;
			if(input[pos] == ',' || input[pos] == '*'){
				curRoom = input.substr(oldPos, pos - oldPos);
				oldPos = pos + 1;
				roomToAdd = getVectorPosition(curRoom, rooms);
				curRoomPtr->addRoom(roomToAdd);
			}
		}
	}
	return 1;
}



int itemFactory(vector<Room *> * rooms){
	if(rooms == NULL) return 0;
	string name;
	string description;
	string roomName;
	int count = 1;
	string fileName = "items/item" + std::to_string(count);
	std::fstream itemFile;
	itemFile.open(fileName, std::fstream::in);
	while(itemFile.is_open()){
		std::getline(itemFile, name);
		std::getline(itemFile, description);
		std::getline(itemFile, roomName);
		Item * newItem = new Item(name, description);
		vector<Room *>::iterator it;
		for(it = rooms->begin(); it != rooms->end(); ++it){
			if((*it)->getRoomName() == roomName)
				(*it)->addItem(newItem);
		}
		itemFile.close();
		count++;
		string fileName = "items/item" + std::to_string(count);
		itemFile.open(fileName, std::fstream::in);
	}
	return 1;
}

int eventFactory(vector<Room *> * rooms){
	if(rooms == NULL) return 0;
	string name;
	string room;
	string description;
	string input;
	string tempAction;
	vector<string> tempResults;
	vector<string> options;
	std::unordered_map< string, vector<string> > results;
	int count = 1;
	string fileName = "events/event" + std::to_string(count);
	std::fstream eventFile;
	eventFile.open(fileName, std::fstream::in);
	while(eventFile.is_open()){
		std::getline(eventFile, name);
		std::getline(eventFile, description);
		std::getline(eventFile, room);
		std::getline(eventFile, input);
		if(!stringToVector(input, &options))
			cout << "Error converting " << input << " to vector." << endl;
		while(std::getline(eventFile, input)){
			int pos = 0;
			while(input[pos] != ':') pos++;
			tempAction = input.substr(0, pos);
			if(!stringToVector(input.substr(pos + 1), &tempResults))
				cout << "Error convert " << input.substr(pos + 1) << " to vector." << endl;
			results.insert(std::make_pair(tempAction, tempResults));
		}
		Event * newEvent = new Event(name, description, options, results);
		vector<Room *>::iterator it;
		for(it = rooms->begin(); it != rooms->end(); ++it){
			if((*it)->getRoomName() == room){
				(*it)->addEvent(newEvent);
			}
		}
		eventFile.close();
		count++;
		string fileName = "events/event" + std::to_string(count);
		eventFile.open(fileName, std::fstream::in);
	}
}

int loadGame(vector<Room *> * rooms){
	int results = 0;
	if((results = roomFactory(rooms)) == 0) return results;
	if((results = itemFactory(rooms)) == 0) return results;
	if((results = eventFactory(rooms)) == 0) return results;
	return 1;
}







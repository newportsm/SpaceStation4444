#include "factories.hpp"

string cleanRoomName(string input){
	std::cout << (int)input[input.length() - 1] << std::endl;
	if((int)input[input.length() - 1] == 13)
		return input.substr(0, input.length() - 1);
	return input;
}

//Get pointer to Room for room with same name as the string room
Room * getVectorPosition(string room, vector<Room *> * rooms){
	//Iterate over vector of pointers to room until you find match
	//where the room has the same name as the string and return
	//the pointer
	vector<Room *>::iterator it;
	for(it = rooms->begin(); it != rooms->end(); ++it){
		string roomName = cleanRoomName((*it)->getRoomName());
		std::cout << roomName << std::endl;
		if(roomName == room) return (*it);
	}
	//If you find nothing, return null
	std::cout << "Could not find room with name " << room << std::endl;
	return NULL;
}

//Convert string (read from files) into vector of strings
int stringToVector(string input, vector<string> *resultVector){
	
	//After each string is read, this will become the new
	//starting position
	unsigned int oldPos = 0;
	
	//This will hold the substrings to be saved in resultVector
	string newString;

	//Loop over string, and create new substrings based on
	//the segments of the input string, where the string is
	//delimited by ; and *.
	for(unsigned int pos = 0; pos < input.length(); pos++){
		if(input[pos] == ';' || input[pos] == '*'){
			newString = input.substr(oldPos, pos - oldPos);
			std::cout << newString << std::endl;
			oldPos = pos + 1;
			resultVector->push_back(newString);
		}
	}
	return 1;
}

int roomFactory(vector<Room *> * rooms){
	std::cout << "Loading rooms" << std::endl;
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
		std::cout << name << std::endl;
		std::getline(roomFile, longDesc);
		std::cout << longDesc << std::endl;
		std::getline(roomFile, shortDesc);
		std::cout << shortDesc << std::endl;
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
		std::cout << "loading connected rooms" << std::endl;
		std::cout << "Input from connected room file: " << input << "++" << std::endl;
		string curRoom;
		int pos = 0;
		int oldPos = 0;
		Room * curRoomPtr;
		Room * roomToAdd;
		while(input[pos] != ',') pos++;
		curRoom = input.substr(oldPos, pos);
		curRoomPtr = getVectorPosition(curRoom, rooms);
		if(curRoomPtr == NULL){
			return 0;
		}
		oldPos = pos + 1;
		while(input[pos] != '*'){
			pos++;
			if(input[pos] == ',' || input[pos] == '*'){
				curRoom = input.substr(oldPos, pos - oldPos);
				std::cout << curRoom << std::endl;
				oldPos = pos + 1;
				roomToAdd = getVectorPosition(curRoom, rooms);
				if(roomToAdd == NULL){
					return 0;
				}
				curRoomPtr->addRoom(roomToAdd);
			}
		}
	}
	return 1;
}



int itemFactory(vector<Room *> * rooms){
	std::cout << "loading items" << std::endl;
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
		std::cout << name << std::endl;
		std::getline(itemFile, description);
		std::cout << description << std::endl;
		std::getline(itemFile, roomName);
		std::cout << roomName << std::endl;
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
	std::cout << "Loading events" << std::endl;
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
		std::cout << name << std::endl;
		std::getline(eventFile, description);
		std::cout << description << std::endl;
		std::getline(eventFile, room);
		std::cout << room << std::endl;
		std::getline(eventFile, input);
		std::cout << input << std::endl;
		if(!stringToVector(input, &options))
			cout << "Error converting " << input << " to vector." << endl;
		while(std::getline(eventFile, input)){
			int pos = 0;
			while(input[pos] != ':') pos++;
			tempAction = input.substr(0, pos);
			std::cout << tempAction << std::endl;
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

	return 1;
}

int loadGame(vector<Room *> * rooms){
	int results = 0;
	if((results = roomFactory(rooms)) == 0) return results;
	if((results = itemFactory(rooms)) == 0) return results;
	if((results = eventFactory(rooms)) == 0) return results;
	return 1;
}







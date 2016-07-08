#include "factories.hpp"

Room * getVectorPosition(string room, vector<Room *> * rooms){
	std::vector<Room *>::iterator it;
	for(it = rooms->begin(); it != rooms->end(); ++it){
		if((*it)->getRoomName() == room) return (*it);
	}
}

int roomFactory(vector<Room *> * rooms){
	if(rooms == NULL) return 0;
	std::string name;
	std::string longDesc;
	std::string shortDesc; 
	std::string fileName;
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


}



#include "factories.hpp"

//In case we're reading text files on Windows, we need to get rid
//of that '\r' on the end of strings.
string cleanStrings(string input){
	//Check if we have a carriage return and send back
	//the string w/o carriage return
	if((int)input[input.length() - 1] == 13)
		return input.substr(0, input.length() - 1);
	//If no carriage return, just send it back!
	return input;
}

//Get pointer to Room for room with same name as the string room
Room * getVectorPosition(string room, vector<Room *> * rooms){
	//Iterate over vector of pointers to room until you find match
	//where the room has the same name as the string and return
	//the pointer
	vector<Room *>::iterator it;
	for(it = rooms->begin(); it != rooms->end(); ++it){
		//Make sure we don't have carriage return at end of string
		string roomName = cleanStrings((*it)->getRoomName());
		if(roomName == room) return (*it);
	}
	//If you find nothing, return null
	std::cout << "Could not find room with name " << room << std::endl;
	return NULL;
}

//Convert string (read from files) into vector of strings
int stringToVector(string input, vector<string> *resultVector){
	
	resultVector->clear();

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
			oldPos = pos + 1;
			resultVector->push_back(newString);
		}
	}
	return 1;
}

//Factory function for creating and initializing Room objects 
//(objects saved via vector of pointers to Room in Game object)
//NOTE: This function is way too long and should be split up
int roomFactory(vector<Room *> * rooms){
	std::cout << "Loading rooms" << std::endl;
	//Make sure the rooms pointer isn't null
	if(rooms == NULL) return 0;

	//These will temporarily hold text read in from
	//test files and used to initialize Room objects
	string name;
	string longDesc;
	string shortDesc; 
	string fileName;

	//room text files are access via this file path
	//files are numbered the loop will continue reading
	//files until there are no more to be opened
	int count = 1;
	fileName = "rooms/room" + std::to_string(count);

	std::fstream roomFile;
	roomFile.open(fileName, std::fstream::in);

	//Loop as long as there are room files to open
	while(roomFile.is_open()){
		//get input from text file and run cleanStrings 
		//(in case there's a carriage return added by Windows)
		std::getline(roomFile, name);
		name = cleanStrings(name);
		std::getline(roomFile, longDesc);
		longDesc = cleanStrings(longDesc);
		std::getline(roomFile, shortDesc);
		shortDesc = cleanStrings(shortDesc);
		
		//Instantial new room object
		Room * newRoom = new Room(name, longDesc, shortDesc);
		
		//Add room object to game object's vector of
		//pointers to Room
		rooms->push_back(newRoom);

		//Close the current file and try opening the next one.
		roomFile.close();
		count++;
		fileName = "rooms/room" + std::to_string(count);
		roomFile.open(fileName, std::fstream::in);
	}

	//We add connected rooms AFTER initializing them
	//or there are no room objects to add connected rooms to
	fileName = "rooms/roomsconnected";
	roomFile.open(fileName, std::fstream::in);
	string input;

	std::cout << "Loading connected rooms" << std::endl;

	//Get each line in text file
	//First room is the room to add connected rooms to
	//Remaining rooms are rooms to be added to list
	while(getline(roomFile, input)){
		//Clean up string
		input = cleanStrings(input);
		string curRoom;
		int pos = 0;
		int oldPos = 0;

		//curRoomPtr holds pointer to room to be added to
		//which is found by taking the first room and searching
		//using getVectorPosition, which loops through
		//the rooms vector and finds the room with the matching
		//string for name
		Room * curRoomPtr;
		Room * roomToAdd;
		while(input[pos] != ',') pos++;
		curRoom = input.substr(oldPos, pos);
		curRoomPtr = getVectorPosition(curRoom, rooms);

		//If we can't get a match, fail.
		if(curRoomPtr == NULL){
			return 0;
		}

		oldPos = pos + 1;

		//Loop over the rest of string input, getting pointer
		//for each room name in the string and adding pointer
		//to room via curRoomPtr
		while(input[pos] != '*'){
			pos++;
			if(input[pos] == ',' || input[pos] == '*'){
				curRoom = input.substr(oldPos, pos - oldPos);
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


//Factory function for creating and initializing Item objects 
//(objects saved in corresponding room objects saved in the 
//vector of pointers to Room in the Game object)
int itemFactory(vector<Room *> * rooms){

	std::cout << "Loading items" << std::endl;

	//If rooms is null, fail
	if(rooms == NULL) return 0;
	string name;
	string description;
	string roomName;
	int count = 1;
	string fileName = "items/item" + std::to_string(count);
	std::fstream itemFile;
	itemFile.open(fileName, std::fstream::in);

	//Same as intializing room -- read in text from text file
	//and save in room indicated by roomName line
	//Loop until no more files to open
	while(itemFile.is_open()){
		std::getline(itemFile, name);
		name = cleanStrings(name);
		std::getline(itemFile, description);
		description = cleanStrings(description);
		std::getline(itemFile, roomName);
		roomName = cleanStrings(roomName);
		Item * newItem = new Item(name, description);
		vector<Room *>::iterator it;
		for(it = rooms->begin(); it != rooms->end(); ++it){
			string curRoomName = cleanStrings((*it)->getRoomName());
			if(curRoomName == roomName)
				(*it)->addItem(newItem);
		}
		itemFile.close();
		count++;
		string fileName = "items/item" + std::to_string(count);
		itemFile.open(fileName, std::fstream::in);
	}
	return 1;
}

//Factory function for creating and initializing Event objects 
//(objects saved via vector of pointers to Room in Game object)
//NOTE: This function is way too long and should be split up
int eventFactory(vector<Room *> * rooms){
	std::cout << "Loading events" << std::endl;

	//fail if rooms is null
	if(rooms == NULL) return 0;

	//Events are a bit complicated:
	//They have name, descriptions, list of potential input
	//and an unordered_map to hold results of inputs
	//The unordered map has a string as its key and a vector
	//of strings as its value
	string name;
	string room;
	string description;
	string input;
	string tempAction;
	vector<string> tempResults;
	vector<string> options;
	std::unordered_map< string, vector<string> > results;

	//Files are read through same process as Room objects
	int count = 1;
	string fileName = "events/event" + std::to_string(count);
	std::fstream eventFile;
	eventFile.open(fileName, std::fstream::in);
	while(eventFile.is_open()){

		//Clear options, tempResults, and results each time
		//or you will have a sad time with this. :(
		options.clear();
		tempResults.clear();
		results.clear();

		//Get the name, description, and room the event
		//happens in
		std::getline(eventFile, name);
		name = cleanStrings(name);
		std::getline(eventFile, description);
		description = cleanStrings(description);
		std::getline(eventFile, room);
		room = cleanStrings(room);

		//Input here holds the options for the event
		//Once we have the input string, split it into a vector of strings
		std::getline(eventFile, input);
		input = cleanStrings(input);
		if(!stringToVector(input, &options))
			cout << "Error converting " << input << " to vector." << endl;

		//Here, input hold the options and their corresponding results
		//Results have description and keyword -- keyword is used
		//by the engine to figure out what to do next
		while(std::getline(eventFile, input)){
			input = cleanStrings(input);
			int pos = 0;
			while(input[pos] != ':'){
			   	pos++;
			}
			//Temp ation is key
			tempAction = input.substr(0, pos);
			//turn remainder of string into a vector called tempResults
			if(!stringToVector(input.substr(pos + 1), &tempResults)){
				cout << "Error converting " << input.substr(pos + 1);
				cout << " to vector." << endl;
			}
			//Add tempAction and tempResults to unordered map
			results.insert(std::make_pair(tempAction, tempResults));
		}

		//Create new event object
		Event * newEvent = new Event(name, description, options, results);

		//Find the room it belongs to...
		vector<Room *>::iterator it;
		//cout << "Add events to rooms" << endl;
		for(it = rooms->begin(); it != rooms->end(); ++it){
			string roomName = cleanStrings((*it)->getRoomName());
			if(roomName == room){
				//...and add it.
				(*it)->addEvent(newEvent);
				break;
			}
		}

		//close and then try to open next file like room file
		eventFile.close();
		count++;
		string fileName = "events/event" + std::to_string(count);
		eventFile.open(fileName, std::fstream::in);
	}

	return 1;
}

//Simple function to call the functions necessary to load the game
int loadGame(vector<Room *> * rooms){
	int results = 0;
	if((results = roomFactory(rooms)) == 0) return results;
	if((results = itemFactory(rooms)) == 0) return results;
	if((results = eventFactory(rooms)) == 0) return results;
	cout << endl;
	return 1;
}







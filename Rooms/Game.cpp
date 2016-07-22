#include "Game.hpp"

//Simple function for debugging.
//prints all the info saved in each rooms (but not item/event vector)
void Game::printRooms(){
	vector<Room *>::const_iterator connIt;
	std::vector<Room *>::const_iterator it;
	for(it = rooms.begin(); it != rooms.end(); ++it){
		cout << (*it)->getRoomName() << ": ";
		connIt = (*it)->getCurrentRooms()->begin();
		for(; connIt != (*it)->getCurrentRooms()->end(); ++connIt){
			cout << (*connIt)->getRoomName() << "   ";
		}
		cout << endl;
	}
}

//Main function called by game loop (for the moment)
//Will print info for current room -- room name, description, etc.
//If there is an active event, that is printed and then handled
//before anything else happens
void Game::printCurrentRoom(){
	cout << "You are in the " << currentRoom->getRoomName() << endl;
	
	Event * currentEvent = currentRoom->getFirstActiveEvent();

	//If we have an active event, print name, description and options
	//and then call respondToEvent to handle user input
	if(currentEvent != NULL){
		cout << endl << currentEvent->getEventName() << endl;
		cout << currentEvent->getEventDescription() << endl;
		cout << "You can: ";
		const vector<string> * currentOptions = currentEvent->getEventOptions();
		vector<string>::const_iterator optIt;
		for(optIt = currentOptions->begin(); optIt != currentOptions->end(); ++optIt){
			cout << (*optIt) << ", ";
		}
		cout << endl;
		respondToEvent(currentEvent, currentOptions);
	}
	//Otherwise, print room stuff and do regular user input via getPlayerInput
	else {
		if(!currentRoom->getVisited()){
			cout << currentRoom->getLongDescription() << endl;
			currentRoom->changeVisited();
		} else {
			cout << currentRoom->getShortDescription() << endl;
		}
		cout << "The room seems to be quiet." << endl;
		getPlayerInput();
	}
}

//Simple function for splitting string into vector
//From this StackOverflow question:
//http://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
void Game::inputToVector(string input){
	currentCommand.clear();
	std::stringstream inputString(input);
	std::istream_iterator<string> begin(inputString);
	std::istream_iterator<string> end;
	vector<string> tempCommand(begin, end);
	std::copy(currentCommand.begin(), currentCommand.end(), std::ostream_iterator<string>(std::cout, "\n"));
	currentCommand = tempCommand;
}

//Take currentEvent and currentOptions and gets input from user
//Checks if input is in currentOptions and if it is, Event object's processEvent is called
//and the result text is diplayed. The corresponding result keyword is also checked before
//calling processEvent
void Game::respondToEvent(Event * currentEvent, const vector<string> * currentOptions){
	string input;
	bool match = false;
	do{
		do{
			cout << "What do you want to do?" << endl;
			getline(cin, input);
			cout << endl;

		} while(input.length() < 1);
		vector<string>::const_iterator optIt;
		
		for(optIt = currentOptions->begin(); optIt != currentOptions->end(); ++optIt){
			if(input == (*optIt)){
				cout << "You selected: " << (*optIt) << endl;
				match = true;
				vector<string>results(currentEvent->processEvent(input));
				cout << results[0];
				if(results[1] == "playerdied"){
					playerHasDied();
				} else if(results[1] == "continue"){
					currentEvent->changeStatus();
				}
				cout << endl;
			}
		}
		if(!match){
			cout << "Sorry, I don't understand: " << input << endl;
		}
	}while(!match);
}

//Get input from player, then calls inputToVector to split it into vector
//and then calls processPlayerInput to hanlde that vector
void Game::getPlayerInput(){
	string input;
	do{
		cout << "What do you want to do?" << endl;
		getline(cin, input);
		cout << endl;

	} while(input.length() < 1);

	inputToVector(input);
	processPlayerInput();
}

//Searches vector of connected rooms and sets currentRoom to be
//pointer to that room or displays error message
void Game::go(string location){
	vector<Room *>::iterator roomIt;
	Room * checkRoom = currentRoom;
	for(roomIt = rooms.begin(); roomIt != rooms.end(); ++roomIt){
		string roomName = (*roomIt)->getRoomName();
		if(location == roomName)
			currentRoom = (*roomIt);
	}
	if(checkRoom == currentRoom){
		cout << "Sorry, that room cannot be reached from here." << endl;
	}
}

//Lists all the items that can be picked up and
//the connected rooms
void Game::look(){
	const vector<Room *> * connectedRooms;
	connectedRooms = currentRoom->getCurrentRooms();
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	vector<Room *>::const_iterator roomIt;
	cout << "You can go to these rooms: ";
	for(roomIt = connectedRooms->begin(); roomIt != connectedRooms->end(); ++roomIt){
		cout << (*roomIt)->getRoomName() << ", ";
	}
	cout << endl;
	vector<Item *>::const_iterator itemIt;
	cout << "You can grab these items: ";
	for(itemIt = itemsInRoom->begin(); itemIt != itemsInRoom->end(); ++itemIt){
		cout << (*itemIt)->getItemName() << ", ";
	}
	cout << endl << endl;
}

//Picks up an item, which means the item is added to the items vector
//held by the player and removes the pointer from the room's items vector
void Game::grab(string item){
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	vector<Item *>::const_iterator itemIt;
	bool itemFound = false;
	for(itemIt = itemsInRoom->begin(); itemIt != itemsInRoom->end(); ++itemIt){
		string itemName = (*itemIt)->getItemName();
		if(itemName == item){
			string itemName = (*itemIt)->getItemName();
			string itemDesc = (*itemIt)->getItemDescription();
			Item * newItem = new Item(itemName, itemDesc);
			player.addItem(newItem);
			currentRoom->removeItem((*itemIt));
			cout << "You have picked up " << newItem->getItemName() << endl << endl;
			itemFound = true;
			return;
		}

	}
	if(!itemFound){
		cout << "Sorry that item is not in this room." << endl;
	}
}

//Displays all the items in the player's items vector
void Game::checkItemsInHand(){
	const vector<Item *> * items = player.getCurrentItems();
	vector<Item *>::const_iterator itemIt;
	cout << "You currently are holding: ";
	for(itemIt = items->begin(); itemIt != items->end(); ++itemIt){
		cout << (*itemIt)->getItemName() << ", ";
	}
	cout << endl;
}

//Uses currentCommand calls appropriate function matching command
void Game::processPlayerInput(){

	if(currentCommand[0] ==  "go"){
		if(currentCommand.size() > 1){
			if(currentCommand[1] == "to"){
				cout << "Let's go!" << endl << endl;
				string location = "";
				for(unsigned int i = 2; i < currentCommand.size(); i++){
					location += currentCommand[i] + " ";
				}
				location = location.substr(0, location.length() - 1);
				go(location);
			}
		}
	} else if (currentCommand[0] == "go"){
		cout << "Where do you want to go?" << endl;
	}
	else if(currentCommand[0] == "look"){
		look();
	}	
	else if(currentCommand[0] == "grab"){	
		if(currentCommand.size() > 1){
			string item = "";
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				item += currentCommand[i] + " ";
			}
			item = item.substr(0, item.length() - 1);
			grab(item);
		} else {
			cout << "What would you like to grab?" << endl << endl;
		}
	}
	else if(currentCommand[0] == "check"){
		checkItemsInHand();
	}
	else if(currentCommand[0] == "quit"){
		cout << "Good-bye!" << endl << endl;
		playerHasDied();
	}
	else
		cout << "Sorry, I don't understand." << endl << endl;
}


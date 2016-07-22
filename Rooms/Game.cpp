#include "Game.hpp"

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

void Game::printCurrentRoom(){
	cout << "You are in the " << currentRoom->getRoomName() << endl;
	if(!currentRoom->getVisited()){
		cout << currentRoom->getLongDescription() << endl;
		currentRoom->changeVisited();
	} else {
		cout << currentRoom->getShortDescription() << endl;
	}
	Event * currentEvent = currentRoom->getFirstActiveEvent();
	if(currentEvent != NULL){
		cout << currentEvent->getEventDescription() << endl;
		cout << "What do you want to do?" << endl;
		const vector<string> * currentOptions = currentEvent->getEventOptions();
		vector<string>::const_iterator optIt;
		for(optIt = currentOptions->begin(); optIt != currentOptions->end(); ++optIt){
			cout << (*optIt) << endl;
		}
	} else {
		cout << "The room seems to be quiet." << endl;
	}
	const vector<Item *> * currentItem = currentRoom->getCurrentItems();
	vector<Item *>::const_iterator itemIt;
	for(itemIt = currentItem->begin(); itemIt != currentItem->end(); ++itemIt){
		cout << (*itemIt)->getItemName() << endl;
	}
}

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

void Game::getPlayerInput(){
	string input;
	do{
		cout << "What do you want to do? (For example, \"Go to [room].\"" << endl;
		getline(cin, input);
		cout << endl;

	} while(input.length() < 1);

	inputToVector(input);
}

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

void Game::checkItemsInHand(){
	const vector<Item *> * items = player.getCurrentItems();
	vector<Item *>::const_iterator itemIt;
	cout << "You currently are holding: ";
	for(itemIt = items->begin(); itemIt != items->end(); ++itemIt){
		cout << (*itemIt)->getItemName() << ", ";
	}
	cout << endl;
}


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
		cout << "Test against events" << endl << endl;
}


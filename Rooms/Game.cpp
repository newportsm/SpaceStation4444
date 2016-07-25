#include "Game.hpp"

//This function gets information for current room and returns it as a struct. 
currentRoomStrings Game::getCurrentRoomStrings(){
    currentRoomStrings result;
    
    result.roomName = currentRoom->getRoomName();

	//If we have an active event, print name, description and options
	//and then call respondToEvent to handle user input
	if(currentRoom->getFirstActiveEvent() != NULL){
        result.activeEvent = true;
        result.roomDescription = "";
        result.eventName = currentRoom->getFirstActiveEvent()->getEventName();
        result.eventDescription = currentRoom->getFirstActiveEvent()->getEventDescription();
        result.currentOptions = currentRoom->getFirstActiveEvent()->getEventOptions();
	}
	//Otherwise, print room stuff and do regular user input via getPlayerInput
	else {
        result.activeEvent = false;
		if(!currentRoom->getVisited()){
            result.roomDescription =  currentRoom->getLongDescription();
			currentRoom->changeVisited();
		} else {
            result.roomDescription = currentRoom->getShortDescription();
		}
        result.eventName = "";
		result.eventDescription = "The room seems to be quiet.";
	}
    return result;
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
vector<string> Game::respondToEvent(string input){
    vector<string>results;
    bool match = false;
    vector<string>::const_iterator optIt;
    const vector<string> * currentOptions = currentRoom->getFirstActiveEvent()->getEventOptions();
    
    for(optIt = currentOptions->begin(); optIt != currentOptions->end(); ++optIt){
        if(input == (*optIt)){
            match = true;
            results = currentRoom->getFirstActiveEvent()->processEvent(input);
            if(results[1] == "playerdied"){
                playerHasDied();
            } else if(results[1] == "continue"){
                currentRoom->getFirstActiveEvent()->changeStatus();
            }
        }
    }
    if(!match){
        results.push_back( "Sorry, I don't understand: " );
    }
    return results;
}

//Searches vector of connected rooms and sets currentRoom to be
//pointer to that room or displays error message
string Game::go(string location){
	vector<Room *>::iterator roomIt;
	//Room * checkRoom = currentRoom;
	for(roomIt = rooms.begin(); roomIt != rooms.end(); ++roomIt){
		string roomName = (*roomIt)->getRoomName();
		if(location == roomName){
			currentRoom = (*roomIt);
            return "ok";
        }
	}
    return "Sorry, that room cannot be reached from here.";
}

//Lists all the items that can be picked up and
//the connected rooms
string Game::look(){
    string result = "";
	const vector<Room *> * connectedRooms;
	connectedRooms = currentRoom->getCurrentRooms();
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	vector<Room *>::const_iterator roomIt;
	result += "You can go to these rooms: ";
	for(roomIt = connectedRooms->begin(); roomIt != connectedRooms->end(); ++roomIt){
		result += (*roomIt)->getRoomName() + ", ";
	}
	vector<Item *>::const_iterator itemIt;
	result += "You can grab these items: ";
	for(itemIt = itemsInRoom->begin(); itemIt != itemsInRoom->end(); ++itemIt){
		result += (*itemIt)->getItemName() + ", ";
	}
    return result;
}

//Picks up an item, which means the item is added to the items vector
//held by the player and removes the pointer from the room's items vector
string Game::grab(string item){
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	vector<Item *>::const_iterator itemIt;
	bool itemFound = false;
    string result = "";
	for(itemIt = itemsInRoom->begin(); itemIt != itemsInRoom->end(); ++itemIt){
		string itemName = (*itemIt)->getItemName();
		if(itemName == item){
			string itemName = (*itemIt)->getItemName();
			string itemDesc = (*itemIt)->getItemDescription();
			Item * newItem = new Item(itemName, itemDesc);
			player.addItem(newItem);
			currentRoom->removeItem((*itemIt));
			result =  "You have picked up " + newItem->getItemName();
			itemFound = true;
			return result;
		}

	}
	if(!itemFound){
		result = "Sorry that item is not in this room.";
	}
    return result;
}

//Displays all the items in the player's items vector
string Game::checkItemsInHand(){
	const vector<Item *> * items = player.getCurrentItems();
	vector<Item *>::const_iterator itemIt;
    string results = "";
	results =  "You currently are holding: ";
	for(itemIt = items->begin(); itemIt != items->end(); ++itemIt){
		results += (*itemIt)->getItemName() + ", ";
	}
    return results;
}

//Uses currentCommand calls appropriate function matching command
string Game::processPlayerInput(string input){

    inputToVector(input);
	if(currentCommand[0] ==  "go"){
		if(currentCommand.size() > 1){
			if(currentCommand[1] == "to"){
				string location = "";
				for(unsigned int i = 2; i < currentCommand.size(); i++){
					location += currentCommand[i] + " ";
				}
				location = location.substr(0, location.length() - 1);
				return go(location);
			}
		}
	} else if (currentCommand[0] == "go"){
		return "Where do you want to go?";
	}
	else if(currentCommand[0] == "look"){
		return look();
	}	
	else if(currentCommand[0] == "grab"){	
		if(currentCommand.size() > 1){
			string item = "";
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				item += currentCommand[i] + " ";
			}
			item = item.substr(0, item.length() - 1);
			return grab(item);
		} else {
			return "What would you like to grab?";
		}
	}
	else if(currentCommand[0] == "check"){
		return checkItemsInHand();
	}
	else if(currentCommand[0] == "help") {
		instructions = "Use 'go to [exact room name]' to move to another room.\n" + 
		"Use 'look' to see what items are in a room and what the connected rooms are.\n" +
		"Use 'grab [exact item name]' to pick up an item.\n" +
		"Use 'quit' to exit. (Will not work when responding to an event.\n" + 
		"Use 'help' at any point during the game to see these instructions again.\n"; 
		return instructions;
	}
	else if(currentCommand[0] == "quit"){
        playerHasDied();
		return "Good-bye!"; 
	}
	return "Sorry, I don't understand.";
}


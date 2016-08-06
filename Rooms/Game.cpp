#include "Game.hpp"

string Game::getRoomStatus(){
	string result = "\n";
	const vector<Room *> * connectedRooms;
	connectedRooms = currentRoom->getCurrentRooms();
	
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	
	vector<Room *>::const_iterator roomIt;
	result += "You can go to these rooms: ";

	for(roomIt = connectedRooms->begin(); roomIt != connectedRooms->end(); ++roomIt){
		if((*roomIt)->getRoomName() != "0"){
			result += (*roomIt)->getRoomName() + ", ";
		}
	}

	result = result.substr(0, result.length() - 2);
	result += "\n";
	
	vector<Item *>::const_iterator itemIt;
	result += "You can grab or inspect these items: ";
	
	for(itemIt = itemsInRoom->begin(); itemIt != itemsInRoom->end(); ++itemIt){
		if((*itemIt)->isVisible())
			result += (*itemIt)->getItemName() + ", ";
	}
	
	result = result.substr(0, result.length() - 2);

	return result;
}
		
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
	
		result.roomDescription += getRoomStatus();

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
			if(currentRoom->getFirstActiveEvent()->getEventName() == "Alien attack!"){
				if(input == "flash with flashlight"){
					vector<Item *>::const_iterator itemIt;
					bool hasFlash = false;
					for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
						if((*itemIt)->getItemName() == "flashlight") hasFlash = true;
					}
			        if(!hasFlash){
						match = true;
						results.push_back( "You don't have a flashlight!"  );
						results.push_back( "nothing" );
					} else {
						match = true;
						results = currentRoom->getFirstActiveEvent()->processEvent(input);
						if(results[1] == "playerdied"){
							playerHasDied();
						} else if(results[1] == "continue"){
							currentRoom->getFirstActiveEvent()->changeStatus();
						}
					}
				} else {
					match = true;
					results = currentRoom->getFirstActiveEvent()->processEvent(input);
					if(results[1] == "playerdied"){
						playerHasDied();
					} else if(results[1] == "continue"){
						currentRoom->getFirstActiveEvent()->changeStatus();
					}
				}
			}
			else if(currentRoom->getFirstActiveEvent()->getEventName() == "Retracted Ladder"){
				if(input == "turn off gravity"){
					vector<Item *>::const_iterator itemIt;
					bool hasKeys = false;
					for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
						if((*itemIt)->getItemName() == "captain's keys") hasKeys = true;
					}
			        if(!hasKeys){
						match = true;
						results.push_back( "You need the captain's keys to do that."  );
						results.push_back( "nothing" );
					} else {
						match = true;
						results = currentRoom->getFirstActiveEvent()->processEvent(input);
						if(results[1] == "playerdied"){
							playerHasDied();
						} else if(results[1] == "continue"){
							currentRoom->getFirstActiveEvent()->changeStatus();
						}
					}
				}
				else if(input == "leave room"){
					go("Equipment Room");
					match = true;
					results.push_back("Going back to the Equipment Room.");
					results.push_back("nothing");
				}
				else {
					match = true;
					results = currentRoom->getFirstActiveEvent()->processEvent(input);
					if(results[1] == "playerdied"){
						playerHasDied();
					} else if(results[1] == "continue"){
						currentRoom->getFirstActiveEvent()->changeStatus();
					}
				}
			}
			else if(currentRoom->getFirstActiveEvent()->getEventName() == "Flying Through the Tube"){
				if(input == "go through tube"){
					vector<Item *>::const_iterator itemIt;
			        if(spaceSuitIsRepaired && helmestIsRepaired){
						match = true;
						results = currentRoom->getFirstActiveEvent()->processEvent(input);
						if(results[1] == "playerdied"){
							playerHasDied();
						} else if(results[1] == "continue"){
							currentRoom->getFirstActiveEvent()->changeStatus();
						}
					}
					else {
						match = true;
						if(!helmestIsRepaired && !spaceSuitIsRepaired){
							results.push_back("Oh no! You should have pateched your suit and helmet! Your protective gear can't withstand the vacuum!");
							results.push_back("playdied");
						}
						else if(!helmestIsRepaired){
							results.push_back("You might have thought you could just hold your breath, but the cold of space and the cloud of metal flakes has other ideas. At least death in space is cooler than a car accident.");
							results.push_back("playdied");
						} else {
							results.push_back("You might have thought you wouldn't need a space suit, but the cold of space and the cloud of metal flakes has other ideas. At least death in space is cooler than a car accident.");
							results.push_back("playdied");
						}
						playerHasDied();
					}
				}
				else if(input == "leave room"){
					vector<Room *>::iterator roomIt = rooms.begin();
					for(; roomIt != rooms.end(); roomIt++){
						if((*roomIt)->getRoomName() == "Entrance to Connection Tube"){
							currentRoom = (*roomIt);
						}
					}
					match = true;
					results.push_back("Going back to the Entrance to Connection Tube.");
					results.push_back("nothing");
				}
			}

			else {
				match = true;
				results = currentRoom->getFirstActiveEvent()->processEvent(input);
				if(results[1] == "playerdied"){
					playerHasDied();
				} else if(results[1] == "continue"){
					currentRoom->getFirstActiveEvent()->changeStatus();
				}
			}
        }
    }
    if(!match){
        results.push_back( "Sorry, I don't understand: " + input );
		results.push_back( "nothing" );
    }
    return results;
}

//Searches vector of connected rooms and sets currentRoom to be
//pointer to that room or displays error message
string Game::go(string location){
	vector<Room *>::const_iterator roomIt;
	//Room * checkRoom = currentRoom;
	if(location != "0"){
		for(roomIt = currentRoom->getCurrentRooms()->begin(); roomIt != currentRoom->getCurrentRooms()->end(); ++roomIt){
			string roomName = (*roomIt)->getRoomName();
			if(location == roomName){
				currentRoom = (*roomIt);
				return "ok";
			}
		}
	}
    return "Sorry, that room cannot be reached from here.";
}

string Game::open(string item){
	string result = "";

	vector<Item *>::const_iterator roomItems;
	
	for(roomItems = currentRoom->getCurrentItems()->begin(); roomItems != currentRoom->getCurrentItems()->end(); roomItems++){
		if((*roomItems)->getItemName() == item){
			if((*roomItems)->getHeldItem() != NULL){
				result = "The " + item + " contains a " + (*roomItems)->getHeldItem()->getItemName() + ", which is now visible.";
				(*roomItems)->getHeldItem()->makeVisible();
			}		
		}
	}
	
	if(result == ""){
		result = "Can't open " + item + ".";
	}
	return result;
}

string Game::fly(string item){
	string result = "";
	if(!navigationSystemInstalled)
		return "You need to install the navigation system before you can fly the escape pod.";

	vector<Item *>::const_iterator roomItems;
	
	for(roomItems = currentRoom->getCurrentItems()->begin(); roomItems != currentRoom->getCurrentItems()->end(); roomItems++){
		if((*roomItems)->getItemName() == item){
			if(item == "escape pod"){
				result = "You have successfully escaped! Congratulations!";
				playerHasDied();
			}
		}
	}
	
	if(result == ""){
		result = "Can't fly " + item + ".";
	}
	return result;
}

string Game::lookAt(string item){
    string result = "";
	vector<Item *>::const_iterator roomItems;
	for(roomItems = currentRoom->getCurrentItems()->begin(); roomItems != currentRoom->getCurrentItems()->end(); roomItems++){
		if((*roomItems)->getItemName() == item){
			result = (*roomItems)->getItemDescription();
			
		}
	}
	if(result == "") result = "Sorry, there is no " + item + " here.";
	return result;
}

//Lists all the items that can be picked up and
//the connected rooms
string Game::look(){
	string result = "";
	result =  currentRoom->getLongDescription();
	result += getRoomStatus();

	return result;


	/*
    string result = "";
	
	const vector<Room *> * connectedRooms;
	connectedRooms = currentRoom->getCurrentRooms();
	
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	
	vector<Room *>::const_iterator roomIt;
	result += "You can go to these rooms: ";

	for(roomIt = connectedRooms->begin(); roomIt != connectedRooms->end(); ++roomIt){
		if((*roomIt)->getRoomName() != "0"){
			result += (*roomIt)->getRoomName() + ", ";
		}
	}

	result = result.substr(0, result.length() - 2);
	result += "\n";
	
	vector<Item *>::const_iterator itemIt;
	result += "You can grab or inspect these items: ";
	
	for(itemIt = itemsInRoom->begin(); itemIt != itemsInRoom->end(); ++itemIt){
		if((*itemIt)->isVisible())
			result += (*itemIt)->getItemName() + ", ";
	}
	
	result = result.substr(0, result.length() - 2);
    
	return result;*/
}

//Picks up an item, which means the item is added to the items vector
//held by the player and removes the pointer from the room's items vector
string Game::grab(string item){
	item = itemAlias(item);
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	vector<Item *>::const_iterator itemIt;
	bool itemFound = false;
    string result = "";
	for(itemIt = itemsInRoom->begin(); itemIt != itemsInRoom->end(); ++itemIt){
		string itemName = (*itemIt)->getItemName();
		if(itemName == item){
			if((*itemIt)->getCanGrab()){
				
				vector<Item *>::const_iterator removeIt;
				for(removeIt = itemsInRoom->begin(); removeIt != itemsInRoom->end(); removeIt++){
					if((*removeIt)->getHeldItem() != NULL){
						cout << (*removeIt)->getHeldItem()->getItemName() << endl;
						if((*removeIt)->getHeldItem()->getItemName() == item){
							(*removeIt)->removeHeldItem();
						}
					}
				}
				
				string itemName = (*itemIt)->getItemName();
				string itemDesc = (*itemIt)->getItemDescription();
				bool canGrab = true;
				bool isVisible = true;
				Item * newItem = new Item(itemName, itemDesc, canGrab, isVisible);
				player.addItem(newItem);
				currentRoom->removeItem((*itemIt));

				result =  "You have picked up " + newItem->getItemName();
			} else {
				result = "Sorry, you can't pick up " + item;
			}
			itemFound = true;
			return result;
		}
	}
	if(!itemFound){
		result = "Sorry that item is not in this room.";
	}
    return result;
}

string Game::drop(string item){
	item = itemAlias(item);
	vector<Item *>::const_iterator itemIt;
	bool itemFound = false;
	string result = "";

	for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
		if((*itemIt)->getItemName() == item){
			currentRoom->addItem((*itemIt));
			player.removeItem((*itemIt));
			itemFound = true;
			break;
		}
	}

	if(itemFound){
		result =  "You have dropped up " + item;
	} else {
		result = "Sorry, you don't have the " + item + ", so you can't drop it.";
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

string Game::itemAlias(string input){
    string output = "";
    for(unsigned int i = 0; i < input.length(); i++){
        output += tolower(input[i]);
    }
    if(output.substr(0, 3) == "fla") output = "flashlight";
    if(output.substr(0, 3) == "spa") output = "space suit";
	if(output.substr(0, 3) == "bat") output = "battery pack";
    if(output.substr(0, 3) == "hel") output = "helmet";
    if(output.substr(0, 3) == "cap") output = "captain's keys";
    if(output.substr(0, 3) == "duc") output = "duct tape";
    if(output.substr(0, 3) == "tub") output = "tube";
    if(output.substr(0, 3) == "nav") output = "navigation system";
    if(output.substr(0, 3) == "dra") output = "drawers";
    if(output.substr(0, 3) == "wal") output = "walls";
    if(output.substr(0, 3) == "foo") output = "food box";
    if(output.substr(0, 3) == "cab") output = "cabinet";
    if(output.substr(0, 3) == "per") output = "personal locker";
    if(output.substr(0, 3) == "ser") output = "service locker";
    if(output.substr(0, 3) == "mir") output = "mirror";
    if(output.substr(0, 3) == "woo") output = "wooden desk";
    if(output.substr(0, 3) == "clo") output = "clothes closet";
    if(output.substr(0, 3) == "sho") output = "showers";
    if(output.substr(0, 3) == "sui") output = "suit locker";
    if(output.substr(0, 3) == "sta") output = "station map";
    if(output.substr(0, 3) == "con") output = "connection tube window";
	if(output.substr(0, 3) == "bre") output = "breach warning";
	if(output.substr(0, 3) == "bac") output = "bacon";
	if(output.substr(0, 3) == "com") output = "computer room door";
	if(output.substr(0, 3) == "eng") output = "engine room door";
	if(output.substr(0, 3) == "ter") output = "terminal for computer";
	if(output.substr(0, 3) == "slo") output = "slot for battery";
	if(output.substr(0, 3) == "eme") output = "emergency battery locker";
	if(output.substr(0, 3) == "fus") output = "fusion engine";
	if(output.substr(0, 3) == "tre") output = "treadmill";
	if(output.substr(0, 3) == "fre") output = "freeweights locker";
	if(output.substr(0, 3) == "dum") output = "dumbbell";
	if(output.substr(0, 3) == "not") output = "notes";
	if(output.substr(0, 3) == "ele") output = "electron microscope";
	if(output.substr(0, 3) == "cle") output = "cleaning supply closet";
	if(output.substr(0, 3) == "mop") output = "mop sink";
	if(output.substr(0, 3) == "wea") output = "weapons locker";
	if(output.substr(0, 3) == "laz") output = "lazer rifle guidebook";
	if(output.substr(0, 3) == "win") output = "window";
	if(output.substr(0, 3) == "esc") output = "escape pod";

    return output;
}


string Game::roomAlias(string input){
    string output = "";
    for(unsigned int i = 0; i < input.length(); i++){
        output += tolower(input[i]);
    }
    if(output.substr(0, 3) == "kit") output = "Kitchen";
    if(output.substr(0, 3) == "bri") output = "Bridge";
    if(output.substr(0, 3) == "sle"){
        if(output[output.length() - 1] == '1')
            return "Sleeping Quarters 1";
        else
            return "Sleeping Quarters 2";
    }
    if(output.substr(0, 3) == "equ") output = "Equipment Room";
    if(output.substr(0, 3) == "con") output = "Connection Tube";
    if(output.substr(0, 3) == "eng") output = "Engine Room";
    if(output.substr(0, 3) == "tra") output = "Training Room";
    if(output.substr(0, 3) == "sci") output = "Science Lab";
    if(output.substr(0, 3) == "sto") output = "Storage Room";
    if(output.substr(0, 3) == "wea") output = "Weapons Room";
    if(output.substr(0, 3) == "com") output = "Computer Room";
    if(output.substr(0, 3) == "loc") output = "Locker Room";
    if(output.substr(0, 3) == "esc") output = "Escape Pods";
    if(output.substr(0, 3) == "com") output = "Computer Room";
    if(output.substr(0, 3) == "obs") output = "Observatory";
    if(output.substr(0, 3) == "ent") output = "Entrance to Connection Tube";

    return output;
}

string Game::install(string item1, string item2){
	if(item1 == "navigation system" && item2 == "escape pod"){
		bool hasEscapePod = false;
		bool hasNavSystem = false;
		vector<Item *>::const_iterator itemIt;
		for(itemIt = currentRoom->getCurrentItems()->begin(); itemIt != currentRoom->getCurrentItems()->end(); itemIt++){
			if((*itemIt)->getItemName() == "escape pod") hasEscapePod = true;
		}
		if(!hasEscapePod) return "There is no escape pod to insert the battery into!";
		vector<Item *>::const_iterator itemIt2;
		for(itemIt2 = player.getCurrentItems()->begin(); itemIt2 != player.getCurrentItems()->end(); itemIt2++){
			if((*itemIt2)->getItemName() == "navigation system"){
				hasNavSystem = true;
				break;
			}
		}
		if(!hasNavSystem) return "You should probably find the battery pack before you try to use it...";
		player.removeItem((*itemIt2));
		navigationSystemInstalled = true;
		return "The navigation system is installed. Now you can fly out of here!!";
	} 
	else {
		return "I don't think that fits in there the way you think it does...";
	}
}
string Game::insert(string item1, string item2){
	if(item1 == "battery pack" && item2 == "slot for battery"){
		bool hasBatterySlot = false;
		bool hasBatteryPack = false;
		vector<Item *>::const_iterator itemIt;
		for(itemIt = currentRoom->getCurrentItems()->begin(); itemIt != currentRoom->getCurrentItems()->end(); itemIt++){
			if((*itemIt)->getItemName() == "slot for battery") hasBatterySlot = true;
		}
		if(!hasBatterySlot) return "There is no slot to insert the battery into!";
		vector<Item *>::const_iterator itemIt2;
		for(itemIt2 = player.getCurrentItems()->begin(); itemIt2 != player.getCurrentItems()->end(); itemIt2++){
			if((*itemIt2)->getItemName() == "battery pack"){
				hasBatteryPack = true;
				break;
			}
		}
		if(!hasBatteryPack) return "You should probably find the battery pack before you try to use it...";
		player.removeItem((*itemIt2));
		for(itemIt2 = currentRoom->getCurrentItems()->begin(); itemIt2 != currentRoom->getCurrentItems()->end(); itemIt2++){
			if((*itemIt2)->getItemName() == "navigation system"){
				(*itemIt2)->makeVisible();
				break;
			}
		}
		//(*itemIt)->setItemDescription("The computer is running now thanks to the battery pack.");
		return "The computer terminal is on! Now you can grab the navigation system!";
	} else if(item1 == "tube" && item2 == "space suit"){
		bool hasSpaceSuit = false;
		bool hasTube = false;
		vector<Item *>::const_iterator itemIt;
		for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
			if((*itemIt)->getItemName() == "space suit") hasSpaceSuit = true;
		}
		if(!hasSpaceSuit) return "You don't even have a space suit yet!";
		vector<Item *>::const_iterator itemIt2;
		for(itemIt2 = player.getCurrentItems()->begin(); itemIt2 != player.getCurrentItems()->end(); itemIt2++){
			if((*itemIt2)->getItemName() == "tube"){
				hasTube = true;
				break;
			}
		}
		if(!hasTube) return "Maybe you should try finding a tube first.";
		player.removeItem((*itemIt2));
		spaceSuitIsRepaired = true;
		return "You've fixed the space suit!";
	} 
	else {
		return "I don't think that fits in there the way you think it does...";
	}
}

string Game::patch(string item1, string item2){
	cout << item1 << " " << item2 << endl;
	if(item1 == "helmet" && item2 == "duct tape"){
		bool hasHelmet = false;
		bool hasDuctTape = false;
		vector<Item *>::const_iterator itemIt;
		for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
			if((*itemIt)->getItemName() == "helmet") hasHelmet = true;
		}
		if(!hasHelmet) return "You should probably try finding the helmet first!";
		vector<Item *>::const_iterator itemIt2;
		for(itemIt2 = player.getCurrentItems()->begin(); itemIt2 != player.getCurrentItems()->end(); itemIt2++){
			if((*itemIt2)->getItemName() == "duct tape"){
				hasDuctTape = true;
				break;
			}
		}
		if(!hasDuctTape) return "You don't even have the duct tape yet!";
		helmestIsRepaired = true;
		player.removeItem((*itemIt2));
		return "You have patched your helmet with the duct tape..";
	} else {
		return "Well, that was a nice try, but it didn't do anything.";
	}
}

string Game::hit(string item1, string item2){
	if(item1 == "emergency battery locker" && item2 == "dumbbell"){
		bool hasLocker = false;
		bool hasDumbbell = false;
		vector<Item *>::const_iterator itemIt;
		for(itemIt = currentRoom->getCurrentItems()->begin(); itemIt != currentRoom->getCurrentItems()->end(); itemIt++){
			if((*itemIt)->getItemName() == "emergency battery locker") hasLocker = true;
		}
		if(!hasLocker) return "There is no emergency battery locker to hit!";
		vector<Item *>::const_iterator itemIt2;
		for(itemIt2 = player.getCurrentItems()->begin(); itemIt2 != player.getCurrentItems()->end(); itemIt2++){
			if((*itemIt2)->getItemName() == "dumbbell"){
				hasDumbbell = true;
				break;
			}
		}
		if(!hasDumbbell) return "That didn't do anything. You need something heavy and sturdy.";
		(*itemIt2)->makeVisible();
		//(*itemIt)->setItemDescription("The emergency battery locker is open.");
		return "The emergency battery locker is open! Now you can grab a battery pack.";
	} else {
		return "Well, that's not going to do anything.";
	}
}

//Uses currentCommand calls appropriate function matching command
string Game::processPlayerInput(string input){

    inputToVector(input);

	if(currentCommand[0] ==  "go"){
		if(currentCommand.size() > 1){
			string location = "";
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				location += currentCommand[i] + " ";
			}
			location = location.substr(0, location.length() - 1);
			location = roomAlias(location);
			return go(location);
		}
	} else if (currentCommand[0] == "go"){
		return "Where do you want to go?";
	}
	else if(currentCommand[0] == "look"){
	   	if(currentCommand.size() > 1){
		   	if(currentCommand[1] == "at"){
				string item = "";
				for(unsigned int i = 2; i < currentCommand.size(); i++){
					item += currentCommand[i] + " ";
				}
				item = item.substr(0, item.length() - 1);
				item = itemAlias(item);
				return lookAt(item);
			}
		}
		else return look();
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
	else if(currentCommand[0] == "drop"){	
		if(currentCommand.size() > 1){
			string item = "";
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				item += currentCommand[i] + " ";
			}
			item = item.substr(0, item.length() - 1);
			item = itemAlias(item);
			return drop(item);
		} else {
			return "What would you like to drop?";
		}
	}
	else if(currentCommand[0] == "check"){
		return checkItemsInHand();
	}
	else if(currentCommand[0] == "eat"){
		if(currentCommand.size() > 0){
			if(currentCommand[1] != "bacon"){
				return "You cant' eat that!";
			} else {
				playerHasDied();
				return "Oh, no, it was covered with alien acid goo! It's burning the inside of your stomach! Oh, why did you eat the bacon?!";
			}
		} else {
			return "What would you like to eat?";
		}

	}
	else if(currentCommand[0] == "open"){
		if(currentCommand.size() > 1){
			string item = "";
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				item += currentCommand[i] + " ";
			}
			item = item.substr(0, item.length() - 1);
			item = itemAlias(item);
			return open(item);
		} else {
			return "What would you like to open?";
		}
	}
	else if(currentCommand[0] == "fly"){
		if(currentCommand.size() > 1){
			string item = "";
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				item += currentCommand[i] + " ";
			}
			item = item.substr(0, item.length() - 1);
			item = itemAlias(item);
			return fly(item);
		} else {
			return "What would you like to fly?";
		}
	}
	else if(currentCommand[0] == "hit"){
		if(currentCommand.size() > 3){
			string item1 = "";
			string item2 = "";
			int withPos = 0;
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				if(currentCommand[i] == "with"){
					withPos = i;
					break;
				}
				item1 += currentCommand[i] + " ";
			}
			item1 = item1.substr(0, item1.length() - 1);
			item1 = itemAlias(item1);
			
			for(unsigned int i = withPos + 1; i < currentCommand.size(); i++){
				item2 += currentCommand[i] + " ";
			}
			item2 = item2.substr(0, item2.length() - 1);
			item2 = itemAlias(item2);

			return hit(item1, item2);
		} else {
			return "What would you like to hit and what would you like to hit it with?";
		}
	} else if(currentCommand[0] == "patch"){
		if(currentCommand.size() > 3){
			string item1 = "";
			string item2 = "";
			int withPos = 0;
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				if(currentCommand[i] == "with"){
					withPos = i;
					break;
				}
				item1 += currentCommand[i] + " ";
			}
			item1 = item1.substr(0, item1.length() - 1);
			item1 = itemAlias(item1);
			
			for(unsigned int i = withPos + 1; i < currentCommand.size(); i++){
				item2 += currentCommand[i] + " ";
			}
			item2 = item2.substr(0, item2.length() - 1);
			item2 = itemAlias(item2);

			return patch(item1, item2);
		} else {
			return "What would you like to patch and what would you like to patch it with?";
		}
	}
	else if(currentCommand[0] == "insert"){
		if(currentCommand.size() > 3){
			string item1 = "";
			string item2 = "";
			int intoPos = 0;
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				if(currentCommand[i] == "into"){
					intoPos = i;
					break;
				}
				item1 += currentCommand[i] + " ";
			}
			item1 = item1.substr(0, item1.length() - 1);
			item1 = itemAlias(item1);
			
			for(unsigned int i = intoPos + 1; i < currentCommand.size(); i++){
				item2 += currentCommand[i] + " ";
			}
			item2 = item2.substr(0, item2.length() - 1);
			item2 = itemAlias(item2);

			return insert(item1, item2);
		} else {
			return "What would you like to insert into what?";
		}
	}
	else if(currentCommand[0] == "install"){
		if(currentCommand.size() > 3){
			string item1 = "";
			string item2 = "";
			int intoPos = 0;
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				if(currentCommand[i] == "into"){
					intoPos = i;
					break;
				}
				item1 += currentCommand[i] + " ";
			}
			item1 = item1.substr(0, item1.length() - 1);
			item1 = itemAlias(item1);
			
			for(unsigned int i = intoPos + 1; i < currentCommand.size(); i++){
				item2 += currentCommand[i] + " ";
			}
			item2 = item2.substr(0, item2.length() - 1);
			item2 = itemAlias(item2);

			return install(item1, item2);
		} else {
			return "What would you like to insert into what?";
		}
	}
	else if(currentCommand[0] == "help") {
		string instructions = "Use 'go to [exact room name]' to move to another room.\n"; 
		instructions += "Use 'look' to see what items are in a room and what the connected rooms are.\n"; 
		instructions += "Use 'grab [exact item name]' to pick up an item.\n";
		instructions += "Use 'quit' to exit. (Will not work when responding to an event.\n";
		instructions += "Use 'help' at any point during the game to see these instructions again.\n"; 
		return instructions;
	}
	else if(currentCommand[0] == "quit"){
        playerHasDied();
		return "Good-bye!"; 
	}
	return "Sorry, I don't understand.";
}


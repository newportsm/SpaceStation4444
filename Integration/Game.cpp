#include "Game.hpp"

string Game::getRoomStatus(){
	string result = "\n";
	const vector<Room *> * connectedRooms;
	connectedRooms = currentRoom->getCurrentRooms();
	
	const vector<Item *> * itemsInRoom;
	itemsInRoom = currentRoom->getCurrentItems();
	
	vector<Room *>::const_iterator roomIt;
	result += "You can go";

	int count = 0;
	int skip = 0;

	for(roomIt = connectedRooms->begin(); roomIt != connectedRooms->end(); ++roomIt){
		if((*roomIt)->getRoomName() != "0"){
			if(count == 0) 
				result += " counter-clockwise to " + (*roomIt)->getRoomName(); 
			if(count == 1 && !skip)
				result += " or clockwise to " + (*roomIt)->getRoomName();
			if(count == 1 && skip)
				result += " clockwise to " + (*roomIt)->getRoomName();
		} else {
			skip = true;
		}
		count++;
	}

	result += ".\n";
	
	vector<Item *>::const_iterator itemIt;
	result += "You can grab or look at these items: ";
	
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
		result.eventDescription = "";
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
	input = eventAlias(input);
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
			else if(currentRoom->getFirstActiveEvent()->getEventName() == "Sleeping alien!"){
				if(input == "burn it"){
					vector<Item *>::const_iterator itemIt;
					bool hasFlamethrower = false;
					for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
						if((*itemIt)->getItemName() == "flamethrower") hasFlamethrower = true;
					}
			        if(!hasFlamethrower){
						match = true;
						results.push_back( "You don't have anything to burn it with!"  );
						results.push_back( "nothing" );
					} else {
						match = true;
						results.push_back( "\"Hey, punk, do you feel lucky?!\" you shout at the alien as you pull the trigger on the flamethrower. Screeching, the giant creature scampers away.");
						results.push_back("continue");
						currentRoom->getFirstActiveEvent()->changeStatus();
					}
				} else if (input == "run away"){
					match = true;
					results = currentRoom->getFirstActiveEvent()->processEvent(input);
					vector<Room *>::const_iterator roomIt;
					for(roomIt = rooms.begin(); roomIt != rooms.end(); roomIt++){
						if((*roomIt)->getRoomName() == "Storage Room"){
							currentRoom = (*roomIt);
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
				if(input == "lower ladder"){
					vector<Item *>::const_iterator itemIt;
					bool hasKeys = false;
					for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
						if((*itemIt)->getItemName() == "captain's keys"){
							hasKeys = true;
							break;
						}
					}
			        if(!hasKeys){
						match = true;
						results.push_back( "You need the captain's keys to do that."  );
						results.push_back( "nothing" );
					} else {
						player.removeItem((*itemIt));
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
			        if(spaceSuitIsPatched && spaceSuitIsRepaired && helmestIsRepaired){
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
		string error = "Sorry, I don't understand: " + input + "\nEvent options: ";
		vector<string>::const_iterator opts;
		for(opts = currentRoom->getFirstActiveEvent()->getEventOptions()->begin(); opts != currentRoom->getFirstActiveEvent()->getEventOptions()->end(); opts++){
			error = error + (*opts) + ", ";
		}
		error = error.substr(0, error.length() - 2);
        results.push_back( error );
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
	string error = "Sorry, that room cannot be reached from here.\nRooms you can reach: ";
	vector<Room *>::const_iterator roomOpts;
	for(roomOpts = currentRoom->getCurrentRooms()->begin(); roomOpts != currentRoom->getCurrentRooms()->end(); roomOpts++){
		if((*roomOpts)->getRoomName() != "0")
			error = error + (*roomOpts)->getRoomName() + ", ";
	}

	error = error.substr(0, error.length() - 2);

	return error;
}

string Game::open(string item){
	string result = "";

	vector<Item *>::const_iterator roomItems;
	
	for(roomItems = currentRoom->getCurrentItems()->begin(); roomItems != currentRoom->getCurrentItems()->end(); roomItems++){
		if((*roomItems)->getItemName() == "weapons locker"){		
			const vector<Item *> * items = player.getCurrentItems();
			vector<Item *>::const_iterator itemIt;
			string results = "";
			for(itemIt = items->begin(); itemIt != items->end(); ++itemIt){
				if((*itemIt)->getItemName() == "wire"){
					(*roomItems)->getHeldItem()->makeVisible();
					result = "The " + item + " contains a " + (*roomItems)->getHeldItem()->getItemName() + ", which is now visible. Unfortunately, all of the other weapons are lacking battery power.";
					(*roomItems)->setItemDescription("You've taken the only weapon worth taking already!");
				}
			}
			if(result == ""){
				result = "You'll need to find something to pick the lock with before you can open this.";
			}
		}
		else if((*roomItems)->getItemName() == item){
			if((*roomItems)->getHeldItem() != NULL){
				result = "The " + item + " contains a " + (*roomItems)->getHeldItem()->getItemName() + ", which is now visible.";
				(*roomItems)->getHeldItem()->makeVisible();
			}		
		}
	}
	
	if(result == ""){
		result = "There's nothing inside " + item + ".";
	}
	return result;
}

string Game::fly(string item){
	string result = "";
	if(item == "escape pod" && !navigationSystemInstalled)
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
		result = "What? You can't fly " + item + ".";
	}
	return result;
}

string Game::lookAt(string item){
    string result = "";
	vector<Item *>::const_iterator roomItems;
	for(roomItems = currentRoom->getCurrentItems()->begin(); roomItems != currentRoom->getCurrentItems()->end(); roomItems++){
		if((*roomItems)->getItemName() == item){
			result = (*roomItems)->getItemName() + ": " + (*roomItems)->getItemDescription();
			
		}
	}
	if(result == "") result = "Sorry, there is no " + item + " here.";
	return result;
}

//Lists all the items that can be picked up and
//the connected rooms
string Game::look(){
	string result = "";
	result = currentRoom->getRoomName() + "\n";
	result +=  currentRoom->getLongDescription();
	result += getRoomStatus();

	return result;
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
			if((*itemIt)->getCanGrab() && (*itemIt)->isVisible()){
				
				vector<Item *>::const_iterator removeIt;
				for(removeIt = itemsInRoom->begin(); removeIt != itemsInRoom->end(); removeIt++){
					if((*removeIt)->getHeldItem() != NULL){
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

				result =  "You have picked up the " + newItem->getItemName() + ".";
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
	if(player.getCurrentItems()->size() > 0){
		const vector<Item *> * items = player.getCurrentItems();
		vector<Item *>::const_iterator itemIt;
		string results = "";
		results =  "You currently are holding: ";
		for(itemIt = items->begin(); itemIt != items->end(); ++itemIt){
			results += (*itemIt)->getItemName() + ", ";
		}

		results = results.substr(0, results.length() - 2);
		results += ".";
		return results;
	} else {
		return "You are not currently holding any items.";
	}
}

string Game::itemAlias(string input){
    string output = "";
    for(unsigned int i = 0; i < input.length(); i++){
        output += tolower(input[i]);
    }
	
	if(output.substr(0, 4) == "flam") output = "flamethrower";
    if(output.substr(0, 4) == "flas") output = "flashlight";
    if(output.substr(0, 3) == "spa") output = "space suit";
	if(output.substr(0, 3) == "bat") output = "battery pack";
    if(output.substr(0, 3) == "hel") output = "helmet";
    if(output.substr(0, 3) == "cap") output = "captain's keys";
    if(output.substr(0, 3) == "duc") output = "duct tape";
    if(output.substr(0, 3) == "tap") output = "duct tape";
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
	if(output.substr(0, 3) == "tel") output = "telescope";
	if(output.substr(0, 3) == "deb") output = "debris field chart";
	if(output.substr(0, 3) == "wir") output = "wire";

    return output;
}

string Game::eventAlias(string input){
    string output = "";
    for(unsigned int i = 0; i < input.length(); i++){
        output += tolower(input[i]);
    }
    if(output.substr(0, 3) == "fla") output = "flash with flashlight";
    if(output.substr(0, 3) == "pun") output = "punch it";
    if(output.substr(0, 3) == "run") output = "run away";
    if(output.substr(0, 3) == "lea") output = "leave room";
    if(output.substr(0, 3) == "go ") output = "go through tube";
    if(output.substr(0, 3) == "got") output = "go through tube";
    if(output.substr(0, 3) == "jum") output = "jump for tube door";
    if(output.substr(0, 3) == "bui") output = "build ladder";
    if(output.substr(0, 3) == "low") output = "lower ladder";

	return output;
}

string Game::roomAlias(string input){
    string output = "";
    for(unsigned int i = 0; i < input.length(); i++){
        output += tolower(input[i]);
    }
    if(output.substr(0, 3) == "kit") output = "Kitchen";
    else if(output.substr(0, 3) == "bri") output = "Bridge";
    else if(output.substr(0, 3) == "sle"){
        if(output[output.length() - 1] == '1')
            return "Sleeping Quarters 1";
        else
            return "Sleeping Quarters 2";
    }
    else if(output.substr(0, 3) == "equ") output = "Equipment Room";
    else if(output.substr(0, 3) == "con") output = "Connection Tube";
	else if(output.substr(0, 3) == "eng") output = "Engine Room";
	else if(output.substr(0, 3) == "tra") output = "Training Room";
	else if(output.substr(0, 3) == "sci") output = "Science Lab";
	else if(output.substr(0, 3) == "sto") output = "Storage Room";
	else if(output.substr(0, 3) == "wea") output = "Weapons Room";
	else if(output.substr(0, 3) == "com") output = "Computer Room";
	else if(output.substr(0, 3) == "loc") output = "Locker Room";
	else if(output.substr(0, 3) == "esc") output = "Escape Pods";
	else if(output.substr(0, 3) == "com") output = "Computer Room";
	else if(output.substr(0, 3) == "obs") output = "Observatory";
	else if(output.substr(0, 3) == "ent") output = "Entrance to Connection Tube";
	else if(output.substr(0, 3) == "clo") output = "clockwise";
	else if(output.substr(0, 3) == "cou") output = "counter-clockwise";
	else output = "nope";

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
		if(spaceSuitIsPatched && spaceSuitIsRepaired){
		   	string rep = "Space suit can now be used in space!";
			vector<Item *>::const_iterator itemIt3;
			for(itemIt3 = player.getCurrentItems()->begin(); itemIt3 != player.getCurrentItems()->end(); itemIt3++){
				if((*itemIt3)->getItemName() == "space suit") (*itemIt3)->setItemDescription(rep);
			}
		} else {
		   	string rep = "Your space suit still has holes in it.";
			vector<Item *>::const_iterator itemIt3;
			for(itemIt3 = player.getCurrentItems()->begin(); itemIt3 != player.getCurrentItems()->end(); itemIt3++){
				if((*itemIt3)->getItemName() == "space suit") (*itemIt3)->setItemDescription(rep);
			}
		}

		return "You've fixed the space suit!";
	} 
	else {
		return "I don't think that fits in there the way you think it does...";
	}
}

string Game::patch(string item1, string item2){
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
		string rep = "Helmet can now be used in space!";
		helmestIsRepaired = true;
		vector<Item *>::const_iterator itemIt3;
		for(itemIt3 = player.getCurrentItems()->begin(); itemIt3 != player.getCurrentItems()->end(); itemIt3++){
			if((*itemIt3)->getItemName() == "helmet") (*itemIt3)->setItemDescription(rep);
		}
		return "You have patched your helmet with the duct tape.";
	} 
	if(item1 == "space suit" && item2 == "duct tape"){
		bool hasHelmet = false;
		bool hasDuctTape = false;
		vector<Item *>::const_iterator itemIt;
		for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
			if((*itemIt)->getItemName() == "space suit") hasHelmet = true;
		}
		if(!hasHelmet) return "You should probably try finding the space suit first!";
		vector<Item *>::const_iterator itemIt2;
		for(itemIt2 = player.getCurrentItems()->begin(); itemIt2 != player.getCurrentItems()->end(); itemIt2++){
			if((*itemIt2)->getItemName() == "duct tape"){
				hasDuctTape = true;
				break;
			}
		}
		if(!hasDuctTape) return "You don't even have the duct tape yet!";
		spaceSuitIsPatched = true;
		if(spaceSuitIsPatched && spaceSuitIsRepaired){
			string rep = "Space suit can now be used in space!";
			vector<Item *>::const_iterator itemIt3;
			for(itemIt3 = player.getCurrentItems()->begin(); itemIt3 != player.getCurrentItems()->end(); itemIt3++){
				if((*itemIt3)->getItemName() == "space suit") (*itemIt3)->setItemDescription(rep);
			}
		} else {
			string rep = "Your space suit still needs a tube!";
			vector<Item *>::const_iterator itemIt3;
			for(itemIt3 = player.getCurrentItems()->begin(); itemIt3 != player.getCurrentItems()->end(); itemIt3++){
				if((*itemIt3)->getItemName() == "space suit") (*itemIt3)->setItemDescription(rep);
			}
		}
		return "You have patched your space suit with the duct tape.";
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
		
		if(!hasDumbbell) return "You need to find a dumbbell before you can use it!";
	
		vector<Item *>::const_iterator itemIt3;
		for(itemIt3 = currentRoom->getCurrentItems()->begin(); itemIt3 != currentRoom->getCurrentItems()->end(); itemIt3++){
			if((*itemIt3)->getItemName() == "battery pack") 
				(*itemIt3)->makeVisible();
		}

		vector<Item *>::const_iterator itemIt4;
		for(itemIt4 = currentRoom->getCurrentItems()->begin(); itemIt4 != currentRoom->getCurrentItems()->end(); itemIt4++){
			if((*itemIt4)->getItemName() == "emergency battery locker") 
				(*itemIt4)->setItemDescription("The emergency battery locker is open.");
		}

		return "The emergency battery locker is open! Now you can grab a battery pack.";

	} else {
		return "Well, that's not going to do anything.";
	}
}

string Game::checkItem(string item){
	vector<Item *>::const_iterator itemIt;
	for(itemIt = player.getCurrentItems()->begin(); itemIt != player.getCurrentItems()->end(); itemIt++){
		if(item == (*itemIt)->getItemName()){
			return (*itemIt)->getItemDescription();
		}
	}
	return "Sorry, you currently do not have that item.";
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
			if(location == "clockwise" && currentRoom->getCurrentRooms()->at(1)->getRoomName() != "0")
				location = currentRoom->getCurrentRooms()->at(1)->getRoomName();
			if(location == "counter-clockwise" && currentRoom->getCurrentRooms()->at(0)->getRoomName() != "0")
				location = currentRoom->getCurrentRooms()->at(0)->getRoomName();
			return go(location);
		}
		else
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
		if(currentCommand.size() < 2)
			return checkItemsInHand();
		else {
			string item = "";
			for(unsigned int i = 1; i < currentCommand.size(); i++){
				item += currentCommand[i] + " ";
			}
			item = item.substr(0, item.length() - 1);
			item = itemAlias(item);
			return checkItem(item);
		}
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
		string instructions = "Use 'go [room name]' to move to another room.\n"; 
		instructions += "Use 'look' to get full room description.\n";
		instructions += "Use 'look at [item name]' to get description of something in a room.\n"; 
		instructions += "Use 'check' to get a list of all the items you have picked up.\n"; 
		instructions += "Use 'check [item name]' to get a description of an item you have picked up.\n";	
		instructions += "Use 'open [item name]' top open something and see what's inside.\n";
		instructions += "Use 'grab [item name]' to pick up an item.\n";
		instructions += "Use 'patch [item name] with [item name]' to patch and item.\n";
		instructions += "Use 'insert [item name] into [item name]' to insert one item into another.\n";
		instructions += "Use 'install [item name] into [item name]' to install one item in another.\n";
		instructions += "Use 'fly [item name]' to fly something, like an airplane.\n";
		instructions += "Use 'hit [item name] with [item name]' to hit one item with another.\n";
		instructions += "Use 'quit' to exit. (Will not work when responding to an event.\n";
		instructions += "Use 'help' at any point during the game to see these instructions again.\n"; 
		return instructions;
	}
	else if(currentCommand[0] == "quit"){
        playerHasDied();
		return "Good-bye!"; 
	}
	else {
		string location = "";
		for(unsigned int i = 0; i < currentCommand.size(); i++){
			location += currentCommand[i] + " ";
		}
		location = location.substr(0, location.length() - 1);
		location = roomAlias(location);
		if(location != "nope"){
			if(location == "clockwise" && currentRoom->getCurrentRooms()->at(1)->getRoomName() != "0")
				location = currentRoom->getCurrentRooms()->at(1)->getRoomName();
			if(location == "counter-clockwise" && currentRoom->getCurrentRooms()->at(0)->getRoomName() != "0")
				location = currentRoom->getCurrentRooms()->at(0)->getRoomName();
			
			return go(location);
		} else {
			return "Sorry, I don't understand. You can use \"help\" to see the list of commands available or use \"look\" to look around the room.";
		}
	}
	return "Sorry, I don't understand. You can use \"Help\" to see the list of commands available or use \"look\" to look around the room.";
}


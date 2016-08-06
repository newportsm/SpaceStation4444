#ifndef GAME_HPP
#define GAME_HPP

#include "factories.hpp"
#include "Player.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using std::vector;
using std::string;
using std::cin;

struct currentRoomStrings{
    string roomName;
    string roomDescription;
    bool activeEvent;
    string eventName;
    string eventDescription;
    const vector<string> * currentOptions;
};

class Game{
	private:
		Player player;
		vector<Room *> rooms;
		Room * currentRoom;
		bool playerIsAlive;
		bool suitIsRepaired;
		bool helmestIsRepaired;
		vector<string> currentCommand;
	public:
		Game(){
			loadGame(&rooms);
			currentRoom = rooms[0];
			playerIsAlive = true;
			suitIsRepaired = false;
			helmestIsRepaired = false;
		}
		bool getPlayerStatus(){ return playerIsAlive; }
		void playerHasDied(){ playerIsAlive = false; }
		void inputToVector(string input);
		void printRooms();
		void printCurrentRoom();
		string processPlayerInput(string input);
		string look();
		string go(string location);
		string grab(string item);
		string drop(string item);
		string checkItemsInHand();
		vector<string> respondToEvent(string input);
        currentRoomStrings getCurrentRoomStrings();
        string roomAlias(string input);
		string itemAlias(string input);
		string lookAt(string item);
		string getRoomStatus();
		string open(string item);
		string hit(string item1, string item2);



};


#endif

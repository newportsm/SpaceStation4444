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
		vector<string> currentCommand;
	public:
		Game(){
			loadGame(&rooms);
			currentRoom = rooms[0];
			playerIsAlive = true;
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
		string checkItemsInHand();
		vector<string> respondToEvent(string input);
        currentRoomStrings getCurrentRoomStrings();
};


#endif

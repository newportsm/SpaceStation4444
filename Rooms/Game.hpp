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
		void getPlayerInput();
		void processPlayerInput();
		void look();
		void go(string location);
		void grab(string item);
		void checkItemsInHand();
		void respondToEvent(Event * currentEvent, const vector<string> * currentOptions);

};


#endif

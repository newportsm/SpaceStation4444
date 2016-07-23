#include "Game.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(){

	Game game;

	cout << "Use 'go to [exact room name]' to move to another room." << endl;
	cout << "Use 'look' to see what items are in a room and what the connected rooms are." << endl;
	cout << "Use 'grab [exact item name]' to pick up an item" << endl;
	cout << "Use 'quit' to exit. (Will not work when responding to an event." << endl << endl;

	while(game.getPlayerStatus()){
		game.printCurrentRoom();
	}

	return 0;
}

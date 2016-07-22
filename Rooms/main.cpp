#include "Game.hpp"

int main(){

	Game game;
	//game.printRooms();

	while(game.getPlayerStatus()){
		game.printCurrentRoom();
		game.getPlayerInput();
		game.processPlayerInput();
	}

	return 0;
}

#include "Game.hpp"

int main(){

	Game game;

	while(game.getPlayerStatus()){
		game.printCurrentRoom();
	}

	return 0;
}

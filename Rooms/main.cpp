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
	cout << "Use 'help' at any point during the game to see these instructions again" << endl;

	while(game.getPlayerStatus()){
		//game.printCurrentRoom();
        currentRoomStrings res = game.getCurrentRoomStrings();
        cout << res.roomName << endl;
        cout << res.roomDescription << endl;
        cout << res.eventName << endl;
        cout << res.eventDescription << endl;
        if(res.activeEvent){ 
            cout << res.currentOptions->at(0) << endl;
            vector<string> rez = game.respondToEvent("flash with flashlight");
            cout << rez[0] << " " << rez[1] << endl;
        };
        cout << game.processPlayerInput("look");

        cout << game.processPlayerInput("go to Kitchen");
        cout << game.processPlayerInput("help");
        cout << endl << endl ;
        cout << "Press any key to continue or control + c to quit.";
        cout << endl << endl;
        getchar();
	}

	return 0;
}

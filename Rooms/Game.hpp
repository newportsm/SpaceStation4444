#ifndef GAME_HPP
#define GAME_HPP

#include "factories.hpp"
#include "Player.hpp"

class Game{
	private:
		Player player;
		vector<Room *> rooms;
	public:
		Game(){
			loadGame(&rooms);
		}
		void printRooms(){
			vector<Room *>::const_iterator connIt;
			std::vector<Room *>::const_iterator it;
			for(it = rooms.begin(); it != rooms.end(); ++it){
				cout << (*it)->getRoomName() << ": ";
				connIt = (*it)->getCurrentRooms()->begin();
				for(; connIt != (*it)->getCurrentRooms()->end(); ++connIt){
					cout << (*connIt)->getRoomName() << "   ";
				}
				cout << endl;
			}
		}

};


#endif

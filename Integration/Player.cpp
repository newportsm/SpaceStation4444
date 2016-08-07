#include "Player.hpp"

void Player::removeItem( Item * oldItem){
	vector<Item *>::iterator it;
	for(it = items.begin(); it != items.end(); ++it){
		if(*it == oldItem){
			items.erase(it);
		}
	}

}

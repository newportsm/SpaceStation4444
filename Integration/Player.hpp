#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "Item.hpp"

using std::vector;

class Player{
	private:
		vector<Item *> items;
	public:
		//Player(){}
		const vector<Item *> * getCurrentItems(){ return & items; }
		void addItem( Item * newItem ){ items.push_back(newItem); }
		void removeItem( Item * oldItem){
			vector<Item *>::iterator it;
			for(it = items.begin(); it != items.end(); ++it){
				//std::cout << (*it)->getItemName() << std::endl;
				if(*it == oldItem){
					//delete((*it));
					items.erase(it);
					break;
				}
			}

		}
};

#endif

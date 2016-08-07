#ifndef FACTORIES_HPP
#define FACTORIES_HPP

#include "Room.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;

int roomFactory(vector<Room *> * rooms);
int itemFactory(vector<Room *> * rooms);
int eventFactory(vector<Room *> * rooms);

int loadGame(vector<Room *> * rooms);

#endif

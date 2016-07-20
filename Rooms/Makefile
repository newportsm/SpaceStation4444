Item.o: Item.hpp Item.cpp
	g++ -Wall -std=c++1y -c Item.hpp Item.cpp
Event.o: Event.hpp Event.cpp
	g++ -Wall -std=c++1y -c Event.hpp Event.cpp
Room.o: Room.hpp Room.cpp
	g++ -Wall -std=c++1y -c Room.hpp Room.cpp
factories.o: factories.hpp factories.cpp
	g++ -Wall -std=c++1y -c factories.hpp factories.cpp
Game.o: Event.o Item.o factories.o Room.o Player.hpp
	g++ -Wall -std=c++1y -c Game.hpp Player.hpp
testGame: Event.o Item.o factories.o Room.o Game.o
	g++ -Wall -std=c++1y Event.o Item.o factories.o Room.o main.cpp -o testGame
cleandepend:
	rm *.o *.gch
cleanall:
	rm *.o testGame *.gch

Item.o: Item.hpp Item.cpp
	g++ -std=c++14 -c Item.hpp Item.cpp
Event.o: Event.hpp Event.cpp
	g++ -std=c++14 -c Event.hpp Event.cpp
Room.o: Room.hpp Room.cpp
	g++ -std=c++14 -c Room.hpp Room.cpp
factories.o: factories.hpp factories.cpp
	g++ -std=c++14 -c factories.hpp factories.cpp
Game.o: Event.o Item.o factories.o Room.o Player.hpp
	g++ -std=c++14 -c Game.hpp Player.hpp
testGame: Event.o Item.o factories.o Room.o Game.o
	g++ -std=c++14 Event.o Item.o factories.o Room.o main.cpp -o testGame
cleandepend:
	rm *.o *.gch
cleanall:
	rm *.o testGame *.gch

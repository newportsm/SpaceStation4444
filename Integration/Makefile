Item.o: Item.hpp Item.cpp
	g++ -Wall -std=c++1y -c Item.hpp Item.cpp
Event.o: Event.hpp Event.cpp
	g++ -Wall -std=c++1y -c Event.hpp Event.cpp
Room.o: Room.hpp Room.cpp
	g++ -Wall -std=c++1y -c Room.hpp Room.cpp
factories.o: factories.hpp factories.cpp
	g++ -Wall -std=c++1y -c factories.hpp factories.cpp
Game.o: Event.o Item.o factories.o Room.o Player.hpp Game.hpp Game.cpp
	g++ -Wall -std=c++1y -c Game.hpp Game.cpp Player.hpp
testMain: Event.o Item.o factories.o Room.o Game.o main_integrated.cpp
	g++ -Wall -std=c++1y Event.o Item.o Game.o factories.o Room.o main.cpp -o testGame
testGame: Event.o Item.o factories.o Room.o Game.o main_integrated.cpp
	g++ -Wall -std=c++1y Event.o Item.o Game.o factories.o Room.o main_integrated.cpp -o testGame -lncurses
testGameExp: Event.o Item.o factories.o Room.o Game.o main_integrated_exp.cpp
	g++ -Wall -std=c++1y Event.o Item.o Game.o factories.o Room.o main_integrated_exp.cpp -o testGame -lncurses
SpaceStation4444: Event.o Item.o factories.o Room.o Game.o main_integrated_exp.cpp
	g++ -Wall -std=c++1y Event.o Item.o Game.o factories.o Room.o main_integrated_exp.cpp -o SpaceStation4444 -lncurses

clean:
	rm *.o *.gch SpaceStation4444
cleandepend:
	rm *.o *.gch
cleanall:
	rm *.o testGame *.gch SpaceStation4444

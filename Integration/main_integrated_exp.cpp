#include "Game.hpp"
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <string>


using namespace std;

void strToCstr(string input, char * output){
	for(unsigned int i = 0; i < input.length(); i++){
		output[i] = input[i];
	}
}

void draw_borders(WINDOW* screen)
{
    int x, y, i;

    getmaxyx(screen, y, x);

    // the 4 corners
    mvwprintw(screen, 0, 0, "*");
    mvwprintw(screen, y - 1, 0, "*");
    mvwprintw(screen, 0, x - 1, "*");
    mvwprintw(screen, y - 1, x - 1, "*");

    // sides of the borders
    for (i = 1; i < (y - 1); i++)
    {
        mvwprintw(screen, i, 0, "|");
        mvwprintw(screen, i, x - 1, "|");
    }

    // top and bottom
    for (i = 1; i < (x - 1); i++)
    {
        mvwprintw(screen, 0, i, "*");
        mvwprintw(screen, y - 1, i, "*");
    }
}

int main(){
    int parent_x, parent_y;
    int middle_size = 20;
    int bottom_size = 3;
    char TitleScreen[] ="   _____                         _____ _        _   _ \n                 / ____|                       / ____| |      | | (_)         \n                | (___  _ __   __ _  ___ ___  | (___ | |_ __ _| |_ _  ___  _ __ \n                 \\___ \\| '_ \\ / _` |/ __/ _ \\  \\___ \\| __/ _` | __| |/ _ \\| '_ \\ \n                 ____) | |_) | (_| | (_|  __/  ____) | || (_| | |_| | (_) | | | |\n                |_____/| .__/ \\__,_|\\___\\___| |_____/ \\__\\__,_|\\__|_|\\___/|_| |_| \n                       | |       _  _   _  _   _  _   _  _ \n                       |_|      | || | | || | | || | | || |\n                                | || |_| || |_| || |_| || |_ \n                                |__   _|__   _|__   _|__   _|\n                                   | |    | |    | |    | |\n                                   |_|    |_|    |_|    |_|";
    char HelpMenu[] = "Use 'go to [exact room name]' to move to another room. \n  Use 'look' to see what items are in a room and what the connected rooms are. \n  Use 'grab [exact item name]' to pick up an item \n  Use 'quit' to exit. (Will not work when responding to an event). \n  Use 'help' at any point during the game to see these instructions again \n";
    //const char *RoomInfo = "";
    Game game;
    
    initscr();
    //noecho();
    curs_set(TRUE);
    keypad(stdscr, TRUE);

    // get our maximum window dimensions
    //getmaxyx(stdscr, parent_y, parent_x);
    
    // preset window settings
    parent_x = 110;
    parent_y = 50;
    
    // set up the initial windows
    WINDOW* top = newwin(parent_y - middle_size, parent_x, 0, 0);
    WINDOW* middle = newwin(middle_size - bottom_size, parent_x, parent_y - middle_size, 0);
    WINDOW* bottom = newwin(bottom_size, parent_x, parent_y - bottom_size, 0);

    // initalize color
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    bkgd(COLOR_PAIR(1));
    wbkgd(top, COLOR_PAIR(1));
    wbkgd(middle, COLOR_PAIR(1));
    wbkgd(bottom, COLOR_PAIR(1));
    
    // draw to our windows
    mvwaddstr(top, 3, 15, TitleScreen);
    mvwaddstr(middle, 1, 8, HelpMenu);
    //mvwaddstr(bottom, 1, 1, "TEXT INPUT WINDOW");
    
    draw_borders(top);
    draw_borders(middle);
    //draw_borders(bottom);
    
    refresh();
    wrefresh(top);
    wrefresh(middle);
    //wrefresh(bottom);
    
	string curRoom = "";

	char RoomInfo[3000];

	while(game.getPlayerStatus()){
        
		currentRoomStrings res = game.getCurrentRoomStrings();
    
        string RoomInfoStr; 
        
		if(res.activeEvent){
			RoomInfoStr = res.roomName + "\n" + res.eventName + "\n" + res.eventDescription + "\n";
			RoomInfoStr += "Event options: ";
			for(unsigned int i = 0; i < res.currentOptions->size(); i++){
				RoomInfoStr += res.currentOptions->at(i) + ", ";
			}
		} else {
			RoomInfoStr = res.roomName + "\n" + res.roomDescription;
		}

		memset(RoomInfo, '\0', 3000);

		char lengC[10];
		strToCstr(RoomInfoStr, RoomInfo);
		string leng = to_string(strlen(RoomInfo));
		strToCstr(leng, lengC);

		if(curRoom != res.roomName){
   
			// draw to our windows
			mvwprintw(top, 3, 15, TitleScreen);
			mvwprintw(middle, 1, 1, RoomInfo);
			mvwprintw(bottom, 1, 1, lengC);
		
			draw_borders(top);
			draw_borders(middle);
			draw_borders(bottom);

						
			// refresh each window
			refresh();
			wrefresh(top);
			wrefresh(middle);
			wrefresh(bottom);

			curRoom = res.roomName;
		}

		char cInput[1000];
		memset(cInput, '\0', 1000);

		move(48,1);
		refresh();

		getstr(cInput);
		
       	string input = "";
	   	
		int len = strlen(cInput);
		for(int i = 0; i < len; i++){
			input += cInput[i];
		}
		
		string result;
		if(res.activeEvent){
			result = game.respondToEvent(input).at(0);
		} else {
			result = game.processPlayerInput(input);
		}

		//char resultC[3000];
		memset(RoomInfo, '\0', 3000);

		strToCstr(result, RoomInfo);

        mvwprintw(middle, 1, 1, " ");

        draw_borders(middle);
        
       	// refresh each window
        refresh();
        wrefresh(middle);


		// draw to our windows
        mvwprintw(top, 3, 15, TitleScreen);
        mvwprintw(middle, 1, 1, RoomInfo);
        mvwprintw(bottom, 1, 1, "");

        draw_borders(top);
        draw_borders(middle);
        draw_borders(bottom);
        
       	// refresh each window
        refresh();
        wrefresh(top);
        wrefresh(middle);
        wrefresh(bottom);
	}

	return 0;
}

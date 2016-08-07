#include "Game.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <string>


using namespace std;

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
    int middle_size = 12;
    int bottom_size = 3;
    char TitleScreen[] ="   _____                         _____ _        _   _ \n                 / ____|                       / ____| |      | | (_)         \n                | (___  _ __   __ _  ___ ___  | (___ | |_ __ _| |_ _  ___  _ __ \n                 \\___ \\| '_ \\ / _` |/ __/ _ \\  \\___ \\| __/ _` | __| |/ _ \\| '_ \\ \n                 ____) | |_) | (_| | (_|  __/  ____) | || (_| | |_| | (_) | | | |\n                |_____/| .__/ \\__,_|\\___\\___| |_____/ \\__\\__,_|\\__|_|\\___/|_| |_| \n                       | |       _  _   _  _   _  _   _  _ \n                       |_|      | || | | || | | || | | || |\n                                | || |_| || |_| || |_| || |_ \n                                |__   _|__   _|__   _|__   _|\n                                   | |    | |    | |    | |\n                                   |_|    |_|    |_|    |_|";
    char HelpMenu[] = "Use 'go to [exact room name]' to move to another room. \n  Use 'look' to see what items are in a room and what the connected rooms are. \n  Use 'grab [exact item name]' to pick up an item \n  Use 'quit' to exit. (Will not work when responding to an event). \n  Use 'help' at any point during the game to see these instructions again \n";
    //const char *RoomInfo = "";
    Game game;
    
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    // get our maximum window dimensions
    //getmaxyx(stdscr, parent_y, parent_x);
    
    // preset window settings
    parent_x = 110;
    parent_y = 30;
    
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
    

	/*while(game.getPlayerStatus()){
		//game.printCurrentRoom();
        currentRoomStrings res = game.getCurrentRoomStrings();
        
        RoomInfo = (res.roomName + "\n" + res.roomDescription + "\n" + res.eventName + "\n" + res.eventDescription + "\n").c_str();
        
        
        // draw to our windows
        mvwprintw(top, 3, 15, "Graphics/Animation");
        mvwprintw(middle, 1, 1, RoomInfo);
        mvwprintw(bottom, 1, 1, "TEXT INPUT WINDOW");
    
        draw_borders(top);
        draw_borders(middle);
        draw_borders(bottom);
        
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
        
        // refresh each window
        refresh();
        wrefresh(top);
        wrefresh(middle);
        wrefresh(bottom);
	}*/

	return 0;
}

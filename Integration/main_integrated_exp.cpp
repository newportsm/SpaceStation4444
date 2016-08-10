#include "Game.hpp"
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <string>


using namespace std;

void strToCstr(string input, char * output){
	/*for(unsigned int i = 0; i < input.length(); i++){
		output[i] = input[i];
	}*/
	int totalLength = input.length();
	int inPos = 0;
	int outPos = 0;
	int wordCount = 0;
	int lineCount = 0;
	int width = 105;
	while(inPos < totalLength){
		wordCount = 0;
		while(input[inPos + wordCount] != ' ' && input[inPos + wordCount] != '\n' && inPos + wordCount < totalLength - 2){
			wordCount++;
		}
		if(input[inPos + wordCount] == '\n'){
			lineCount = 0;
		}
		wordCount++;
		if(wordCount + lineCount > width){
			output[outPos] = '\n';
			outPos++;
			lineCount = 0;
		}
		int curPos = inPos;
		while(inPos < curPos + wordCount){
			output[outPos] = input[inPos];
			outPos++;
			inPos++;
			lineCount++;
		}
	}
}

string cstrToStr(char * input){
	string output = "";
	int len = strlen(input);
	for(int i = 0; i < len; i++){
		output += input[i];
	}
	return output;
}

int main(){
    int parent_x, parent_y;
    int middle_size = 22;
    int bottom_size = 3;
    char TitleScreen[] ="   _____                         _____ _        _   _ \n                 / ____|                       / ____| |      | | (_)         \n                | (___  _ __   __ _  ___ ___  | (___ | |_ __ _| |_ _  ___  _ __ \n                 \\___ \\| '_ \\ / _` |/ __/ _ \\  \\___ \\| __/ _` | __| |/ _ \\| '_ \\ \n                 ____) | |_) | (_| | (_|  __/  ____) | || (_| | |_| | (_) | | | |\n                |_____/| .__/ \\__,_|\\___\\___| |_____/ \\__\\__,_|\\__|_|\\___/|_| |_| \n                       | |       _  _   _  _   _  _   _  _ \n                       |_|      | || | | || | | || | | || |\n                                | || |_| || |_| || |_| || |_ \n                                |__   _|__   _|__   _|__   _|\n                                   | |    | |    | |    | |\n                                   |_|    |_|    |_|    |_|";
    char HelpMenu[] = "HELP MENU - COMMANDS\nUse 'go [room name]' to move to another room.\nUse 'look' to get full room description.\nUse 'look at [item name]' to get description of something in a room.\nUse 'check' to get a list of all the items you have picked up.\nUse 'check [item name]' to get a description of an item you have picked up.\nUse 'open [item name]' top open something and see what's inside.\nUse 'grab [item name]' to pick up an item.\nUse 'patch [item name] with [item name]' to patch and item.\nUse 'insert [item name] into [item name]' to insert one item into another.\nUse 'install [item name] into [item name]' to install one item in another.\nUse 'fly [item name]' to fly something, like an airplane.\nUse 'hit [item name] with [item name]' to hit one item with another.\nUse 'quit' to exit. (Will not work when responding to an event.\nUse 'help' at any point during the game to see these instructions again.\nType 'START' and hit enter to begin the game.";
	char Introduction[] = "Space Station 4444 is the last line of defense for the Planet Hobbly Knees, a planet rich in\n untamed resources and a warning to chartographers everywhere not to let their kids get involved \nin the naming process. You've been serving on this station for the better part of a year -- not\n quite a newbie yet not quite a regular. Nevertheless, you've bonded well with the other crew and \nthe captain has proven to be strict by understanding.\n\nIt's the afternoon watch, and you're alone on the bridge -- the rest of the crew are either in \nthe rest of the crew is either in the training room or in the science lab. You're relaxing in the\ncaptain's chair on the bridge, spinning a pen in your hand daydreaming about sipping exotic cocktails\n on a beach when the proximity sensors begin blaring. Before you even have time to sit up, the wall \nabove you explodes and the furious screech of air being sucked into space deafens you.\n\nEverything goes black... \nPress a key to continue...";
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
    WINDOW* topborder = newwin(parent_y - middle_size, parent_x, 0, 0);
    WINDOW* top = newwin(parent_y - middle_size - 2, parent_x - 2, 1, 1);
    WINDOW* middleborder = newwin(middle_size - bottom_size, parent_x, parent_y - middle_size, 0);
    WINDOW* middle = newwin(middle_size - bottom_size - 2, parent_x - 2, parent_y - middle_size + 1, 1);
    WINDOW* bottomborder = newwin(bottom_size, parent_x, parent_y - bottom_size, 0);
    WINDOW* bottom = newwin(bottom_size - 2, parent_x - 2, parent_y - bottom_size + 1, 1);

    // initalize color
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    bkgd(COLOR_PAIR(1));
    wbkgd(top, COLOR_PAIR(1));
    wbkgd(middle, COLOR_PAIR(1));
    wbkgd(bottom, COLOR_PAIR(1));
    
    // draw to our windows
    mvwaddstr(top, 8, 15, TitleScreen);
    mvwaddstr(middle, 0, 0, HelpMenu);
    mvwaddstr(bottom, 1, 1, " ");
    
	box(topborder, 0, 0);
	box(middleborder, 0, 0);
	box(bottomborder, 0, 0);
    
    refresh();
    wrefresh(topborder);
    wrefresh(top);
    wrefresh(middleborder);
    wrefresh(middle);
    wrefresh(bottomborder);
    wrefresh(bottom);

   	//String and c-string used to get input!	
	string curRoom = "";
	char RoomInfo[3000];
	char cInput[1000];
	string input = "";

	do{
		refresh();
		werase(bottom);
        wrefresh(bottom);

		mvwaddstr(bottom, 1, 1, " ");
		box(bottomborder, 0, 0);
		wrefresh(bottom);
		move(48, 1);
		refresh();

		getstr(cInput);
		input = cstrToStr(cInput);
		for(unsigned int i = 0; i < input.length(); i++){
			input[i] = tolower(input[i]);
		}
	}while(input != "start");

	clear();
	refresh();
	
	// introduction window message
	box(topborder, 0, 0);
	mvwprintw(top, 5, 1, Introduction);
	refresh();
	wrefresh(topborder);
	wrefresh(top);
	
	getchar();

	clear();
	refresh();


	while(game.getPlayerStatus()){
   
	 	//This gets the "strings" (room name, event name, descriptions, etc.)
		//from the current room.
		//The starting room is set as the brdige when the game loads.
		currentRoomStrings res = game.getCurrentRoomStrings();
   
	   	//This string will cumulatively hold the strings to be display for the room.
		//    !!!! Important !!!!
		//    We display EITHER room info OR event info!!!
        string RoomInfoStr; 
       
	   	//Here's where we do the dumping. If there's an active event, grab
		//all those strings and dump them into res.	
		if(res.activeEvent){
			//Get room name, event name, and event description
			RoomInfoStr = res.roomName + "\n" + res.eventName + "\n" + res.eventDescription + "\n";
			//We also need the options for the event.
			RoomInfoStr += "Event options: ";
			for(unsigned int i = 0; i < res.currentOptions->size(); i++){
				RoomInfoStr += res.currentOptions->at(i) + ", ";
			}
		} 
		//If there is no active event, just get the room name and description.
		else {
			RoomInfoStr = res.roomName + "\n" + res.roomDescription;
		}

		//Make sure RoomInfo is empty, please!
		memset(RoomInfo, '\0', 3000);

		//Convert our string with the room info into a c-string for nCurses.
		strToCstr(RoomInfoStr, RoomInfo);
	
		//If we have moved to a new room, display it.
		//Otherwise, skip to getting input from user.	
		if(curRoom != res.roomName){
			werase(stdscr); 
			werase(middle);
   
			// draw to our windows
			mvwprintw(top, 8, 15, TitleScreen);
			mvwprintw(middle, 1, 1, RoomInfo);
			mvwprintw(bottom, 1, 1, "");
		
			box(topborder, 0, 0);
			box(middleborder, 0, 0);
			box(bottomborder, 0, 0);
					
			// refresh each window
			refresh();
			wrefresh(topborder);
			wrefresh(top);
			wrefresh(middleborder);
			wrefresh(middle);
			wrefresh(bottomborder);
			wrefresh(bottom);

			curRoom = res.roomName;
		}

		//Make sure our input c-string is nice and empty, please!
		memset(cInput, '\0', 1000);

		//Put our cursor in the text entry box.
		move(48,1);
		refresh();

		//Get input from the user!
		do{
			getstr(cInput);
			move(48,1);
			refresh();
		}while(strlen(cInput) < 2);
	
		//Convert cInput to string
       	input = cstrToStr(cInput);

		//We'll pass input to the game object to get the result
		//of the player's command. Note that if there is an 
		//active event, it will go to respondToEvent.
		//Otherwise, it goes to processPlayerInput.
		string result = "";
		if(res.activeEvent){
			result = game.respondToEvent(input).at(0);
		} else {
			result = game.processPlayerInput(input);
		}

		// refresh each window
        refresh();
        werase(middle);
        wrefresh(middle);
		werase(bottom);
        wrefresh(bottom);

		//We'll reuse RoomInfo here and convert the result
		//to a c-string which goes into RoomInfo.
		memset(RoomInfo, '\0', 3000);
		strToCstr(result, RoomInfo);
        
		// draw to our windows
        mvwprintw(top, 3, 15, TitleScreen);
        mvwprintw(middle, 1, 1, RoomInfo);
        mvwprintw(bottom, 1, 1, "");

		box(topborder, 0, 0);
		box(middleborder, 0, 0);
		box(bottomborder, 0, 0);
        
       	// refresh each window
        refresh();
        wrefresh(topborder);
        wrefresh(top);
        wrefresh(middleborder);
        wrefresh(middle);
        wrefresh(bottomborder);
        wrefresh(bottom);
	}

	return 0;
}

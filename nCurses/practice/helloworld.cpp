#include <ncurses.h>

int main()
{	
	printw("Main window");

    WINDOW* subwindow = newwin(10,20,5,15);

    refresh();
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
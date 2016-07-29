#include <ncurses.h>
#include <unistd.h>

// function to draw borders around windows
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

int main(int argc, char* argv[])
{
    int parent_x, parent_y;
    int middle_size = 12;
    int bottom_size = 3;


    initscr();
    noecho();
    curs_set(FALSE);

    // get our maximum window dimensions
    getmaxyx(stdscr, parent_y, parent_x);
    
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
    
    // draw borders
    draw_borders(top);
    draw_borders(middle);
    draw_borders(bottom);
    
    // draw to our windows
    mvwprintw(top, 1, 1, "GRAPHICS WINDOW");
    mvwprintw(middle, 1, 1, "TEXT DESCRIPTION WINDOW");
    mvwprintw(bottom, 1, 1, "TEXT INPUT WINDOW");
    
    // refresh each window
    refresh();
    wrefresh(top);
    wrefresh(middle);
    wrefresh(bottom);
    
    // wait to exit
    getch();
    
    // to exit after * seconds
    //sleep(5);
    
    // clean up
    // delwin(top);
    // delwin(middle);
    // delwin(bottom);

    endwin();
    return 0;
}
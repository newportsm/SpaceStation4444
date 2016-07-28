#include <ncurses.h>
#include <unistd.h>

// for drawing borders around each window (top, middle, bottom)
void draw_borders(WINDOW *screen) {
  int x, y, i;

  getmaxyx(screen, y, x);

  // the 4 corners
  mvwprintw(screen, 0, 0, "*");
  mvwprintw(screen, y - 1, 0, "*");
  mvwprintw(screen, 0, x - 1, "*");
  mvwprintw(screen, y - 1, x - 1, "*");

  // sides of the borders
  for (i = 1; i < (y - 1); i++) {
    mvwprintw(screen, i, 0, "|");
    mvwprintw(screen, i, x - 1, "|");
  }

  // top and bottom
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, 0, i, "*");
    mvwprintw(screen, y - 1, i, "*");
  }
}

int main(int argc, char *argv[]) {
  int parent_x, parent_y, new_x, new_y;
  int middle_size = 12;
  int bottom_size = 3;

  initscr();
  curs_set(1);

  // set up the initial windows
  getmaxyx(stdscr, parent_y, parent_x);

  WINDOW *top = newwin(parent_y - middle_size, parent_x, 0, 0);
  WINDOW *middle = newwin(middle_size - bottom_size, parent_x, parent_y - middle_size, 0);
  WINDOW *bottom = newwin(bottom_size, parent_x, parent_y - bottom_size, 0);

    // run through and call borders function for each window
  draw_borders(top);
  draw_borders(middle);
  draw_borders(bottom);
  
  // window colors
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  wbkgd(stdscr, COLOR_PAIR(1));
  wbkgd(top, COLOR_PAIR(1));
  wbkgd(middle, COLOR_PAIR(1));
  wbkgd(bottom, COLOR_PAIR(1));
  refresh();
  

    // this will be for resizing still needs work
   while(1) {
     getmaxyx(stdscr, new_y, new_x);

    if (new_y != parent_y || new_x != parent_x) {
      parent_x = new_x;
      parent_y = new_y;

      wresize(top, new_y - bottom_size, new_x);
      wresize(bottom, bottom_size, new_x);
      mvwin(bottom, new_y - bottom_size, 0);

      wclear(stdscr);
      wclear(top);
      wclear(middle);
      wclear(bottom);

      draw_borders(top);
      draw_borders(middle);
      draw_borders(bottom);
    }

    // print out to each window
    mvwprintw(top, 1, 1, "TOP WINDOW");
    mvwprintw(middle, 1, 1, "MIDDLE WINDOW");
    mvwprintw(bottom, 1, 1, "TEXT INPUT WINDOW");

    // refresh each window
    wrefresh(top);
    wrefresh(middle);
    wrefresh(bottom);
   }

  endwin();
  return 0;
}
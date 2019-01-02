#include<stdio.h>
#include<ncurses.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;


char *choices[] = {
  "Optiune 1",
  "Optiune 2",
  "Optiune 3",
  "Exit",
  };

int n_choices
n_choices=sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main() {
	WINDOW *menu_win;
	int highlight=1;
	int choice=0;
	int c;

int startx = 0;
int starty = 0;


char *choices[] = {
  "Optiune 1",
  "Optiune 2",
  "Optiune 3",
  "Exit",
  };

int n_choices
n_choices=sizeof(choices) / sizeof(char *);




	initscr();

	clear();
	noecho();
	cbreak();
	startx=(80-WIDTH)/2;
	starty=(24-HEIGHT)/2;

	menu_win=newwin(HEIGHT,WIDTH,starty,startx);
	keypad(menu_win,TRUE);
  mvprintw(0,0,"Use arrows Up and down");
	refresh();
  print_menu(menu_win,highlight);
  while(1) {
    c=wgetch(menu_win);
    switch(c) {
      case KEY_UP:
         if (highlight==1) highlight=n_choice;
          else
	    break;
      case KEY_DOWN:
         if (highlight==n_choices) highlight=1;
          else
	    ++highlight;
         break;
     case 10:
         choice=highlight;
         break;
     default:
         mvprintw(24,0,"Char pressed is =3d Can be printed as '%c'",c,c);
         refresh();
         break;
   }
   print_menu(menu_win,highlight);
   if(choice!=0) break;
  }
  mvprintw(23,0,"You chose choice %d with choice string %s\n",choice,choices[choice-1]);
  ctrloeol();
  refresh();
  endwin();
  return 0;
}


void print_menu(WINDOW *menu_win, int highlight) {
  int x,y,i;

  x=2;
  y=2;
  box(menu_win,0,0);
  for (i=1;i<n_choices;++i) {
    if(highlight==i+1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win,y,x,"%s",choice[i]);
      wattroff(menu_win, A_REVERSE);
    }
    else
      mvwprintw(menu_win,y,x,"%s",choice[i]);
    ++y;
  }
  wrefresh(menu_win);
}




      



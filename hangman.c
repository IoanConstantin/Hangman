#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

#define CTRLD 4

WINDOW *win1,*win2;


void quit(void) //iesire din aplicatie
{
  delwin(win1);
  delwin(win2);
  endwin();
}

//definire meniu
char *choices[]={
  "New Game",
  "Resume Game",
  "Quit",
  };

void joc(char *name); //functia apelata la selectia optiunii

int main() {
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices,i;

  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr,TRUE);
  init_pair(1,COLOR_RED,COLOR_BLACK);
  init_pair(2,COLOR_GREEN,COLOR_BLACK);
  init_pair(3,COLOR_MAGENTA,COLOR_BLACK);

  n_choices=ARRAY_SIZE(choices);
  my_items=(ITEM **)calloc(n_choices+1,sizeof(ITEM *));
  for(i=0;i<n_choices; ++i) {
     my_items[i]=new_item(choices[i],"");
     set_item_userptr(my_items[i], joc);
  }
  my_items[n_choices]=(ITEM *)NULL;
  my_menu=new_menu((ITEM **)my_items);

  set_menu_fore(my_menu,COLOR_PAIR(1) | A_REVERSE);
  set_menu_back(my_menu,COLOR_PAIR(2));
  set_menu_grey(my_menu,COLOR_PAIR(3));
  
  mvprintw(LINES-2,0,"Up/Down to Navigate            ENTER for Selection");
  post_menu(my_menu);
  refresh();

  int ww;
  ww=0;
  do {
    c=getch();
    switch(c) {
       case KEY_DOWN:
          menu_driver(my_menu,REQ_DOWN_ITEM);
          break;
       case KEY_UP:
          menu_driver(my_menu,REQ_UP_ITEM);
          break;
       case 10:
       {  ITEM *cur;
          void (*p)(char *);
          cur=current_item(my_menu);
          p=item_userptr(cur);
          p((char *)item_name(cur));
          pos_menu_cursor(my_menu);
          if (strcmp(item_name(current_item(my_menu)),"Quit")==0) ww=1;
          break;
        }
        break;
     }
  } while (ww==0);
  
  unpost_menu(my_menu);
  for(i=0;i<n_choices;++i)
    free_item(my_items[i]);
  free_menu(my_menu);
  endwin();
}


void joc(char *name)
{
   move(20,0);
   clrtoeol();
   mvprintw(20,0,"Item selected is: %s",name);

   ITEM **my_items;
   int n_choices,i;

   initscr();
   start_color();
   cbreak();
   noecho();
   keypad(stdscr,TRUE);
   init_pair(1,COLOR_RED,COLOR_BLACK);
   init_pair(2,COLOR_GREEN,COLOR_BLACK);
   init_pair(3,COLOR_MAGENTA,COLOR_BLACK);

   n_choices=ARRAY_SIZE(choices);
   my_items=(ITEM **)calloc(n_choices+1,sizeof(ITEM *));
   for(i=0;i<n_choices; ++i) {
     my_items[i]=new_item(choices[i],"");
     set_item_userptr(my_items[i], joc);
   }
   my_items[n_choices]=(ITEM *)NULL;
   if (strcmp(name,"New Game")==0) 
   //daca se selecteaza optiunea "New Game"
   {
       time_t timer;
       char buffer[26];
       struct tm* tm_info;
       time(&timer);
       tm_info=localtime(&timer);

       strftime(buffer,26,"%d-%m-%Y %H:%M:%S\n",tm_info);
  
      char cuv[1000];
      char afis[1000];
      FILE *fp;
      fp=fopen("fis1.txt","r");
      int m,m2;
      m2=rand()%8;
  
      m=0;
      do {
  	fgets(cuv,1000,fp);
	m++;		
      } while (m<m2);

      fclose(fp);


     initscr();
     atexit(quit);
     clear();
  
     // transformare initiala catre sir ascuns
     strcpy(afis,cuv);
     int nch_cuv;
     nch_cuv=strlen(cuv)-1;
 
  
     for(m=0;m<nch_cuv;m++) {
       cuv[m]=tolower(cuv[m]);
       afis[m]='.';    
     }
  

     for(m=0;m<nch_cuv-1;m++) 
       if (cuv[m]==' ')
         afis[m]=' ';

  
     // primul char afisat sau nu
    if (cuv[1]!=' ') 
       afis[0]=cuv[0];

    // ultimul char afisat sau nu
    if (cuv[nch_cuv-2]!=' ') 
      if (nch_cuv>2) 
        if (cuv[nch_cuv-3]!=' ')
           afis[m]=cuv[nch_cuv-1];
    
  
    // dc caracterul are un spatiu in dreapta il afisez
    for(m=1;m<nch_cuv-2;m++) 
      if (afis[m+1]==' ')
      {    
          if(m==1) 
              afis[m]='.'; 
          else 
              afis[m]=cuv[m];
      }

    // dc caracterul are un spatiu in stanga il afisez
    for(m=1;m<nch_cuv-1;m++) 
      if (afis[m-1]==' ')
  	  afis[m]=cuv[m];

    // exceptie pt. spatiu+ch1+ch2+spatiu cand se afiseaza ch1 si spatiu
    for(m=1;m<nch_cuv-4;m++) 
      if (afis[m]==' ')
         if (afis[m+1]!=' ')
           if (afis[m+2]!=' ')
             if (afis[m+3]==' ') {
        	  afis[m+1]=cuv[m+1];
        	  afis[m+2]='.';
             };

    //exceptie pt. spatiu+ch+spatiu cand se afiseaza punct(sau spatiu in cazul enuntului)
    for(m=1;m<nch_cuv-2;m++)
       if(afis[m]==' ')
          if(afis[m+1]!=' ')
             if(afis[m+2]==' ')
                   afis[m+1]='.';

    //un char care e afisat cf algoritmului
    // trebuie afisat oriunde apare in alte cuvinte/litere

    for(m=0;m<nch_cuv;m++) 
      if (afis[m]==cuv[m])
        for (m2=0;m2<nch_cuv;m2++)  
  	  if ( (cuv[m2]==cuv[m]) && (m2!=m) && (afis[m2]=='.') ) 
             afis[m2]=afis[m];

  
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, 1);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);

    win1 = newwin(10,40,7, 5);
    win2 = newwin(3, 40,19, 5);
  
    bkgd(COLOR_PAIR(1));
    wbkgd(win1, COLOR_PAIR(2));
    wbkgd(win2, COLOR_PAIR(2));

  
    mvwaddstr(win1, 1, 3, "___________________________");
    mvwaddstr(win1, 2, 3, "  |                      |");
    mvwaddstr(win1, 3, 3, "  |                      |");
    mvwaddstr(win1, 4, 3, "  |");
    mvwaddstr(win1, 5, 3, "  |"); 
    mvwaddstr(win1, 6, 3, "  |"); 
    mvwaddstr(win1, 7, 3, "  |");
    mvwaddstr(win1, 8, 3, " /|\\"); 
    mvwaddstr(win1, 9, 3, " /|\\"); 
    mvwaddstr(win1, 7, 7, " Litere gresite:");

    mvwaddstr(win2, 1, 3, " Q - Save and Exit\n");
    mvwaddstr(win2, 2, 3, buffer);
  
    refresh();

    wrefresh(win1);
    wrefresh(win2);



    // citire litere
    int greseli_adm,gresite,sfarsit_joc;
    sfarsit_joc=0;
    greseli_adm=6;
    gresite=0;

    char ghici;
    char sir_gresite[6]="      ";

    move(2,2);
    printw(afis);
    refresh();
  
    do {
     ghici=getch();
     ghici=tolower(ghici);//ghici-litera introdusa de utilizator
     
     int i,caracterexista=0;
     //caracterexista verifica daca litera 
     //exista deja in sirul ascuns sau in sirul caracterelor gresite
       for(i=0;i<strlen(sir_gresite);i++)
           if(ghici==sir_gresite[i]) caracterexista=1;

       for(i=0;i<strlen(afis);i++)
           if(ghici==afis[i]) caracterexista=1;
   if(caracterexista==0) 
   {
     if(ghici=='q') {
        sfarsit_joc=1; 
        FILE *fp2;
        fp2=fopen("fis2.txt","w");
        fputs(cuv,fp2);
        fputs(afis,fp2);
        fputs(sir_gresite,fp2);
        fclose(fp2);
        char cuvant[100]="1";
        FILE *fp1;
        fp1=fopen("jocterminat.txt","w");
        fputs(cuvant,fp1);
        fclose(fp1);
     }
     else 
     { int incerc_reusita;
      incerc_reusita=0;
      for (m2=0;m2<nch_cuv;m2++) {
        if (cuv[m2]==ghici)  
          if (afis[m2]=='.')
          {
             incerc_reusita=1;
             afis[m2]=ghici;
             move(2,2);
             printw(afis);
             m=0;
             for (m2=0;m2<nch_cuv;m2++) 
                if (afis[m2]=='.')
                   m=1;
             if (m==0) {
                move(3,2);
                printw("   *** WIN ***   ");
                char cuvant[100]="0";
                FILE *fp1;
                fp1=fopen("jocterminat.txt","w");
                fputs(cuvant,fp1);
                fclose(fp1);
             }
             refresh();
         }
       }
        if (incerc_reusita==0) {
            sir_gresite[gresite]=ghici;  
            ++gresite;
           switch (gresite) {
               case 1:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 wrefresh(win1);
                 break;
               case 2:
                 mvwaddstr(win1, 5, 3, "  |                      |");
                 wrefresh(win1);
                 break;
               case 3:
                 mvwaddstr(win1, 5, 3, "  |                     /|");
                 wrefresh(win1);
                 break;
               case 4:
                 mvwaddstr(win1, 5, 3, "  |                     /|\\");
                 wrefresh(win1);
                 break;
               case 5:
                 mvwaddstr(win1, 6, 3, "  |                     /");
                 wrefresh(win1);
                 break;
               case 6:
                 mvwaddstr(win1, 6, 3, "  |                     / \\");
                 wrefresh(win1);
                 break;

           }

            move(3,2);
	    mvwaddstr(win1, 8, 7,sir_gresite); 
            wrefresh(win1);
            refresh();
       }      
            if(gresite==greseli_adm) {
		move(4,2);
                printw("   GAME OVER   ");
                char cuvant[100]="0";
                FILE *fp1;
                fp1=fopen("jocterminat.txt","w");
                fputs(cuvant,fp1);
                fclose(fp1);
                refresh();
                         
              sfarsit_joc=1;
            }
         }
      
      FILE *fp1;
      char str1[100];
      fp1=fopen("jocterminat.txt","r");
      //daca pe prima linie a fisierului jocterminat se gaseste 1 
      //inseamna ca s-a salvat starea curenta prin apasarea tastei q
      //si apoi se poate selecta resume
      //daca pe prima linie a fisierului jocterminat se gaseste 0
      //nu s-a apasat q si se ascunde optiunea de resume 
      fgets(str1,100,fp1);
      if(strcmp(str1,"1")==0) 
         item_opts_on(my_items[2],O_SELECTABLE);
      if(strcmp(str1,"0")==0) 
         item_opts_off(my_items[2],O_SELECTABLE);
      fclose(fp1);
   
      time(&timer);
      tm_info=localtime(&timer);
      strftime(buffer,26,"%d-%m-%Y %H:%M:%S\n",tm_info);
      mvwaddstr(win2, 2, 3, buffer); 
      wrefresh(win2);
     } 
    } while (sfarsit_joc!=1);

   }
   if (strcmp(name,"Resume Game")==0)
   //daca se selecteaza optiunea Resume Game
   {
       time_t timer;
       char buffer[26];
       struct tm* tm_info;
       time(&timer);
       tm_info=localtime(&timer);

       strftime(buffer,26,"%d-%m-%Y %H:%M:%S\n",tm_info);
  
      char cuv[1000];
      char afis[1000];
      char sir_gresite[6]="      ";
      FILE *fp;
      fp=fopen("fis2.txt","r");
      int m,m2;
      
      //citire date salvate de la ultima rulare a jocului
      m=0;
      do {
  	if (m==0)
          fgets(cuv,1000,fp);
	if (m==1)
          fgets(afis,1000,fp);
	if (m==2)
          fgets(sir_gresite,1000,fp);
         m++;		
      } while (m<3);

      fclose(fp);


     initscr();
     atexit(quit);
     clear();
  
     int nch_cuv;
     nch_cuv=strlen(cuv)-1;
 
  
  
    noecho(); 
    curs_set(0);
    cbreak();
    keypad(stdscr, 1);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);

    win1 = newwin(10,40,7, 5);
    win2 = newwin(3, 40,19, 5);
  
    bkgd(COLOR_PAIR(1));
    wbkgd(win1, COLOR_PAIR(2));
    wbkgd(win2, COLOR_PAIR(2));
  
    mvwaddstr(win1, 1, 3, "___________________________");
    mvwaddstr(win1, 2, 3, "  |                      |");
    mvwaddstr(win1, 3, 3, "  |                      |");
    mvwaddstr(win1, 4, 3, "  |");
    mvwaddstr(win1, 5, 3, "  |"); 
    mvwaddstr(win1, 6, 3, "  |"); 
    mvwaddstr(win1, 7, 3, "  |");
    mvwaddstr(win1, 8, 3, " /|\\"); 
    mvwaddstr(win1, 9, 3, " /|\\");
    mvwaddstr(win1, 7, 7, " Litere gresite:"); 

    mvwaddstr(win2, 1, 3, " Q - Save and Exit\n");
    mvwaddstr(win2, 2, 3, buffer);
  
    refresh();
    wrefresh(win1);
    wrefresh(win2);



    // citire litere
    int greseli_adm,gresite,sfarsit_joc;
    sfarsit_joc=0;
    greseli_adm=6;
    gresite=0;

    // calculez nr. de greseli pentru datele restaurate din fis2.txt
    for(m=0;m<6;m++)
       if(sir_gresite[m]!=' ')    
          gresite++;

    char ghici;
  

    move(2,2);
    printw(afis);
    mvwaddstr(win1, 8, 7,sir_gresite); 
    wrefresh(win1);
    refresh();

    //afisez spanzuratoarea
           switch (gresite) {
               case 1:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 wrefresh(win1);
                 break;
               case 2:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 mvwaddstr(win1, 5, 3, "  |                      |");
                 wrefresh(win1);
                 break;
               case 3:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 mvwaddstr(win1, 5, 3, "  |                      |");
                 mvwaddstr(win1, 5, 3, "  |                     /|");
                 wrefresh(win1);
                 break;
               case 4:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 mvwaddstr(win1, 5, 3, "  |                      |");
                 mvwaddstr(win1, 5, 3, "  |                     /|");
                 mvwaddstr(win1, 5, 3, "  |                     /|\\");
                 wrefresh(win1);
                 break;
               case 5:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 mvwaddstr(win1, 5, 3, "  |                      |");
                 mvwaddstr(win1, 5, 3, "  |                     /|");
                 mvwaddstr(win1, 5, 3, "  |                     /|\\");
                 mvwaddstr(win1, 6, 3, "  |                     /");
                 wrefresh(win1);
                 break;
               case 6:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 mvwaddstr(win1, 5, 3, "  |                      |");
                 mvwaddstr(win1, 5, 3, "  |                     /|");
                 mvwaddstr(win1, 5, 3, "  |                     /|\\");
                 mvwaddstr(win1, 6, 3, "  |                     /");
                 mvwaddstr(win1, 6, 3, "  |                     / \\");
                 wrefresh(win1);
                 break;

           }

     time(&timer);
     tm_info=localtime(&timer);
     strftime(buffer,26,"%d-%m-%Y %H:%M:%S\n",tm_info);
     mvwaddstr(win2, 2, 3, buffer); 
     wrefresh(win2);

    do {
     ghici=getch();
     ghici=tolower(ghici);

     int i,caracterexista=0;
 
       for(i=0;i<strlen(sir_gresite);i++)
           if(ghici==sir_gresite[i]) caracterexista=1;

       for(i=0;i<strlen(afis);i++)
           if(ghici==afis[i]) caracterexista=1;

   if(caracterexista==0)
   {  
     if(ghici=='q') {
        sfarsit_joc=1;  
        FILE *fp2;
        fp2=fopen("fis2.txt","w");
        fputs(cuv,fp2);
        fputs(afis,fp2);
        fputs(sir_gresite,fp2);
        fclose(fp2);
        char cuvant[100]="1";
        FILE *fp1;
        fp1=fopen("jocterminat.txt","w");
        fputs(cuvant,fp1);
        fclose(fp1);
     }
     else    // alta litera
     {
      int incerc_reusita;
      incerc_reusita=0;
      for (m2=0;m2<nch_cuv;m2++) {
        if (cuv[m2]==ghici)     
          if (afis[m2]=='.')
          {
             incerc_reusita=1;
             afis[m2]=ghici;  
             move(2,2);
             printw(afis);
             m=0;
             for (m2=0;m2<nch_cuv;m2++) 
                if (afis[m2]=='.')
                   m=1;
             if (m==0) {
                move(3,2);
                printw("   *** WIN ***   ");
                char cuvant[100]="0";
                FILE *fp1;
                fp1=fopen("jocterminat.txt","w");
                fputs(cuvant,fp1);
                fclose(fp1);
             }
             refresh();
         }
      }
        if (incerc_reusita==0) {
            sir_gresite[gresite]=ghici;
            ++gresite;
           switch (gresite) {
               case 1:
                 mvwaddstr(win1, 4, 3, "  |                      O");
                 wrefresh(win1);
                 break;
               case 2:
                 mvwaddstr(win1, 5, 3, "  |                      |");
                 wrefresh(win1);
                 break;
               case 3:
                 mvwaddstr(win1, 5, 3, "  |                     /|");
                 wrefresh(win1);
                 break;
               case 4:
                 mvwaddstr(win1, 5, 3, "  |                     /|\\");
                 wrefresh(win1);
                 break;
               case 5:
                 mvwaddstr(win1, 6, 3, "  |                     /");
                 wrefresh(win1);
                 break;
               case 6:
                 mvwaddstr(win1, 6, 3, "  |                     / \\");
                 wrefresh(win1);
                 break;

           }




           move(3,2);
           mvwaddstr(win1, 8, 7,sir_gresite);
           wrefresh(win1); 
           refresh();
       }
           
           if(gresite==greseli_adm) {
		move(4,2);
                printw("   GAME OVER   ");
                char cuvant[100]="0";
                FILE *fp1;
                fp1=fopen("jocterminat.txt","w");
                fputs(cuvant,fp1);
                fclose(fp1);
                refresh();
                         
              sfarsit_joc=1;
           }
         }

     FILE *fp1;
     char str1[100];
     fp1=fopen("jocterminat.txt","r");
     fgets(str1,100,fp1);
     if(strcmp(str1,"1")==0) 
         item_opts_on(my_items[2],O_SELECTABLE);
     if(strcmp(str1,"0")==0) 
         item_opts_off(my_items[2],O_SELECTABLE);
     fclose(fp1);
     
     time(&timer);
     tm_info=localtime(&timer);
     strftime(buffer,26,"%d-%m-%Y %H:%M:%S\n",tm_info);
     mvwaddstr(win2, 2, 3, buffer); 
     wrefresh(win2);
    }
    } while (sfarsit_joc!=1);

   }

}



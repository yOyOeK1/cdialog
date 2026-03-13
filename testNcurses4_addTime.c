#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <pthread.h>
#include <unistd.h>

#include "fileh.h"
#include "timeh.h"
#include "cmdh.h"
#include "dogh.h"


int row,col;
pthread_t dogTest1;

void ncursInit(){
    // init uft / emoji style 
    setlocale(LC_ALL, "");
    // Start curses mode
    initscr();
    if( has_colors() == FALSE ){
    	endwin();
	printf("Terminal don't support colors :(");
	exit(1);
    }
    
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    // get screen size 
    getmaxyx( stdscr, row, col );
    // Disable echoing of characters to the screen
    noecho();
    // Allow ncurses to capture special keys (like arrow keys and KEY_MOUSE)
    keypad(stdscr, TRUE);
    // Hide the cursor
    //curs_set(1);
    // Enable all mouse events and position reporting
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
 

}

void cl( char *msg ){
	move( 7, 0 );
	attron( A_DIM );
	printw( "[cldIM] [ %s ]", msg );
	attroff( A_DIM );
}

void clTest(){
	mvprintw( 8, 3, "1 ◔ 2 ◔ 3 \uf240 nf-fa-battery 4  \n");
	attron( COLOR_PAIR(1) |  A_BLINK );
	printw( "[cl1] ⏻ 4 POWER 󰩲 \n󱩳 panels\n󰄌 | | |󱤁 |󱤂 | 󰠌 \n");
	attroff( COLOR_PAIR(1) | A_BLINK );
	printw( "󱩅 hot 󰻠  󰝢  󰘚 󱤓 󰝲  󱚼 󰖪  " );
}

void clHelp(){
	move( 1,1 );
	printw(
		" 󰋖 - help\n"
		"h -	as help\n"
		"b - 	as battery\n"
		"t - 	as time\n"
		"c - 	as clien\n"
		"C - 	as CMD\n"
		"! - 	as thread ... start\n"
		"@ - 	as thread ... kill\n"
		"\nq - 	as Quit"
	);

}

void onBatteryUpdate(){
	attron( A_BOLD );
	mvprintw( 0,18, " 󰄌 %s %% ", file_read_to_chars("/sys/class/power_supply/BAT0/capacity") );
	attroff( A_BOLD );
	refresh();
}

void *dogBattery( void *vargp ){
	while( true ){
		onBatteryUpdate();
		sleep( 15 );
	}
}

void onClockUpdate(){
	mvprintw( 0,0, "  %s\r", time_now_tt() );
	refresh();
}


void *dogClock( void *vargp ){
	while( true ){
		onClockUpdate();
		sleep( 10 );
	}
}


bool onMouseEvent( MEVENT even){
      // Check button states and display coordinates
      if (even.bstate & BUTTON1_PRESSED) {
           mvprintw(2, 0, "Left button pressed at Y: %d, X: %d", even.y, even.x);
           return true;
	} else if (even.bstate & BUTTON2_PRESSED) {
           mvprintw(2, 0, "Middle button pressed at Y: %d, X: %d", even.y, even.x);
           return  true;
        } else if (even.bstate & BUTTON1_RELEASED ){
           mvprintw(3, 0, "RELESEAD ! Y: %d, X: %d", even.y, even.x);
           return true;
        } else if (even.bstate & BUTTON3_PRESSED) {
           mvprintw(2, 0, "Right button pressed at Y: %d, X: %d", even.y, even.x);
           return true;
        }

      return false;
}

bool onKeyEvent ( char ch ){
	
        if( ch == 'c' ){
		clear();

        }else if( ch == 'h' ){
		clHelp();
		move(15,5);
		clTest();

	}else if( ch == '!' ){ // start thread
		pthread_create( &dogTest1, NULL, myDogTest, NULL);
		//dog_create("gogo");

	}else if( ch == '@' ){ // kill thread
		pthread_cancel( dogTest1 );

	}else if( ch == 't' ){ // time A
		onClockUpdate();
	
	}else if( ch == 'b' ){ // battery local / laptop
		onBatteryUpdate();

	}else if( ch == 'C' ){
		mvprintw( 1,5, "[cmd] [%s]", cmd_to_chars("cal") );

	}else if( ch == 'f' ){
		mvprintw( 1,5, "[F] %s",file_read_to_chars("/tmp/d") );

	}

        mvprintw(row-1, 0, "Char key press: [ %c ]", ch);

	return false;
}

int main(void) {
    MEVENT event;
    bool doRefresh = false;
    int ch;

    ncursInit();	    
    attron( A_REVERSE );
    mvprintw(1, 0, "1Click the mouse or press 'q' to exit size[ %i x %i]", row, col );
    attroff( A_REVERSE );

    cl("OK!");

    refresh();

    pthread_t ptBat;
    pthread_create( &ptBat, NULL, dogBattery, NULL );
    pthread_t ptClock;
    pthread_create( &ptClock, NULL, dogClock, NULL );


    while ((ch = getch()) != 'q') {


        if( ch == KEY_MOUSE && getmouse(&event) == OK ){
                // Clear previous message
                move(2, 0);
                clrtoeol();
		doRefresh = onMouseEvent( event );
            
	}

	onKeyEvent( ch );

	if( doRefresh ){
        	refresh(); // Update the screen with new information
		doRefresh = false;
	}
    }

    // End curses mode
    endwin();
    return 0;
}



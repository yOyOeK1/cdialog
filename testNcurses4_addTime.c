#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>

#include "fileh.h"
#include "timeh.h"
#include "cmdh.h"


int row,col;

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
		"\nq - 	as Quit"
	);

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
	}else if( ch == 't' ){ // time 
		mvprintw( 0,0, "%s",time_now_tt() );
	}else if( ch == 'b' ){ // battery local / laptop
		mvprintw( 0,17, "󰄌%s%%",file_read_to_chars("/sys/class/power_supply/BAT0/capacity") );
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



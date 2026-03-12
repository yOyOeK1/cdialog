#include <ncurses.h>
#include <stdlib.h>


void ncursInit(){
    // Start curses mode
    initscr();
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
	mvprintw( 7, 0, "[cl] ◔ ◔ \uf240 nf-fa-battery  [%s]", msg );
}


int main(void) {
    MEVENT event;
    bool doRefresh = false;
    int ch;

    ncursInit();	    
   
    mvprintw(1, 0, "1Click the mouse or press 'q' to exit");
    
    cl("OK!");

    refresh();

    while ((ch = getch()) != 'q') {
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                // Clear previous message
                move(2, 0);
                clrtoeol();

                // Check button states and display coordinates
                if (event.bstate & BUTTON1_PRESSED) {
                    mvprintw(2, 0, "Left button pressed at Y: %d, X: %d", event.y, event.x);
                    doRefresh = true;
		} else if (event.bstate & BUTTON2_PRESSED) {
                    mvprintw(2, 0, "Middle button pressed at Y: %d, X: %d", event.y, event.x);
                    doRefresh = true;
                } else if (event.bstate & BUTTON1_RELEASED ){
                    mvprintw(3, 0, "RELESEAD ! Y: %d, X: %d", event.y, event.x);
                    doRefresh = true;
                } else if (event.bstate & BUTTON3_PRESSED) {
                    mvprintw(2, 0, "Right button pressed at Y: %d, X: %d", event.y, event.x);
                    doRefresh = true;
                }
                // Handle other events like BUTTON4_PRESSED for mouse wheel up, etc.
            }
        }
        mvprintw(4, 0, "Char key press: [ %c ]", ch);
	if( doRefresh ){
        	refresh(); // Update the screen with new information
		doRefresh = false;
	}
    }

    // End curses mode
    endwin();
    return 0;
}



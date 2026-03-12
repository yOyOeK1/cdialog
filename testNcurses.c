#include <ncurses.h>
#include <stdlib.h>

int main(void) {
    MEVENT event;
    int ch;

    // Start curses mode
    initscr();
    // Disable echoing of characters to the screen
    noecho();
    // Allow ncurses to capture special keys (like arrow keys and KEY_MOUSE)
    keypad(stdscr, TRUE);
    // Hide the cursor
    curs_set(0);

    // Enable all mouse events and position reporting
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    mvprintw(0, 0, "Click the mouse or press 'q' to exit");
    refresh();

    while ((ch = getch()) != 'q') {
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                // Clear previous message
                move(1, 0);
                clrtoeol();

                // Check button states and display coordinates
                if (event.bstate & BUTTON1_PRESSED) {
                    mvprintw(1, 0, "Left button pressed at Y: %d, X: %d", event.y, event.x);
                } else if (event.bstate & BUTTON2_PRESSED) {
                    mvprintw(1, 0, "Middle button pressed at Y: %d, X: %d", event.y, event.x);
                } else if (event.bstate & BUTTON3_PRESSED) {
                    mvprintw(1, 0, "Right button pressed at Y: %d, X: %d", event.y, event.x);
                }
                // Handle other events like BUTTON4_PRESSED for mouse wheel up, etc.
            }
        }
        refresh(); // Update the screen with new information
    }

    // End curses mode
    endwin();
    return 0;
}



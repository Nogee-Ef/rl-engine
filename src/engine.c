#include <rogue.h>

void cursesSetup(void)
{
    initscr(); // Sets up curses.
    noecho(); // Prevents curses from immediately drawing.
    curs_set(0); // Makes the cursor invisible.
}

void gameLoop(void)
{
    int ch;

    drawEverything();

    // getch() takes a single character input from the keyboard.
    while(ch = getch())
    { 
        if (ch == 'q')
        { 
            break;
        } 

        handleInput(ch);
        drawEverything();
    } 
}

void closeGame(void)
{
    endwin(); // Closes curses in the terminal.
    free(player);
}
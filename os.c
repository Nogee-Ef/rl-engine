#include "main.h"

#ifdef _WIN32
    #include <Windows.h>

    void enableVirtualTerminalProcessing(void) {
        HANDLE h_ouput = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dw_mode;
        GetConsoleMode(h_ouput, &dw_mode);
        SetConsoleMode(h_ouput, dw_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    static unsigned int codepage;
    void displaySetup(void) {
        enableVirtualTerminalProcessing();
        codepage = GetConsoleOutputCP();
        SetConsoleOutputCP(CP_UTF8);

        printf(HIDE);
        printf(CLEAR);
    }

    void onExit(void) {
        // It might also be a good idea to reverse enableVirtualTerminalProcessing.
        SetConsoleOutputCP(codepage);
    }

    void moveCursor(int x, int y) {
        COORD coord = { .X = x, .Y = y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    int getInput(void) {
        return _getch();
    }
#elif defined(__APPLE__) && defined(__MACH__)
    #include <termios.h>
    #include <unistd.h>

    static struct termios old_settings, new_settings;
    void displaySetup(void) {
        tcgetattr(STDIN_FILENO, &old_settings);
        new_settings = old_settings;
        new_settings.c_lflag &= ~ICANON; // Disable canonical input processing.
        new_settings.c_lflag &= ~ECHO; // Disable echo.
        tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

        printf("\x1b[8;33;102t"); // Resizes the terminal to 102 x 33.
        printf(HIDE);
        printf(CLEAR);
    }

    void onExit(void) {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    }

    void moveCursor(int x, int y) {
        printf("\x1b[%d;%dH", y+1, x+1);
    }

    int getInput(void) {
        return getchar();
    }
#endif
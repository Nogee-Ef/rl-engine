#include "main.h"

#ifdef _WIN32
    #include <Windows.h>

    void enableVirtualTerminalProcessing(void) {
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode;
        GetConsoleMode(hOuput, &dwMode);
        SetConsoleMode(hOuput, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    static uint codepage;
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

    static struct termios oldSettings, newSettings;
    void displaySetup(void) {
        tcgetattr(STDIN_FILENO, &oldSettings);
        newSettings = oldSettings;
        newSettings.c_lflag &= ~ICANON; // Disable canonical input processing.
        newSettings.c_lflag &= ~ECHO; // Disable echo.
        tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

        printf(HIDE);
        printf(CLEAR);
    }

    void onExit(void) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    }

    void moveCursor(int x, int y) {
        printf("\x1b[%d;%dH", y+1, x+1);
    }

    int getInput(void) {
        return getchar();
    }
#endif
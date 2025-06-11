#include "main.h"

#ifdef _WIN32
    #include <Windows.h>
    void enableVirtualTerminalProcessing(void) {
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode;
        GetConsoleMode(hOuput, &dwMode);
        SetConsoleMode(hOuput, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }

    void displaySetup(void) {
        enableVirtualTerminalProcessing();
        SetConsoleOutputCP(CP_UTF8);
        printf(HIDE);
        printf(CLEAR);
    }

    void moveCursor(int x, int y) {
        COORD coord = { .X = x, .Y = y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    int getInput(void) {
        return _getch();
    }
#elif defined(__APPLE__) && defined(__MACH__)
    void displaySetup(void) {
        printf(HIDE);
        printf(CLEAR);
    }

    void moveCursor(int x, int y) {
        printf("\x1b[%d;%dH", y+1, x+1);
    }

    int getInput(void) {
        return getchar();
    }
#endif
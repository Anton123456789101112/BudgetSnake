#include "consoleSetup.h"
#include <windows.h>

void setupConsole()
{
    SetConsoleOutputCP(CP_UTF8);  // UTF-8 (å, ä, ö)
    SetConsoleTitleW(L"🐍 BudgetSnake 🐍");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Change visual screen size
    SMALL_RECT windowSize = {0, 0, 114, 40}; // x1, y1, x2, y2
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Hide the annoying blinkering rectangle cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Change to true if you wan't it back
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

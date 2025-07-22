#include "draw.h"
#include <iostream>
#include <windows.h> // For WORD
#include <string>

void Draw(std::string Str, int X, int Y, WORD color)
{
    HANDLE OutputH;
    COORD position = { static_cast<SHORT>(X), static_cast<SHORT>(Y) };
    OutputH = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(OutputH, color);
    SetConsoleCursorPosition(OutputH, position);
    std::cout << Str;
}

void drawIntroText()
{
    Draw("    ", 20, 6, 224);
    Draw("  ", 20, 7, 224);
    Draw("    ", 20, 8, 224);
    Draw("  ", 20, 9, 224);
    Draw("    ", 20, 10, 224);
    Draw("  ", 24, 7, 224);
    Draw("  ", 24, 9, 224);

    Draw("  ", 28, 6, 224);
    Draw("  ", 28, 7, 224);
    Draw("  ", 28, 8, 224);
    Draw("  ", 28, 9, 224);
    Draw("      ", 28, 10, 224);
    Draw("  ", 32, 6, 224);
    Draw("  ", 32, 7, 224);
    Draw("  ", 32, 8, 224);
    Draw("  ", 32, 9, 224);

    Draw("    ", 36, 6, 224);
    Draw("  ", 36, 7, 224);
    Draw("  ", 36, 8, 224);
    Draw("  ", 36, 9, 224);
    Draw("    ", 36, 10, 224);
    Draw("  ", 40, 7, 224);
    Draw("  ", 40, 8, 224);
    Draw("  ", 40, 9, 224);

    Draw("      ", 44, 6, 224);
    Draw("  ", 44, 7, 224);
    Draw("  ", 44, 8, 224);
    Draw("  ", 44, 9, 224);
    Draw("      ", 44, 10, 224);
    Draw("  ", 48, 8, 224);
    Draw("  ", 48, 9, 224);

    Draw("      ", 52, 6, 224);
    Draw("  ", 52, 7, 224);
    Draw("      ", 52, 8, 224);
    Draw("  ", 52, 9, 224);
    Draw("      ", 52, 10, 224);

    Draw("      ", 60, 6, 224);
    Draw("  ", 62, 7, 224);
    Draw("  ", 62, 8, 224);
    Draw("  ", 62, 9, 224);
    Draw("  ", 62, 10, 224);

    Draw("SNAKE", 66, 10, 190);

    Draw("Use WASD to move", 20, 17, 190);
    Draw("Don't touch the WALLS!", 20, 19, 190);
}

void drawGameOverText()
{
    Draw("      ", 20, 6, 224);
    Draw("  ", 20, 7, 224);
    Draw("  ", 20, 8, 224);
    Draw("  ", 20, 9, 224);
    Draw("      ", 20, 10, 224);
    Draw("  ", 24, 8, 224);
    Draw("  ", 24, 9, 224);

    Draw("      ", 28, 6, 224);
    Draw("  ", 28, 7, 224);
    Draw("      ", 28, 8, 224);
    Draw("  ", 28, 9, 224);
    Draw("  ", 28, 10, 224);
    Draw("  ", 32, 7, 224);
    Draw("  ", 32, 9, 224);
    Draw("  ", 32, 10, 224);

    Draw("          ", 36, 6, 224);
    Draw("  ", 36, 7, 224);
    Draw("  ", 36, 8, 224);
    Draw("  ", 36, 9, 224);
    Draw("  ", 36, 10, 224);
    Draw("  ", 40, 7, 224);
    Draw("  ", 40, 8, 224);
    Draw("  ", 40, 9, 224);
    Draw("  ", 40, 10, 224);
    Draw("  ", 44, 7, 224);
    Draw("  ", 44, 8, 224);
    Draw("  ", 44, 9, 224);
    Draw("  ", 44, 10, 224);

    Draw("      ", 48, 6, 224);
    Draw("  ", 48, 7, 224);
    Draw("      ", 48, 8, 224);
    Draw("  ", 48, 9, 224);
    Draw("      ", 48, 10, 224);

    Draw("      ", 58, 6, 224);
    Draw("  ", 58, 7, 224);
    Draw("  ", 58, 8, 224);
    Draw("  ", 58, 9, 224);
    Draw("      ", 58, 10, 224);
    Draw("  ", 62, 8, 224);
    Draw("  ", 62, 9, 224);
    Draw("  ", 62, 7, 224);

    Draw("  ", 66, 6, 224);
    Draw("  ", 66, 7, 224);
    Draw("  ", 66, 8, 224);
    Draw("  ", 66, 9, 224);
    Draw("  ", 68, 10, 224);
    Draw("  ", 70, 6, 224);
    Draw("  ", 70, 7, 224);
    Draw("  ", 70, 8, 224);
    Draw("  ", 70, 9, 224);

    Draw("      ", 74, 6, 224);
    Draw("  ", 74, 7, 224);
    Draw("      ", 74, 8, 224);
    Draw("  ", 74, 9, 224);
    Draw("      ", 74, 10, 224);

    Draw("      ", 82, 6, 224);
    Draw("  ", 82, 7, 224);
    Draw("  ", 82, 8, 224);
    Draw("      ", 82, 9, 224);
    Draw("  ", 82, 10, 224);
    Draw("  ", 88, 7, 224);
    Draw("  ", 88, 8, 224);
    Draw("  ", 88, 10, 224);
}

// Aqua box animation
void boxAnimation()
{
    for(int X { 16 }, Y = 3; Y < 29; X++)
    {
        Draw(" ", X, Y, 176);
        if(X == 105)
        {
            Sleep(1);
            Y++;
            X = 15; // 15, Otherwise weird
        }
    }

    Draw("Press       to Start", 20, 25, 190);
    Draw("SPACE", 26, 25, 246);
}

// Erase all graphics/draw functions
void eraseAll()
{
    // Change i to according screen lenght/y-level
    for(int i{}; i < 31; i++)
    {
        Draw("                                                                                                            ", 0, i, 0);
    }
}



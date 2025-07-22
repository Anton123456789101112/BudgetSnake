#pragma once

#include <string>
#include <windows.h> // For WORD

void Draw(std::string Str, int X, int Y, WORD color);
void drawIntroText();
void drawGameOverText();
void eraseAll();
void boxAnimation();

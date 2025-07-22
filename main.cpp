#include "collision.h"
#include "consoleSetup.h"
#include "draw.h"
#include "sounds.h"
#include <iostream>
#include <windows.h>
#include <thread>   // For soundeffects

enum Direction { NONE, UP, DOWN, LEFT, RIGHT }; // Use enum to lessen the amount of if-statements for input

structCollision collision;

// Put the classes in seperate files eventually...
// Need to put enum Direction in it's own file if so

class ClassPlayer
{
public:
    // Start position
    int PlayerX { 60 };
    int PlayerY { 15 };

    // Start speed, also need DWORD so you can
    // compare the timers- can't compare int and DWORD
    DWORD PlayerSpeed { 90 };

    Direction direction = NONE;

    void MovePlayerUp()    { PlayerY--; }
    void MovePlayerDown()  { PlayerY++; }
    void MovePlayerRight() { PlayerX++; }
    void MovePlayerLeft()  { PlayerX--; }

    void Move()
    {
        switch(direction)
        {
            case UP:    MovePlayerUp();    break;
            case DOWN:  MovePlayerDown();  break;
            case LEFT:  MovePlayerLeft();  break;
            case RIGHT: MovePlayerRight(); break;
            default: break;
        }
    }
    void DrawPlayer()  { Draw("  ", PlayerX, PlayerY, 144); }
    void ErasePlayer() { Draw("  ", PlayerX, PlayerY, 0);   }
};

class ClassApple
{
public:
    int AppleX{};
    int AppleY{};

    void Respawn()
    {
        // Add do while loop so it doesn't spawn inside the walls
        // do while loop is like a while loop but ALWAYS runs atleast once
        do
        {
            AppleX = rand() % (collision.WallRight - collision.WallLeft - 1) + collision.WallLeft + 1;
            AppleY = rand() % (collision.WallDown - collision.WallUp - 1) + collision.WallUp + 1;
        }
        while((AppleX == collision.WallLeft + 1) || (AppleX == collision.WallRight - 1) || 
        (AppleY == collision.WallUp + 1) || (AppleY == collision.WallDown - 1));
    }

    void DrawApple()  { Draw("  ", AppleX, AppleY, 64); }
    void EraseApple() { Draw("  ", AppleX, AppleY, 0);  }

};

class ClassTimers
{
public:
    // Have to use DWORD not int, idk why
    DWORD PlayerTimer1{};
    DWORD PlayerTimer2{};
    DWORD PlayerElapsed{};

    DWORD AppleTimer1{};
    DWORD AppleTimer2{};
    DWORD AppleElapsed{};    

    void UpdateTimers()
    {
        PlayerTimer2 = GetTickCount();                             
        PlayerElapsed =  PlayerTimer2 - PlayerTimer1;             
        AppleTimer2 = GetTickCount();                              
        AppleElapsed =  AppleTimer2 - AppleTimer1;                
    }
    void startTimers()
    {
        PlayerTimer1 = GetTickCount();      
        AppleTimer1 = GetTickCount();       
    }
    void resetAppleTimer()
    {
        AppleTimer1 = GetTickCount();
        AppleElapsed = 0;
    }
    void resetPlayerTimer()
    {
        PlayerTimer1 = GetTickCount();
        PlayerElapsed = 0;
    }

};

// Put in different files?
void DrawMenu(void);
void DrawBackground(void);

void HandleInput(void);
void UpdatePlayer(void);
void CheckAppleCollision(void); 
void CheckWallCollision(void);
void IncreasePlayerSpeed(void);

ClassTimers timer;
ClassApple apple;
ClassPlayer player;

// Global - bad!
int Score{};
int VisualSpeed{ 1 };

bool GameOver = false;
bool DoOnce = false;


int main()
{
    setupConsole();

    srand(GetTickCount());
    DrawMenu();
    timer.startTimers();

    while(1) // Game Loop
    {
        timer.UpdateTimers();
        HandleInput();
        UpdatePlayer();
        CheckAppleCollision();
        CheckWallCollision();
        IncreasePlayerSpeed();
    }
}

void IncreasePlayerSpeed()
{
    // Increase player speed, if you are moving, and if you haven't reached the speed limit
    // Speed limit exist, because after 16 the game gets weird flashes
    if((timer.AppleElapsed > 2500) && (VisualSpeed < 17) && (player.direction != NONE)) 
    {
        // Ugly fix- because visualspeed and playerspeed increases to two while standing still, why idk
        // I think the ugly fix slows down the 3 sec visual speed update the first time
        if(DoOnce == false)
        {
            player.PlayerSpeed += 5;
            VisualSpeed--;
            DoOnce = true;
        }
        player.PlayerSpeed -= 5;
        VisualSpeed++;
        timer.resetAppleTimer();
    }
}

void CheckWallCollision()
{
    if((player.PlayerX == collision.WallRight - 1) || (player.PlayerX == collision.WallLeft + 1) || 
    (player.PlayerY == collision.WallUp) || (player.PlayerY == collision.WallDown))
    {
        std::thread BreakT(BreakV);
        Sleep(1000);
        BreakT.join();
        std::thread GameOverT(GameOverV);

        GameOver = true;
        DoOnce = false;

        DrawMenu();
        GameOverT.join();
    }
}

void CheckAppleCollision()
{
    if((player.PlayerX == apple.AppleX) && (player.PlayerY == apple.AppleY))
    {
        std::thread CrunchT(CrunchV);
        Score++;
        apple.EraseApple();
        apple.Respawn();
        CrunchT.join();
    }
}

void UpdatePlayer()
{
    if ((timer.PlayerElapsed > player.PlayerSpeed) && (player.direction != NONE))
    {
        player.ErasePlayer();
        player.Move();
        DrawBackground(); // Redraw the map because the player erases it
        player.DrawPlayer();
        apple.DrawApple(); // Redraw apple so it doesn't get half eaten
        timer.resetPlayerTimer();
    }
}

void HandleInput()
{
    if (GetAsyncKeyState(0x57) && player.direction != DOWN)        // W
        player.direction = UP;
    else if (GetAsyncKeyState(0x53) && player.direction != UP)     // S
        player.direction = DOWN;
    else if (GetAsyncKeyState(0x41) && player.direction != RIGHT)  // A
        player.direction = LEFT;
    else if (GetAsyncKeyState(0x44) && player.direction != LEFT)   // D
        player.direction = RIGHT;
}

void DrawMenu()
{
    boxAnimation();

    if(GameOver == true)
    {
        drawGameOverText();

        Draw("Score:", 20, 15, 190);
        Draw(" ", 26, 15, 180);
        std::cout << Score << std::endl;
        Draw("Speed:", 20, 17, 190);
        Draw(" ", 26, 17, 189);
        std::cout << VisualSpeed << 'x' << std::endl;

        // Stop player movement
        player.direction = NONE;

        // Reset player and apple position
        player.PlayerX = 60;
        player.PlayerY = 15;

        // Reset Visual speed and Score
        Score = 0;
        VisualSpeed = 1;

        timer.resetAppleTimer();
        timer.resetPlayerTimer();

    }
    else if(GameOver == false)
       drawIntroText();


    while(!GetAsyncKeyState(0x20)) // Wait for input to continue (space)
        Sleep(10);

    eraseAll();

    apple.Respawn();

    // Reset player speed
    player.PlayerSpeed = 90;

    DrawBackground();

    player.DrawPlayer();
    apple.DrawApple();

    Sleep(500);
}


void DrawBackground()
{
    Draw("Score:", 38, 3, 15);
    Draw(" ", 44, 3, 4);
    std::cout << Score << std::endl;
    Draw("Speed:", 50, 3, 15);
    Draw(" ", 56, 3, 13);
    std::cout << VisualSpeed << 'x' << std::endl;

    //Top and bottom walls
    Draw("                                             ", collision.WallLeft, collision.WallUp, 240);
    Draw("                                             ", collision.WallLeft, collision.WallDown, 240);

    // Side walls and green
    // Create walls, for loop instead of 10000 draw functions
    for(int L { 5 }; L < 26; L++)
    {
        Draw("  ", collision.WallLeft, L, 240);
        Draw("  ", collision.WallRight, L, 240);
        Draw("                                         ", collision.WallLeft + 2, L, 160);
    }
}






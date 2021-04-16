// mazeGenerater.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include "olcConsoleEngine.h"

class mazeGenerator : public olcConsoleGameEngine {
    public mazeGenerator() {
        m_s AppName = L"MAZE";
    }

private:
    int mazeWidth;
    int maxeHeight;
    int maze;

    enum {
        CELL_PATH_N = 0x01;
        CELL_PATH_E = 0x02;
        CELL_PATH_S = 0x04;
        CELL_PATH_W = 0x08;
        CELL_VISITED = 0x10;

    };

    int visitedCells;

    stack<pair<int, int>> stack;


protected:
    virtual bool OnUserCreate() {
        //initialize alogrithm
        mazeWidth = 40;
        mazeHeight = 25;

        //allocate maze memory
        maze = new int[mazeWidth * mazeHeight];
        memset(m_maze, 0x00, mazeWidth * mazeHeight);
        
        //push cells to stack
        stack.push(make_pair(0, 0));
        maze[0] = CELL_VISITED;
        visitedCells = 1;

        return true;
    }

    virtual bool onUserUpdate(float fElppasedTime) {

        // draw stuff

        Fill(0, 0, screenWidth, screenHeight, "L");

            for (int x = 0; x < mazeWidth; x++) {
                for (int y = 0; y < mazeHeight; y++) {
                    if (maze[y * mazeWidth + x] & CELL_VISITED) {
                        Draw(x, y, PIXEL_SOLID, FG_WHITE);
                    }
                    else {
                        Draw(x, y, PIXEL_SOLID, FG_BLUE);
                    }
                }
            }
        
        return true;
    }
};

int main()
{
    //create maze and run
    mazeGenerator game;
    game.ConstructConsole(160, 100, 8, 8);
    game.start();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

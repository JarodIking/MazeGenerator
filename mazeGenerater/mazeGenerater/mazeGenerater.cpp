// mazeGenerater.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include <iostream>
#include <stack>
using namespace std;


#include "olcConsoleEngine.h"


class mazeGenerator : public olcConsoleGameEngine {
    public: 
    
    mazeGenerator(){
        m_sAppName = L"MAZE";
    }

private:
    int m_nMazeWidth;
    int m_nMazeHeight;
    int *m_maze;

    enum{
        CELL_PATH_N = 0x01,
        CELL_PATH_E = 0x02,
        CELL_PATH_S = 0x04,
        CELL_PATH_W = 0x08,
        CELL_VISITED = 0x10,
    };

    int m_nVisitedCells;

    stack<pair<int , int>> m_stack;	// (x, y) coordinate pairs


protected:
    virtual bool OnUserCreate() {
        //initialize alogrithm
        m_nMazeWidth = 40;
        m_nMazeHeight = 25;

        //allocate maze memory
        m_maze = new int[m_nMazeWidth * m_nMazeHeight];
        memset(m_maze, 0x00, m_nMazeWidth * m_nMazeHeight);
        
        //push cells to stack
        m_stack.push(make_pair(0, 0));
        m_maze[0] = CELL_VISITED;
        m_nVisitedCells = 1;

        return true;
    }

     bool OnUserUpdate(float fElppasedTime) override {

        // draw stuff

        Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

            for (int x = 0; x < m_nMazeWidth; x++) {
                for (int y = 0; y < m_nMazeHeight; y++) {
                    if (m_maze[y * m_nMazeWidth + x] & CELL_VISITED) {
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
    game.Start();

    return 0;
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

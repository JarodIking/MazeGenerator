// mazeGenerater.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stack>
#include <vector>
#include <conio.h>
#include <windows.h>
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

    int m_nPathWidth;


protected:
    bool OnUserCreate() {
        // Maze parameters
        m_nMazeWidth = 30;
        m_nMazeHeight = 30;
        m_maze = new int[m_nMazeWidth * m_nMazeHeight];
        memset(m_maze, 0x00, m_nMazeWidth * m_nMazeHeight * sizeof(int));
        m_nPathWidth = 3;

        // Choose a starting cell
        int x = rand() % m_nMazeWidth;
        int y = rand() % m_nMazeHeight;
        m_stack.push(make_pair(x, y));
        m_maze[y * m_nMazeWidth + x] = CELL_VISITED;
        m_nVisitedCells = 1;

        return true;
    }

     bool OnUserUpdate(float fElppasedTime) override {
         //do maze algorithm
         if (m_nVisitedCells < m_nMazeWidth * m_nMazeHeight) {
             //step 1: Create a set of the unvisited neighbours

             auto offset = [&](int x, int y) {
                 return (m_stack.top().second + y) * m_nMazeWidth + (m_stack.top().first + x);
             };


             vector<int> neighbours;
             //north neighbour
             if (m_stack.top().second > 0 && (m_maze[offset(0, -1)] & CELL_VISITED) == 0)
                 neighbours.push_back(0);
                   
             //east neighbour
             if (m_stack.top().first < m_nMazeWidth - 1 && (m_maze[offset(1, 0)] & CELL_VISITED) == 0) 
                 neighbours.push_back(1);
             
             //south neighbour
             if (m_stack.top().second < m_nMazeWidth -1 && (m_maze[offset(0, 1)] & CELL_VISITED) == 0) 
                 neighbours.push_back(2);
             
             //south neighbour
             if (m_stack.top().first > 0 && (m_maze[offset(-1, 0)] & CELL_VISITED) == 0) 
                 neighbours.push_back(3);
             

             //are there any neighbours available?
             if (!neighbours.empty()) {
                 //choose one neighbour at random 
                 int next_cell_dir = neighbours[rand() % neighbours.size()];

                 //create a path between the neighbour and the current cell
                 switch (next_cell_dir)
                 {
                 case 0: //north
                     m_maze[offset(0, -1)] |= CELL_VISITED | CELL_PATH_S;
                     m_maze[offset(0, 0)] |= CELL_PATH_N;
                     m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second - 1)));
                     break;

                 case 1: //east
                     m_maze[offset(+1, 0)] |= CELL_VISITED | CELL_PATH_W;
                     m_maze[offset(0, 0)] |= CELL_PATH_E;
                     m_stack.push(make_pair((m_stack.top().first + 1), (m_stack.top().second + 0)));
                     break;

                 case 2: //south
                     m_maze[offset(0, +1)] |= CELL_VISITED | CELL_PATH_N;
                     m_maze[offset(0, 0)] |= CELL_PATH_S;
                     m_stack.push(make_pair((m_stack.top().first + 0), (m_stack.top().second + 1)));
                     break;

                 case 3: //west
                     m_maze[offset(-1, 0)] |= CELL_VISITED | CELL_PATH_E;
                     m_maze[offset(0, 0)] |= CELL_PATH_E;
                     m_stack.push(make_pair((m_stack.top().first - 1), (m_stack.top().second + 0)));
                     break;

                     //default:
                         //break;
                 }

                 //new cell
                 m_maze[offset(0, 0)] |= CELL_VISITED;
                 m_nVisitedCells++;
             }
             else {
                 m_stack.pop(); //Backtrack
             }

             

         }
         


        // draw stuff

        Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

            for (int x = 0; x < m_nMazeWidth; x++) {
                for (int y = 0; y < m_nMazeHeight; y++) {
                    for (int py = 0; py < m_nPathWidth; py++) {
                        for (int px = 0; px < m_nPathWidth; px++) {
                            if (m_maze[y * m_nMazeWidth + x] & CELL_VISITED) {
                                Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, PIXEL_SOLID, FG_WHITE);
                            }
                            else {
                                Draw(x * (m_nPathWidth + 1) + px, y * (m_nPathWidth + 1) + py, PIXEL_SOLID, FG_BLUE);
                            }
                        }

                        for (int p = 0; p < m_nPathWidth; p++) {
                            if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_S)
                                Draw(x * (m_nPathWidth + 1) + p, y * (m_nPathWidth + 1) + m_nPathWidth);


                            if (m_maze[y * m_nMazeWidth + x] & CELL_PATH_E)
                                Draw(x * (m_nPathWidth + 1) + m_nPathWidth, y * (m_nPathWidth + 1) + p);


                        }
                    }
                }
            }
        
        return true;
    }
};

int main()
{
    system("Color 1A");
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

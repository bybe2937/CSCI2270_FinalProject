/*
Byron Bearden
Luke Sassu
Final Project
4/21/15
*/

#include <iostream>
#include "nodeSud.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#define N 9
#define UNASSIGNED 0
using namespace std;

// Function Definitions
bool solveCurrent(int grid[N][N]);
bool findFirstSpace(int grid[N][N], int &row, int &col);
bool inRow(int grid[N][N], int row, int num);
bool inCol(int grid[N][N], int col, int num);
bool inBox(int grid[N][N], int startRow, int startCol, int num);
bool safeCheck(int grid[N][N], int row, int col, int num);
void parseFile(string file, int grid[N][N]);
void printBoard(int grid[N][N]);

int main()
{
    // Three pre written puzzles
    int easy1[N][N] =
        {{0,0,6, 0,0,7 ,3,0,0},
        {0,1,8, 0,0,9, 0,5,0},
        {5,0,0, 0,0,0, 0,6,4},

        {9,2,0, 0,8,0, 0,0,0},
        {0,0,0, 7,6,3, 0,0,0},
        {0,0,0, 0,9,0, 0,7,5},

        {6,3,0, 0,0,0, 0,0,8},
        {0,9,0, 3,0,0, 5,2,0},
        {0,0,2, 4,0,0, 6,0,0}};
    int medium1[N][N] =
        {{0,9,0, 0,0,0, 0,0,8},
        {2,0,0, 0,0,0, 1,9,0},
        {4,0,0, 2,0,1, 0,0,0},

        {0,3,0, 0,0,6, 0,8,7},
        {0,0,0, 7,0,9, 0,0,0},
        {7,1,0, 8,0,0, 0,3,0},

        {0,0,0, 5,0,3, 0,0,6},
        {0,8,6, 0,0,0, 0,0,1},
        {5,0,0, 0,0,0, 0,7,0}};
    int hard1[N][N] =
        {{0,0,0, 0,0,0, 0,0,0},
        {0,0,0, 0,0,3, 0,8,5},
        {0,0,1, 0,2,0, 0,0,0},

        {0,0,0, 5,0,7, 0,0,0},
        {0,0,4, 0,0,0, 1,0,0},
        {0,9,0, 0,0,0, 0,0,0},

        {5,0,0, 0,0,0, 0,7,3},
        {0,0,2, 0,1,0, 0,0,0},
        {0,0,0, 0,4,0, 0,0,9}};
    // creation of the head node
    Node *head = new Node;
    head->previous = NULL;
    head->row = -1;
    head->col = -1;
    head->prevNum = -1;

    string choice;
    while(choice != "3")
    {
        cout << "===Welcome to Sudoku!===" << endl;                 // MAIN MENU
        cout << "1. Load existing board" << endl;
        cout << "2. Open a puzzle from file" << endl;
        cout << "3. Quit" << endl;
        cin >> choice;
        if(choice == "1")                             // LOAD BOARD
        {
            int currentArray[N][N];                                    // This will be our array that the user will change and solve
            string diff;
            cout << "What difficulty would you like? " << endl;
            cin >> diff;
            if(diff == "Easy"){                                         // this sets our currentarray equal to one of the three pre-existing puzzles and prints it
                for(int i = 0; i < N+1; i++)
                {
                    for(int j = 0; j < N+1; j++)
                    {
                        currentArray[i][j] = easy1[i][j];
                    }
                }
                printBoard(currentArray);
            }
            else if(diff == "Medium"){
                for(int i = 0; i < N+1; i++)
                {
                    for(int j = 0; j < N+1; j++)
                    {
                        currentArray[i][j] = medium1[i][j];
                    }
                }
                printBoard(medium1);
            }
            else if(diff == "Hard"){
                for(int i = 0; i < N+1; i++)
                {
                    for(int j = 0; j < N+1; j++)
                    {
                        currentArray[i][j] = hard1[i][j];
                    }
                }
                printBoard(hard1);
            }
            string choice2 = 0;

            while(choice2 != "4")                                       // once a baord has been loaded it will prompt the user to enter values or solve the board
            {
                cout << endl;
                cout << "1. Enter a value" << endl;
                cout << "2. Previous move" << endl;
                cout << "3. Solve Board" << endl;
                cout << "4. Previous Menu" << endl;
                if(choice2 == "1")
                {
                    int row;
                    int col;
                    int num;
                    string one;
                    string two;
                    string three;
                    cout << "What row?" << endl;
                    cin  >> one;
                    row = stoi(one);
                    cout << "What column?" << endl;
                    cin >> two;
                    col = stoi(two);
                    cout << "What value?" << endl;
                    cin >> three;
                    num = stoi(three);
                    int saveNum = currentArray[row][col];                           // this saves the previous number for our linked list to store
                    nodeSud::saveMove(head, row, col, saveNum);                     // We do this so the user can backtrack if they make a mistake
                    currentArray[row][col] = num;                                   // update array and print
                    printBoard(currentArray);
                }
                else if(choice2 == "2")                                             // undo the previous action and set the value back to the original
                {
                    int row2 = head->row;
                    int col2 = head->col;
                    int num2 = head->prevNum;
                    currentArray[row2][col2] = num2;
                    printBoard(currentArray);
                }
                else if(choice2 == "3")                                             // call the function  to solve the array and print it
                {
                    if(solveCurrent(currentArray))
                        printBoard(currentArray);
                }
            }
        }

        else if(choice == "2")                        // OPEN FROM FILE
        {
            int currentArray[N][N];
            string fileName;
            cout << "What is the name of the file you would like to open?" << endl;
            cin >> fileName;
            parseFile(fileName, currentArray);
            string choice2 = 0;

            while(choice2 != "4")                                       // once a baord has been loaded it will prompt the user to enter values or solve the board
            {
                cout << endl;
                cout << "1. Enter a value" << endl;
                cout << "2. Previous move" << endl;
                cout << "3. Solve Board" << endl;
                cout << "4. Previous Menu" << endl;
                if(choice2 == "1")
                {
                    int row;
                    int col;
                    int num;
                    string one;
                    string two;
                    string three;
                    cout << "What row?" << endl;
                    cin  >> one;
                    row = stoi(one);
                    cout << "What column?" << endl;
                    cin >> two;
                    col = stoi(two);
                    cout << "What value?" << endl;
                    cin >> three;
                    num = stoi(three);
                    int saveNum = currentArray[row][col];                           // this saves the previous number for our linked list to store
                    nodeSud::saveMove(head, row, col, saveNum);                     // We do this so the user can backtrack if they make a mistake
                    currentArray[row][col] = num;                                   // update array and print
                    printBoard(currentArray);
                }
                else if(choice2 == "2")                                             // undo the previous action and set the value back to the original
                {
                    int row2 = head->row;
                    int col2 = head->col;
                    int num2 = head->prevNum;
                    currentArray[row2][col2] = num2;
                    printBoard(currentArray);
                }
                else if(choice2 == "3")                                             // call the function  to solve the array and print it
                {
                    if(solveCurrent(currentArray))
                        printBoard(currentArray);
                }
            }

        }
    }
    cout << "Goodbye!" << endl;
}
/*
Function prototype:
    void parseFile(string file, grid[N][N]);
Function description:
    This function takes in a text file and converts all of the data into a new 2d array sudoku puzzle it then prints the puzzle
    so that the user may begin to make the first move
Example:
    parseFile(fileName, currentArray[][])
Precondition:
    the user must have given the function a textfile to read in data and it must use a preexisting array so it doesnt have
    to pass a 2d array
Post condition:
    N/A
*/
void parseFile(string file, int grid[N][N])
{
    int sudokuArray[N][N];
    ifstream in;
    in.open(file);
    string line;
    string col;
    string number;
    vector<string> indexes;
    while(getline(in, line))
    {
        int row = 0;
        int colNum = 0;
        istringstream linestream(line);
        getline(linestream, col, ',');
        while(getline(linestream, number, ','))
        {
            sudokuArray[row][colNum] = stoi(number);
            colNum++;
        }
        row++;
    }
    for(int i = 0; i < N+1; i++)
    {
        for(int j = 0; j < N+1; j++)
        {
            grid[i][j] = sudokuArray[i][j];
        }
    printBoard(grid);
    }
}
/*
Function prototype:
    void printBoard(int grid[N][N]);
Function description:
    This function simply prints out a 2s array in a nice formatted way
Example:
    printBoard(currentArray)
Precondition:
    N/A
Post condition:
    N/A
*/
void printBoard(int grid[N][N])
{
    cout << "  1  2  3     4  5  6     7  8  9" << endl;
	 //cout << "  -------------------------" << endl;
    int counter = -1;
	 for(int i = 0; i < 9; i++)
     {
        if((i+1) % 3 == 1)
             {
                 cout << "  =============================== ||" << endl;
             }
         for(int j = 0; j < 9; j++)
         {
             cout << "  " << grid[i][j];
             if((j-1) % 3 == 1)
             {
                 cout << " ||";
             }
             counter++;
         }
         cout << " " << i+1 << endl;
     }
}
/*
Function prototype:
    bool solveCurrent(int grid[N][N])
Function description:
    This function calls a series of algorithms in order to solve a currently unfinished sudoku puzzle
    it uses backtracking to place values in the empty spots until the baord is completely solved
Example:
    solvecurrent(currentArray)
Precondition:
    All spots in the puzzle that are incomplete must be initialized to zero
Post condition:
    the function returns a bool so it must print the board if it returns true
*/
bool solveCurrent(int grid[N][N])                                       // this function uses backtracking to find the true values
                                                                        // if it makes a mistake it backtracks to find other values that fit
{
    int row, col;

    if (!findFirstSpace(grid, row, col))
       return true;
    for (int num = 1; num <= 9; num++)
    {

        if (safeCheck(grid, row, col, num))
        {

            grid[row][col] = num;

            if (solveCurrent(grid))
                return true;

            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}
/*
Function prototype:
    bool findFirstSpace(int grid[N][N], int &row, int &col)
Function description:
    This function finds the first open spot to begin the process of
Example:
    findFirstSpace(currentArray, 3, 7)
Precondition: N/A
Post condition: N/A
*/
bool findFirstSpace(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}
/*
Function prototype:
    bool inRow(int grid[N][N], int row, int num)
Function description:
    checks if the number is in the row it lies within
Example:
    inRow(curretnArray, 3, 7)
Precondition: N/A
Post condition: N/A
*/
bool inRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}
/*
Function prototype:
    bool inCol(int grid[N][N], int col, int num)
Function description:
    checks if the number is in the col it lies within
Example:
    inCol(currentArray, 3, 7)
Precondition:
Post condition:
*/
bool inCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}
/*
Function prototype:
    bool inBox(int grid[N][N], int startRow, int startCol, int num)
Function description:
    checks if the number is in the box it lies within
Example:
    inBox(currentArray, 3, 7)
Precondition: N/A
Post condition: N/A
*/
bool inBox(int grid[N][N], int startRow, int startCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+startRow][col+startCol] == num)
                return true;
    return false;
}
/*
Function prototype:
    bool safeCheck(int grid[N][N], int row, int col, int num)
Function description:
    This function calls all of the in box row and col functions in order to check whether the number is allowed in that spot
Example:
    safeCheck(currentArray, 3, 7, 8)
Precondition: N/A
Post condition: N/A
*/
bool safeCheck(int grid[N][N], int row, int col, int num)
{
    return !inRow(grid, row, num) &&
           !inCol(grid, col, num) &&
           !inBox(grid, row - row%3 , col - col%3, num);
}

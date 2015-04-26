#include "nodeSud.h"

nodeSud::nodeSud()
{
    //ctor
}

nodeSud::~nodeSud()
{
    //dtor
}
/*
Function prototype:
    void previousMove(Node *headNode, int row, int col, int number);
Function description:
    This function allows the user to go back to their previous move through a linked list. The tail of the list holds the
    value of the old sudoku puzzle that was changed
Example:
    previousMove(head, 3, 7, 0)

Precondition:
    The user must have made a move before calling this function. head->previous != NULL
Post condition:
    The puzzle must be updated with the old value it used to hold.
*/
void previousMove(Node *headNode, int row, int col, int number)
{

}
/*
Function prototype:
    Node saveMove(Node *headNode, int row, int col, int number);
Function description:
    This function is called every time the user makes a new move so that in case they want to undo it they can call
    previousMove to fix it.
Example:
    saveMove(head, 3, 7, 8)
Precondition:
    the user must have just placed a new value in the puzzle
Post condition:
    the place of the move and the number must have been saved in a node at the end of the linked list
*/
Node saveMove(Node *headNode, int row, int col, int number)
{
    Node *x = new Node;
    x->prevNum = number;
    x->row = row;
    x->col = col;
    x->previous = headNode;
    headNode = x;
}

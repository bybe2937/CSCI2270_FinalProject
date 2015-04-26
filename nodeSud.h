#ifndef NODESUD_H
#define NODESUD_H

struct Node{
    int prevNum;
    int row;
    int col;
    Node *previous;
};

class nodeSud
{
    public:
        nodeSud();
        ~nodeSud();
        void previousMove(Node *headNode, int row, int col, int number);
        void saveMove(Node *headNode, int row, int col, int number);
    protected:
    private:
};

#endif // NODESUD_H

#ifndef BOARD_H
#define BOARD_H
#include "CharStack.h"
class Board
{
    struct slot {
        slot * next;
        slot * prev;
        CharStack slotStack;
        slot ()
        {} };
    private:
        slot * head;
        slot * tail;
        int xCnt;
        int oCnt;

    public:
    Board();
    bool noMove(char player, int move);
    int validMove(char player, int start, int steps, int direction);
    void movePiece(int source, int target);
    void printBoard();
    int evaluateGame();
    bool targetSlotFull(int slot);
    void destroySlot(int slot);
    void createSlotBegin(char player, int num);
    void createSlotEnd(char player, int num);
    void createEmptySlotEnd();
    void clearBoard();
};

#endif

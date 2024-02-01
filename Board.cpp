#include <iostream>
#include <string>
#include "Board.h"
using namespace std;
/******************************************************************************
Purpose: This program is CS204 Homework 3
Usage: feedback.h,feedback.cpp
Author: Maryam Baig 30454
Date: 13/4/2023
******************************************************************************/
///empty board constructor
Board::Board()
{
    head = NULL;
    tail = NULL;
    xCnt = 0;
    oCnt = 0;
}
/*****************************************************************************
This function checks there is any possible move the player can make
*****************************************************************************/
bool Board::noMove(char player, int steps)
{
    slot *current=head;
    int count=0;
    while(current != NULL)
    {
        count++;
        current=current->next;
    }
    slot *current1=head,*target=head,*target1=head;
    char variable;
    for(int i=0; i<count; i++)
    {
        //if steps<count-i-1
        //if steps<i
        if(!(current1->slotStack.isEmpty()))
        {
            current1->slotStack.pop(variable);
            current1->slotStack.push(variable);
            if(variable==player )
            {
                if(steps<=(count-i-1)) {
                    for (int j = 0; j < steps; j++) {
                        if (target->next != NULL) {
                            target = target->next;
                        }
                    }
                    char variable1 = ' ';
                    if (target->slotStack.isEmpty()) {
                        return false;
                    } else {
                        target->slotStack.pop(variable1);
                        target->slotStack.push(variable1);
                        if ((variable1 == player) ) {
                            return false;
                        }
                    }
                }
                if(steps<=i) {
                    for (int j = 0; j < steps; j++) {
                        if (target1->prev != NULL) {
                            target1 = target1->prev;
                        }
                    }
                    char variable2 = ' ';
                    if (target1->slotStack.isEmpty()) {
                        return false;
                    } else {
                        target1->slotStack.pop(variable2);
                        target1->slotStack.push(variable2);
                        if ((variable2 == player) ) {
                            return false;
                        }
                    }
                }
            }

        }
        current1=current1->next;
        target=current1;
        target1=current1;
    }


    return true;
}
/*****************************************************************************
This function checks if the players inputed move is valid
*****************************************************************************/
int Board::validMove(char player, int start, int steps, int direction)
{
    int count=0;
    slot *current=head;
    while(current != NULL)
    {
        count++;
        current=current->next;
    }

    if(start>=count)
    {
        return 1;
    }

    slot *startnode=head;
    slot *targetnode=head;
    for(int i=0; i<start; i++)
    {
        startnode =startnode->next;
        targetnode=targetnode->next;
    }

    char variable=' ';
    ///if empty
    if(startnode->slotStack.isEmpty()){
        return 4;
    }
    else
    {
        startnode->slotStack.pop(variable);
        startnode->slotStack.push(variable);
        if( variable != player  )
        {

            return 4;
        }
    }


    if(direction == 1){
        if((start+steps)>count)
        {
            return 2;
        }
    }

    if(direction == 0){
        if((steps>start))
        {
            return 2;
        }
    }

    if(direction ==1){
        for(int i=0; i<steps; i++)
        {
            targetnode =targetnode->next;
        }
    }

    if(direction ==0)
    {
        for(int i=0; i<steps; i++)
        {
            if (targetnode->prev != NULL)
            {
                targetnode =targetnode->prev;
            }

        }
    }
    char variable1=' ';
    ///if empty
    if (targetnode->slotStack.isEmpty()){
        return 0;
    }
    else{
        targetnode->slotStack.pop(variable1);
        targetnode->slotStack.push(variable1);
        if( (variable1 != player) && variable1 != ' ')
        {
            return 3;
        }
    }


    return 0;

}
/*****************************************************************************
This function checks moves the players valid move
*****************************************************************************/
void Board::movePiece(int source, int target)
{
    slot *targetnode=head, *sourcenode=head;
    char player=' ';

    for(int i=0; i<target; i++)
    {
        targetnode =targetnode->next;
    }
    for(int i=0; i<source; i++)
    {
        sourcenode =sourcenode->next;
    }

    sourcenode->slotStack.pop(player);
    targetnode->slotStack.push(player);
}
/*****************************************************************************
This function prints the board
*****************************************************************************/
void Board::printBoard() {

    string row, lastrow, newrow;
    char variable=' ';
    slot *current = head, *current1 = head;
    int count = 0;
    while (current != NULL) {
        count++;
        lastrow += '^';
        current = current->next;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < count; j++) {
            if (current1->slotStack.isEmpty() ) {
                row += ' ';
            } else {
                current1->slotStack.pop(variable);
                if (variable =='x' || variable =='o' || variable ==' '){
                    row += variable;
                }
            }
            current1 = current1->next;
        }
        current1 = head;
        row += '/';
    }
    current1 = head;
    row = row.substr(0, (row.length() - 1));
    cout<<endl;

    for (int i = 0; i < 3; i++) {
        int idx = row.rfind('/');
        if (idx == string::npos) {
            for (int i = 0; i < row.length(); i++)
            {
                if(row[i]==' '){
                    current1=current1->next;
                }
                else{
                    current1->slotStack.push(row[i]);
                    current1 = current1->next;
                }
            }
            cout << row << endl;
            break;
        }
        else
        {
            newrow = row.substr(idx + 1, (row.length() - idx));
            for (int i = 0; i < newrow.length(); i++)
            {
                if(newrow[i]==' '){
                    current1=current1->next;
                }
                else{
                    current1->slotStack.push(newrow[i]);
                    current1 = current1->next;
                }

            }
            current1 = head;
            cout << newrow << endl;
            row = row.substr(0, idx);
        }
    }
    row = "";
    cout << lastrow << endl;
}
/*****************************************************************************
This function counts the number of x's and o's and determines the winner
*****************************************************************************/
int Board::evaluateGame()
{
    slot *current=head,*current1=head;
    string row,newrow;
    int count=0;
    char variable=' ';
    while(current != NULL)
    {
        count++;
        current=current->next;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < count; j++) {
            if (current1->slotStack.isEmpty()) {
                row += ' ';
            } else {
                current1->slotStack.pop(variable);
                row += variable;

            }
            current1 = current1->next;
        }
        current1 = head;
        row += '/';
    }

    row = row.substr(0, (row.length() - 1));
    for(int i=0;i<row.length();i++)
    {
        if(row[i]=='x'){
            xCnt++;
        }

        if(row[i]=='o'){
            oCnt++;
        }
    }

    if(xCnt<oCnt){
        return 1;
    }

    else if(xCnt>oCnt){
        return 2;
    }
    else{
        return 3;
    }
}
/*****************************************************************************
This function checks if the target slot is full
*****************************************************************************/
bool Board::targetSlotFull(int slotidx)
{
    slot *targetnode=head;
    for(int i=0; i<slotidx; i++)
    {
        targetnode =targetnode->next;
    }

    if( targetnode->slotStack.isFull())
    {
        return true;
    }
    return false;
}
/*****************************************************************************
This function clears the board
*****************************************************************************/
void Board::clearBoard()
{
    slot * ptr = head;
    while(head!=NULL)
    {
        head = head->next;
        delete ptr;
        ptr = NULL;
        ptr = head;
    }
    tail = NULL;

}
/*****************************************************************************
This function creates an empty slot at the end
*****************************************************************************/
void Board::createEmptySlotEnd()
{
    slot *temp = new slot();
    //List is empty
    if(tail == NULL)
    {
        tail = temp;
        head = tail;
        temp->next =NULL;
        temp->prev=NULL;
    }
    else
    {

        tail->next = temp;
        temp->prev =tail;
        tail = temp;
        tail->next=NULL;
    }
    //temp->slotStack.push(' ');

}
/*****************************************************************************
This function creates slot beginning
*****************************************************************************/
void Board::createSlotBegin(char player, int num)
{
    ///class
    slot *ptr = new slot();
    if(head == NULL)
    {
        head = ptr;
        tail = head;
        ptr->next =NULL;
        ptr->prev=NULL;
    }
    else
    {
        head->prev = ptr;
        ptr->next=head;
        head = ptr;
        ptr->prev=NULL;
    }
    for(int i=0; i<num;i++)
    {
        ptr->slotStack.push(player);
    }

    /*if (player =='x'){
        xCnt+=num;
    }

    if (player =='o'){
        xCnt+=num;
    }*/
}
/*****************************************************************************
This function creates a slot at the end
*****************************************************************************/
void Board::createSlotEnd(char player, int num)
{
    ///class
    slot *temp = new slot();
    //List is empty
    if(tail == NULL)
    {
        tail = temp;
        head = tail;
        temp->next =NULL;
        temp->prev=NULL;
    }
    else
    {
        tail->next = temp;
        temp->prev =tail;
        tail = temp;
        tail->next=NULL;
    }

    for(int i=0; i<num;i++)
    {
        temp->slotStack.push(player);
    }
    /*if (player =='x'){
        xCnt+=num;
    }

    if (player =='o'){
        xCnt+=num;
    }*/

}
/*****************************************************************************
This function destroys a slot that is full
*****************************************************************************/
void Board::destroySlot(int slotidx)
{
    slot * ptr ,*toBeDeleted=head;

    for(int i=0; i<slotidx;i++)
    {
        toBeDeleted=toBeDeleted->next;
    }

    if (toBeDeleted == head)  //if the node to be deleted is the first node
    {
        head = head->next;
        head->prev=NULL;
        delete toBeDeleted;
        toBeDeleted = NULL;
    }
    else if (toBeDeleted==tail){
        tail=tail->prev;
        tail->next=NULL;
        delete toBeDeleted;
        toBeDeleted = NULL;
    }
    else  //if the node to be deleted is in the middle or at the end
    {
        ptr = head;
        while (ptr->next != toBeDeleted)
            ptr = ptr->next;
        //after while ptr point to the node just before toBeDeleted

        //connect the previous node to the next node and delete
        ptr->next = toBeDeleted->next;
        toBeDeleted->next->prev=ptr;
        //ptr->prev= toBeDeleted->prev;
        delete toBeDeleted;
        toBeDeleted = NULL;
    }

}
#ifndef __TREES_H
#define __TRESS_H
#include "board.h"

typedef struct SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;// מספר הדילוגים עד כה
	struct SingleSourceMovesTreeNode* next_move[2];//יעדי התנועה
}SingleSourceMovesTreeNode;

typedef struct SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;


SingleSourceMovesTreeNode* FindingSingleSourceMovesHelper(Board board, checkersPos* src, bool topDown, int totalCapture, checkersPos* oldPos, checkersPos* capturedPos);
SingleSourceMovesTree* FindingSingleSourceMoves(Board board, checkersPos* src);
SingleSourceMovesTreeNode* createNewTnode(Board board, checkersPos pos, int totalCapturesSoFar, checkersPos* oldPos, checkersPos* capturedPos);
int findLevel(SingleSourceMovesTreeNode* node);
void freeTreeHelper(SingleSourceMovesTreeNode* source);
void freeTree(SingleSourceMovesTree* tr);
void determinePositionsAndOpponent(bool topDown, Board board, checkersPos* src, char* opponent, char* nextPosLeftValue, char* nextPosRightValue, char* nextNextPosLeftValue, char* nextNextPosRightValue, 
checkersPos* posAfterLeft, checkersPos* posAfterRight, checkersPos* posAfterRightCapture, checkersPos* posAfterLeftCapture);
bool isValidCapture(char nextNext);

#endif
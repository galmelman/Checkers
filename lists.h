#ifndef __LISTS_H
#define __LISTS_H
#include "trees.h"


typedef struct SingleSourceMovesListCell   //the struct of the list node that represents the longest move
{
	checkersPos* position;
	unsigned short captures;
	struct SingleSourceMovesListCell* next;

}SingleSourceMovesListCell;

typedef struct SingleSourceMovesList {       //the struct of the list that represents the longest move

	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;



SingleSourceMovesList* FindingSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
void insertNodeToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail);
bool isEmptyList(SingleSourceMovesList* lst);
void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* dataOfPos, unsigned short captures);
SingleSourceMovesListCell* createNewListNode(checkersPos* dataOfPos, unsigned short captures, SingleSourceMovesListCell* next);
void FindingSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* node, SingleSourceMovesList* list, bool topDown);
void makeEmptyList(SingleSourceMovesList* lst);


#endif
#ifndef __LISTOFLISTS_H
#define __LISTOFLISTS_H
#include "lists.h"


typedef struct multipleSourceMovesListCell   //the struct of the list node that represents the best move for one Piece.
{
	SingleSourceMovesList* single_Source_moves_list;
	struct multipleSourceMovesListCell* next;

}MultipleSourceMovesListCell;

typedef struct multipleSourceMovesList   //the struct of the list that represents the best moves for every Piece . 
{
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
}MultipleSourceMovesList;


MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
MultipleSourceMovesList* createMultipleSourceMovesList();
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* singleSourceMovesList);
void insertNodeToEndListOfList(MultipleSourceMovesList* list, MultipleSourceMovesListCell* newCell);
bool isEmptyListOfList(MultipleSourceMovesList* list);
void insertDataToEndListOfLists(MultipleSourceMovesList* llst, SingleSourceMovesList* data);
void freeListOfLists(MultipleSourceMovesList* list);


#endif
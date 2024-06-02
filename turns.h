#ifndef __TURNS_H
#define __TURNS_H
#include "listsOfLists.h"


void updateBoard(Board board, MultipleSourceMovesListCell* max);
char calculateAverage(char char1, char char2);
void Turn(Board board, Player player);
void convertPlaceToInd(char* row, char* col, checkersPos pos);


#endif
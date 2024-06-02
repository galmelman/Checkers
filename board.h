#ifndef __BOARD_H
#define __BOARD_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BOARD_SIZE 9

typedef struct checkersPos
{
	char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;


void printCheckersBoard(Board board);
Board* buildBoard();
Board* shiftBoard(Board board, checkersPos* newPos, checkersPos* oldPos, checkersPos* capturedPos);

#endif
#include "turns.h"



//this function is playing a turn for a player 
void Turn(Board board, Player player)
{
	MultipleSourceMovesList* playerList = NULL;
	MultipleSourceMovesListCell* max = NULL;
	MultipleSourceMovesListCell* secondMax = NULL;
	MultipleSourceMovesListCell* curr = NULL;
	char rowInd1;
	char colInd1;
	char rowInd2;
	char colInd2;

	rowInd1 = colInd1 = rowInd2 = colInd2 = '0'; // set the index's value to '0' for begin.

	playerList = FindAllPossiblePlayerMoves(board, player);   // set the list of lists that holds every player posiible move.  
	curr = playerList->head;
	max = curr;  // set the optimal move to be the first list in the list of lists.
	secondMax=max; // saves the second max.

    //if there is only a 1 move situation to B 
	if (max->single_Source_moves_list->head == max->single_Source_moves_list->tail)
	{
		if (player == 'B')
		{
			max = curr->next;  
		}	
	}
	if (player == 'B')
	{
		while (curr != NULL)
		{   // Find the maximum capturing move
			if (curr->single_Source_moves_list->tail->captures > max->single_Source_moves_list->tail->captures)
			{
				max = curr;
			}
			curr = curr->next;
		}
	}
	else  //if the player is T
	{
		while (curr != NULL)
		{		// Find the maximum capturing move or equal capturing move
			if (curr->single_Source_moves_list->tail->captures >= max->single_Source_moves_list->tail->captures)
			{
				secondMax=max;
				max = curr;
			}
			curr = curr->next;
		}
		//if the T is captured and cant move we will take the one before him in order to keep the game playing 
		if (max->single_Source_moves_list->head == max->single_Source_moves_list->tail)
		{
			max=secondMax;
		}
	}
	updateBoard(board, max);  //updating the board by the play   

	//update the index's of the  player pice before the turn and after the turn
	rowInd1 = max->single_Source_moves_list->head->position->row;
	colInd1 = max->single_Source_moves_list->head->position->col;
	rowInd2 = max->single_Source_moves_list->tail->position->col;
	colInd2 = max->single_Source_moves_list->tail->position->col;

	//converts the index's to print format.
	convertPlaceToInd(&rowInd1, &colInd1, *(max->single_Source_moves_list->head->position)); 
	convertPlaceToInd(&rowInd2, &colInd2, *(max->single_Source_moves_list->tail->position));
	printf("%c's turn\n", player);
	printf("%c%c -> %c%c\n", rowInd1, colInd1, rowInd2, colInd2);
	freeListOfLists(playerList); // Free the memory used by the player's moves list
}


// This function updates the game board based on the maximum captures move
void updateBoard(Board board, MultipleSourceMovesListCell* max) {
	// Initialize variables
	SingleSourceMovesListCell* curr = NULL;
	checkersPos toDelete;
	Board* newBoard = NULL;

	// Iterate through the single source moves list
	curr = max->single_Source_moves_list->head;
	while (curr->next != NULL)
	{
		// Check if the number of captures is the same in the current and next move
		if (curr->captures == curr->next->captures)
		{
			// Shift the board based on the current and next move positions
			// with no deletion
			newBoard = shiftBoard(board, curr->next->position, curr->position, NULL);
		}
		else
		{
			// Calculate the average position to delete a piece from the board
			toDelete.row = calculateAverage(curr->position->row, curr->next->position->row);
			toDelete.col = calculateAverage(curr->position->col, curr->next->position->col);

			// Shift the board based on the current and next move positions
			// with a deletion at the calculated average position
			newBoard = shiftBoard(board, curr->next->position, curr->position, &toDelete);
		}

		// Copy the contents of the new board to the original board
		memcpy(board, newBoard, sizeof(Board));

		// Move to the next node in the single source moves list
		curr = curr->next;
	}
}



// a function that calculate  the avrage of two index's
char calculateAverage(char char1, char char2) {
	int num1 = char1 - '0';
	int num2 = char2 - '0';
	int average = (num1 + num2) / 2;
	return average + '0';
}


//this function is returning the Index of the checkers in order to print the move 
void convertPlaceToInd(char* row, char* col, checkersPos pos) {


	switch (pos.row)
	{
	case 0:
		*row = 'A';
		break;
	case 1:
		*row = 'B';
		break;
	case 2:
		*row = 'C';
		break;
	case 3:
		*row = 'D';
		break;
	case 4:
		*row = 'E';
		break;
	case 5:
		*row = 'F';
		break;
	case 6:
		*row = 'G';
		break;
	case 7:
		*row = 'H';
		break;
	}


	switch (pos.col)
	{
	case 0:
		*col = '1';
		break;
	case 1:
		*col = '2';
		break;
	case 2:
		*col = '3';
		break;
	case 3:
		*col = '4';
		break;
	case 4:
		*col = '5';
		break;
	case 5:
		*col = '6';
		break;
	case 6:
		*col = '7';
		break;
	case 7:
		*col = '8';
		break;
	}
}



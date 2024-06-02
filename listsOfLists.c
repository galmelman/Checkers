#include "listsOfLists.h"



// this funciton creates Multiple Source Moves List.
MultipleSourceMovesList* createMultipleSourceMovesList()
{
	MultipleSourceMovesList* list = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	if (list == NULL) {
		printf("allocate memory for list of lists failed\n");
		exit(1);
	}

	list->head = list->tail = NULL;
	return list;
}


// This function creates a list of lists with all possible moves for a player
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	MultipleSourceMovesList* playerMoves = NULL;
	playerMoves = createMultipleSourceMovesList();
	int row, col;
	SingleSourceMovesTree* tempSingleSourceTree = NULL;
	checkersPos currPos;
	SingleSourceMovesList* tempSingleSourceList = NULL;

	// Iterate over the board to find all positions occupied by the player
	for (row = 0; row < BOARD_SIZE - 1; row++)
	{
		for (col = 0; col < BOARD_SIZE - 1; col++)
		{
			if (board[row][col] == player)
			{
				currPos.col = col;
				currPos.row = row;

				// Find the single source moves for the current position
				tempSingleSourceTree = FindingSingleSourceMoves(board, &currPos);

				// Find the optimal move from the single source moves tree
				tempSingleSourceList = FindingSingleSourceOptimalMove(tempSingleSourceTree);
				freeTree(tempSingleSourceTree);
				// Insert the single source moves list into the player's moves list
				insertDataToEndListOfLists(playerMoves, tempSingleSourceList);
			}
		}
	}

	return playerMoves;
}


// Insert a SingleSourceMovesList data at the end of a MultipleSourceMovesList
void insertDataToEndListOfLists(MultipleSourceMovesList* lst, SingleSourceMovesList* data)
{
	// Create a new list cell with the given data
	MultipleSourceMovesListCell* newTail = createMultipleSourceMovesListCell(data);

	// Insert the new cell at the end of the list
	insertNodeToEndListOfList(lst, newTail);
}


// Create a new cell for the MultipleSourceMovesList
MultipleSourceMovesListCell* createMultipleSourceMovesListCell(SingleSourceMovesList* singleSourceMovesList)
{
	MultipleSourceMovesListCell* newCell = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	if (newCell == NULL) {
		printf("Memory allocation error for MultipleSourceMovesListCell.\n");
		exit(1);
	}
	newCell->single_Source_moves_list = singleSourceMovesList;
	newCell->next = NULL;
	return newCell;
}

// Insert a node at the end of the list of lists
void insertNodeToEndListOfList(MultipleSourceMovesList* list, MultipleSourceMovesListCell* newCell) {
	if (isEmptyListOfList(list)) {
		// If the list is empty, set the head and tail to the new node
		list->head = list->tail = newCell;
	}
	else {
		// Append the new node to the end of the list
		list->tail->next = newCell;
		list->tail = newCell;
	}
	newCell->next = NULL;
}

// Check if the list of lists is empty
bool isEmptyListOfList(MultipleSourceMovesList* list) {
	return (list->head == NULL);
}


// This function is freeing the list of lists
void freeListOfLists(MultipleSourceMovesList* listOflists)
{
	// Initialize variables
	MultipleSourceMovesListCell* curr = listOflists->head;
	MultipleSourceMovesListCell* saver = curr->next;
	SingleSourceMovesListCell* saverSingleListCell = NULL;
	SingleSourceMovesListCell* currSingleListCell = NULL;

	// Iterate through the list of lists
	while (curr != NULL)
	{
		// Free each single source moves list in the current list of lists
		currSingleListCell = curr->single_Source_moves_list->head;
		saverSingleListCell = currSingleListCell->next;

		while (currSingleListCell != NULL)
		{
			// Free each position in the single source moves list
			free(currSingleListCell->position);
			free(currSingleListCell);

			// Move to the next single source moves list cell
			currSingleListCell = saverSingleListCell;
			if (currSingleListCell != NULL)
				saverSingleListCell = currSingleListCell->next;
		}

		// Move to the next list in the list of lists
		saver = curr->next;

		// Free the single source moves list itself
		free(curr->single_Source_moves_list);

		// Move to the next list of lists cell
		curr = saver;
	}

	// Free the list of lists itself
	free(listOflists);
}

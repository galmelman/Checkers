#include "lists.h"



// Find the longest subtree and build a list with the optimal moves
SingleSourceMovesList* FindingSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	SingleSourceMovesList* optimal_moves_list = NULL;
	bool topDown = false;
	optimal_moves_list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	if (optimal_moves_list == NULL)
	{
		printf("list alocation failed!!!");
		exit(1);
	}
	makeEmptyList(optimal_moves_list);

	if (moves_tree->source->board[moves_tree->source->pos->row][moves_tree->source->pos->col] == 'T')
	{
		topDown = true;
	}


	FindingSingleSourceOptimalMoveHelper(moves_tree->source, optimal_moves_list, topDown);
	return optimal_moves_list;
}


// Recursive function to build the list with the longest path to the tree leaf with maximum captures
void FindingSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* source, SingleSourceMovesList* list, bool topDown) {
	if (source == NULL) {
		return;
	}

	insertDataToEndList(list, source->pos, source->total_captures_so_far);

	// if there is no move that i can make return empty list
	if (source->next_move[0] == NULL && source->next_move[1] == NULL)
		return;

	// Follow the path with the maximum captures
	if (source->next_move[0] != NULL && source->next_move[1] != NULL) {
		if (source->next_move[0]->total_captures_so_far == source->next_move[1]->total_captures_so_far)
		{
			// Check the level of the tree in order to to know where should i follow 
			int numMovesAfter0 = findLevel(source->next_move[0]);
			int numMovesAfter1 = findLevel(source->next_move[1]);

			//if the level of the left tree is higher go there
			if (numMovesAfter0 > numMovesAfter1)
			{
				FindingSingleSourceOptimalMoveHelper(source->next_move[0], list, topDown);
			}
			//if the level of the right tree is higher go there
			else if (numMovesAfter0 < numMovesAfter1)
			{
				FindingSingleSourceOptimalMoveHelper(source->next_move[1], list, topDown);
			}
			//checking if its T or B turn to know wich path should i follow if the path is in the same length 
			//this case is for T
			else if (topDown == true)
			{
				FindingSingleSourceOptimalMoveHelper(source->next_move[1], list, topDown);
			}
			//this case is for B
			else
			{
				FindingSingleSourceOptimalMoveHelper(source->next_move[0], list, topDown);
			}
		}
		//checking the captures size if its not equal in order to know where to go in the tree 
		else if (source->next_move[0]->total_captures_so_far > source->next_move[1]->total_captures_so_far) {
			FindingSingleSourceOptimalMoveHelper(source->next_move[0], list, topDown);
		}
		else {
			FindingSingleSourceOptimalMoveHelper(source->next_move[1], list, topDown);
		}
	}
	// if the tree is one sided make list from the side that is not NULL
	else if (source->next_move[0] != NULL) {
		FindingSingleSourceOptimalMoveHelper(source->next_move[0], list, topDown);
	}
	else if (source->next_move[1] != NULL) {
		FindingSingleSourceOptimalMoveHelper(source->next_move[1], list, topDown);
	}
}


// This function inserts a new node to the end of the list
void insertNodeToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail) {
	if (isEmptyList(lst) == true)
		lst->head = lst->tail = tail;
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

// This function checks if the list is empty
bool isEmptyList(SingleSourceMovesList* lst) {
	if (lst->head == NULL)
		return true;
	else
		return false;
}

// This function creates a new node and puts it at the end of the list
void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* dataOfPos, unsigned short captures) {
	SingleSourceMovesListCell* newTail;
	newTail = createNewListNode(dataOfPos, captures, NULL);
	insertNodeToEndList(lst, newTail);
}

// This function creates a new node
SingleSourceMovesListCell* createNewListNode(checkersPos* dataOfPos, unsigned short captures, SingleSourceMovesListCell* next) {
	SingleSourceMovesListCell* res;
	res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	if (res == NULL) {
		printf("malloc failed!");
		exit(1);
	}
	else {
		res->captures = captures;
		res->next = next;
		res->position = dataOfPos;
	}
	return res;
}

// This function makes the list empty
void makeEmptyList(SingleSourceMovesList* lst) {
	lst->head = lst->tail = NULL;
}



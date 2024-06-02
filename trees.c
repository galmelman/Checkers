#include "trees.h"


// Determine the positions and opponent based on the player's turn
void determinePositionsAndOpponent(bool topDown, Board board, checkersPos* src, char* opponent, char* nextPosLeftValue, char* nextPosRightValue, char* nextNextPosLeftValue, char* nextNextPosRightValue, checkersPos* posAfterLeft, checkersPos* posAfterRight, checkersPos* posAfterRightCapture, checkersPos* posAfterLeftCapture) {
	if (topDown == true) {
		*nextPosLeftValue = board[src->row + 1][src->col - 1];
		*nextPosRightValue = board[src->row + 1][src->col + 1];
		*nextNextPosLeftValue = board[src->row + 2][(src->col - 2)];
		*nextNextPosRightValue = board[src->row + 2][(src->col + 2)];
		*opponent = 'B';

		// Update the left next index
		posAfterLeft->col = src->col - 1;
		posAfterLeft->row = src->row + 1;

		// Update the right next index
		posAfterRight->col = src->col + 1;
		posAfterRight->row = src->row + 1;

		// Update the right next index after capture
		posAfterRightCapture->col = src->col + 2;
		posAfterRightCapture->row = src->row + 2;

		// Update the left next index after capture
		posAfterLeftCapture->col = src->col - 2;
		posAfterLeftCapture->row = src->row + 2;
	}
	else {
		*nextPosLeftValue = board[src->row - 1][src->col - 1];
		*nextPosRightValue = board[src->row - 1][src->col + 1];
		*nextNextPosLeftValue = board[src->row - 2][src->col - 2];
		*nextNextPosRightValue = board[src->row - 2][src->col + 2];
		*opponent = 'T';

		// Update the left next index
		posAfterLeft->col = src->col - 1;
		posAfterLeft->row = src->row - 1;

		// Update the right next index
		posAfterRight->col = src->col + 1;
		posAfterRight->row = src->row - 1;

		// Update the right next index after capture
		posAfterRightCapture->col = src->col + 2;
		posAfterRightCapture->row = src->row - 2;

		// Update the left next index after capture
		posAfterLeftCapture->col = src->col - 2;
		posAfterLeftCapture->row = src->row - 2;
	}
}

// Helper function to find single source moves in a given board
SingleSourceMovesTreeNode* FindingSingleSourceMovesHelper(Board board, checkersPos* src, bool topDown, int totalCapture, checkersPos* oldPos, checkersPos* capturedPos)
{
	// Store the current positions and values
	char currPos = board[src->row][src->col];
	char nextPosLeftValue;
	char nextPosRightValue;
	char nextNextPosLeftValue;
	char nextNextPosRightValue;
	char opponent;

	// Store the positions after capture
	checkersPos posAfterLeftCapture;
	checkersPos posAfterRightCapture;

	// Store the next positions
	checkersPos posAfterRight;
	checkersPos posAfterLeft;

	// Initialize the source tree node and updated board
	SingleSourceMovesTreeNode* source = NULL;
	Board* updatedBoard = NULL;

	// Determine the positions and opponent based on the player's turn
	determinePositionsAndOpponent(topDown, board, src, &opponent, &nextPosLeftValue, &nextPosRightValue, &nextNextPosLeftValue, &nextNextPosRightValue, &posAfterLeft, &posAfterRight, &posAfterRightCapture, &posAfterLeftCapture);

	if (src->col >= BOARD_SIZE - 1 || src->col < 0 || src->row >= BOARD_SIZE - 1 || src->row < 0) {
		// Check if source position is within the board
		return NULL;
	}

	source = createNewTnode(board, *src, totalCapture, oldPos, capturedPos); // Build the source treeNode.

	// Check if the next positions result in a self-capture move
	if ((nextPosLeftValue == 'B' || nextPosLeftValue == 'T') && (nextNextPosLeftValue == 'B' || nextNextPosLeftValue == 'T')) {

		// Check if the other direction also results in a self-capture move
		if ((nextPosRightValue == 'B' || nextPosRightValue == 'T') && (nextNextPosRightValue == 'B' || nextNextPosRightValue == 'T'))
		{
			// If both directions result in self-capture moves, return NULL to indicate invalid move
			return source;
		}
	}

	if (nextPosLeftValue == opponent) {
		// Check if capturing to the left is possible
		if (isValidCapture(nextNextPosLeftValue) == true) {
			source->next_move[0] = FindingSingleSourceMovesHelper(source->board, &posAfterLeftCapture, topDown, totalCapture + 1, src, &posAfterLeft);
		}
	}
	else if (nextPosLeftValue == ' ' && totalCapture == 0) {
		// Check if moving to the left is possible
		source->next_move[0] = createNewTnode(board, posAfterLeft, totalCapture, src, NULL);
	}

	if (nextPosRightValue == opponent) {
		// Check if capturing to the right is possible
		if (isValidCapture(nextNextPosRightValue) == true) {
			source->next_move[1] = FindingSingleSourceMovesHelper(source->board, &posAfterRightCapture, topDown, totalCapture + 1, src, &posAfterRight);
		}
	}
	else if (nextPosRightValue == ' ' && totalCapture == 0) {
		// Check if moving to the right is possible
		source->next_move[1] = createNewTnode(board, posAfterRight, totalCapture, src, NULL);
	}

	return source;
}

// Find all possible single source moves for a given player's turn
SingleSourceMovesTree* FindingSingleSourceMoves(Board board, checkersPos* src) {
	bool topDown = false;
	SingleSourceMovesTree* posTree;

	posTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	if (posTree == NULL) {
		printf("Memory allocation failed!");
		exit(1);
	}

	if (board[src->row][src->col] == ' ') {
		// Empty source position, return NULL
		return NULL;
	}
	else {
		if (board[src->row][src->col] == 'T') {
			topDown = true; // Top player's turn
		}

		posTree->source = FindingSingleSourceMovesHelper(board, src, topDown, 0, src, NULL);

		return posTree;
	}
}

// a funciton that free a tree
void freeTree(SingleSourceMovesTree* tree) {
	// Free the entire tree by freeing the root node and the tree structure itself
	freeTreeHelper(tree->source);
	// Free the current root
	free(tree);
}

// a funciton that free each tree root recursevly
void freeTreeHelper(SingleSourceMovesTreeNode* root) {
	if (root == NULL)
		return;

	for (int i = 0; i < 2; i++) {
		// Recursively free the child nodes
		freeTreeHelper(root->next_move[i]);
	}

	// Free the dynamically allocated memory for position and board
	free(root->board);
}

// a function that creates a treeNode.
SingleSourceMovesTreeNode* createNewTnode(Board board, checkersPos pos, int totalCapturesSoFar, checkersPos* oldPos, checkersPos* capturedPos) {
	checkersPos* currPos = NULL;
	SingleSourceMovesTreeNode* res = NULL;
	Board* updatedBoard;

	currPos = (checkersPos*)malloc(sizeof(checkersPos));
	if (currPos == NULL)
	{
		printf("newPos allocation falied!");
		exit(1);

	}
	currPos->row = pos.row;
	currPos->col = pos.col;

	res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	if (res == NULL)
	{
		printf("allocation error!");
		exit(1);
	}

	updatedBoard = shiftBoard(board, &pos, oldPos, capturedPos);
	memcpy(res->board, updatedBoard, sizeof(Board));  // Copy the original board
	res->next_move[0] = NULL;
	res->next_move[1] = NULL;
	res->total_captures_so_far = totalCapturesSoFar;
	res->pos = currPos;
	return res;

}

// Helper function to count the number of moves after a node
int findLevel(SingleSourceMovesTreeNode* node)
{
	int left, right;

	if (node == NULL)
	{
		return 0;
	}
	left = findLevel(node->next_move[0]); 
	right = findLevel(node->next_move[1]);

	return 1 + (left > right ? left : right);
}

// a function that checks if the next player is valid to capture
bool isValidCapture(char nextNext) {


	if (nextNext == ' ')
	{
		return true;
	}
	return false;

}



#include "board.h"

// board functions need to be here



//The function printCheckersBoard prints an 8x8 checkers game board.
// displaying the contents of each square and including column and row headers, with all elements aligned within a square grid.
void printCheckersBoard(Board board)
{
	printf("+---+---+---+---+---+---+---+---+---+\n"); // Print the top border

	printf("|   "); // Print the empty top-left corner

	// Print the column headers aligned with each column
	for (char col = '1'; col <= '8'; col++)
	{
		printf("| %c ", col);
	}
	printf("|\n");

	printf("+---+---+---+---+---+---+---+---+---+\n"); // Print the separator

	// Iterate over each row and column of the board
	for (char row = 'A'; row < 'A' + BOARD_SIZE - 1; row++)
	{
		printf("| %c |", row); // Print the row header

		// Print the contents of each square and separators
		for (char col = '1'; col <= '8'; col++)
		{
			printf(" "); // Print the left separator
			if (board[row - 'A'][col - '1'] == 'B' || board[row - 'A'][col - '1'] == 'T')
				printf("%c", board[row - 'A'][col - '1']); // Print the square content
			else
				printf(" "); // Print a space for empty square
			printf(" |"); // Print the right separator
		}

		printf("\n");

		printf("+---+---+---+---+---+---+---+---+---+\n"); // Print the separator
	}
}

 //this function is building the first board of the game
Board* buildBoard()                                
{
	Board* newBoard;
	newBoard = (Board*)malloc(sizeof(Board));
	if (newBoard == NULL)
	{
		printf("new board allocation error!");
		exit(1);
	}
	for (int row = 0; row < BOARD_SIZE-1; row++)
	{
		for (int col = 0; col < BOARD_SIZE-1; col++) {

			if (row < (BOARD_SIZE / 2) - 1)
			{
				if (row % 2 == 0 && col % 2 != 0) {

					(*newBoard)[row][col] = 'T'; // Place 'T' on top
				}
				else if (row % 2 != 0 && col % 2 == 0) {

					(*newBoard)[row][col] = 'T'; // Place 'T' on top
				}
				else
				{
					(*newBoard)[row][col] = ' '; // Empty space in the middle
				}

			}
			else  if(row >= (BOARD_SIZE / 2)+1)
			{

				if (row % 2 == 0 && col % 2 != 0) {

					(*newBoard)[row][col] = 'B'; // Place 'B' on top
				}
				else if (row % 2 != 0 && col % 2 == 0) {

					(*newBoard)[row][col] = 'B'; // Place 'B' on top
				}
				else
				{
					(*newBoard)[row][col] = ' '; // Empty space in the middle
				}
			}
			else
			{
				(*newBoard)[row][col] = ' '; // Empty space in the middle
			}
		}
	}
	printf("\n");
	return newBoard;
}


// Shifts the board by updating the player's position and removing the captured player if valid
Board* shiftBoard(Board board, checkersPos* newPos, checkersPos* oldPos, checkersPos* capturedPos) {
	
	Board* updatedBoard = (Board*)malloc(sizeof(Board));
	if (updatedBoard == NULL)
	{
		printf("updatedBoard allocation falied!");
		exit(1);
	}
	memcpy(updatedBoard, board, sizeof(Board));  // Copy the original board

	char player = board[oldPos->row][oldPos->col];
	(*updatedBoard)[oldPos->row][oldPos->col] = ' ';  // Clear the current position
	(*updatedBoard)[newPos->row][newPos->col] = player;  // Set the player's new position

	if (capturedPos != NULL) {
		(*updatedBoard)[capturedPos->row][capturedPos->col] = ' ';  // Remove the captured player
	}

	return updatedBoard;

}

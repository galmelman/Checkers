#include "game.h"
#define T 'T'
#define B 'B'
#define FIRST_ROW 0
#define LAST_ROW 7

// Play the game by taking turns between two players until a winner is determined
void PlayGame(Board board, Player strating_player) {
	bool isWinner = false;
	Board oldBoard;

	// Initialize player info cards for players T and B
	PlayerInfo* t_player_info = buildPlayerInfoCard(T);
	PlayerInfo* b_player_info = buildPlayerInfoCard(B);

	// Set the current player
	Player currentPLayer = strating_player;

	// Print the initial board state
	printCheckersBoard(board);
	printf("\n\n");

	while (isWinner != true)
	{
        // update the old board to be the current board after the turn
	    memcpy(oldBoard, board, sizeof(Board));
        
		// Perform a turn
		Turn(board, currentPLayer);

		//Update player information after the turn
		
		updatePlayerInfoAfterTurn(oldBoard, board, currentPLayer, t_player_info, b_player_info);

		// Print the updated board state
		printCheckersBoard(board);
		printf("\n\n");

		//Check if the game is over
		if (isGameOver(board, t_player_info, b_player_info) == true)
		{
			isWinner = true;
			break;
		}

		// Switch to the next player's turn
		currentPLayer = (currentPLayer == T ? B : T);
	}


	// Print the statistics and winner information
	if (currentPLayer == T)
	{
		printStats(t_player_info, b_player_info);
	}
	else
	{
		printStats(b_player_info, t_player_info);
	}

}

//this function is getting the both players information after a turn and updates it, also the function is getting the board before the turn
//and the new board after the turn in order to compare them 
void updatePlayerInfoAfterTurn(Board oldBoard, Board newBoard, Player cuurentPlayer, PlayerInfo* t_player_info, PlayerInfo* b_player_info) 
{
	int row;
	int col;
	int changesCounter = 0;

	for (row = 0; row < BOARD_SIZE - 1; row++)
	{
		for (col = 0; col < BOARD_SIZE - 1; col++) 
        {
			if (oldBoard[row][col] != newBoard[row][col])
			{
				//counting how many diffrences we have between the boards 
				changesCounter++;
			}
		}
	}
	//sending the information to another function that will update each player struct values by the num of diffrences were between the boards
	if (cuurentPlayer == t_player_info->playerIdentity)
	{
		updatePlayerStatistics(t_player_info,b_player_info, changesCounter);
	}
	else
	{
		updatePlayerStatistics(b_player_info,t_player_info, changesCounter);
	}
}


//Updates the player statistics based on the number of changes in the board after a turn.
void updatePlayerStatistics(PlayerInfo* current_player_info,PlayerInfo* nextPlayer,int changesCounter) {
	switch (changesCounter) {
	case 2: // the player moved one place witout capturing any rivel pices
		current_player_info->sumMoves++;  // Increment the number of moves for the current player
		break;
	case 3:// the player captured one rival pice
		current_player_info->sumMoves++;  // Increment the number of moves for the current player
		// If the current player's highest number of captures in one move is less than 1, update it
		if (current_player_info->highest_number_of_captures_in_one_move < 1) {
			current_player_info->highest_number_of_captures_in_one_move = 1;
		}
		nextPlayer->numOfplayer--;  // Decrement the number of remaining players for the next player
		break;
	case 4: // the player captured 2 rival pices
		current_player_info->sumMoves ++;  // Increment the number of moves for the current player by 2
		// If the current player's highest number of captures in one move is less than 2, update it
		if (current_player_info->highest_number_of_captures_in_one_move < 2) {
			current_player_info->highest_number_of_captures_in_one_move = 2;
		}
		nextPlayer->numOfplayer -= 2;  // Decrement the number of remaining players for the next player by 2
		break;
	case 5:// the player captured 3 rival pices
		current_player_info->sumMoves += 3;  // Increment the number of moves for the current player by 3
		current_player_info->highest_number_of_captures_in_one_move = 3;  // Set the highest number of captures in one move to 3
		nextPlayer->numOfplayer -= 3;  // Decrement the number of remaining players for the next player by 3
		break;
	}

}



// Check if the game is over by determining if any of the players has no more pieces or if a player's pieces have reached the opposite end of the board
bool isGameOver(Board board, PlayerInfo* t_player_info, PlayerInfo* b_player_info) {
	// Check if any of the players has no more pieces
	if (t_player_info->numOfplayer <= 0 || b_player_info->numOfplayer <= 0) {
		return true;
	}

	// Check if any of the player's pieces have reached the opposite end of the board
	for (int i = 0; i < BOARD_SIZE - 1; i++) {
		if (board[FIRST_ROW][i] == B) {
			return true;
		}
		if (board[LAST_ROW][i] == T) {
			return true;
		}
	}

	return false;
}

//this function is getting a struct of a new player T or B and gives him the first game parameters
PlayerInfo* buildPlayerInfoCard(Player player)
{
	PlayerInfo* res;
	res = (PlayerInfo*)malloc(sizeof(PlayerInfo));
	if (res == NULL)
	{
		printf("player allocation failed!");
		exit(1);
	}

	res->playerIdentity = player;  //T or B
	res->sumMoves = 0;         
	res->highest_number_of_captures_in_one_move = 0;
	res->numOfplayer = 12;         //how many pices of T or B on the start of the game 

	return res;
}

//this function is printing the stats of the game and the winner
void printStats(PlayerInfo* winner, PlayerInfo* looser)
{
	printf("%c Wins!\n", winner->playerIdentity);
	printf("%c preformed %d moves.\n", winner->playerIdentity, winner->sumMoves);

	if (winner->highest_number_of_captures_in_one_move > looser->highest_number_of_captures_in_one_move)
	{
		printf("%c preformed the highest number of captures in a single move - %d\n", winner->playerIdentity, winner->highest_number_of_captures_in_one_move);
	}
	else {
		printf("%c preformed the highest number of captures in a single move - %d\n", looser->playerIdentity, looser->highest_number_of_captures_in_one_move);
	}

}





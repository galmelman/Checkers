#ifndef __GAME_H
#define __GAME_H
#include "turns.h"

typedef struct playerInfo {
	Player playerIdentity;
	int numOfplayer;
	int sumMoves;
	int highest_number_of_captures_in_one_move;
}PlayerInfo;


void PlayGame(Board board, Player strating_player);
PlayerInfo* buildPlayerInfoCard(Player player);
bool isGameOver(Board board, PlayerInfo* t_player_info, PlayerInfo* b_player_info);
void updatePlayerInfoAfterTurn(Board oldBoard, Board newBoard, Player cuurentPlayer, PlayerInfo* t_player_info, PlayerInfo* b_player_info);
void printStats(PlayerInfo* winner, PlayerInfo* looser);
void updatePlayerStatistics(PlayerInfo* current_player_info, PlayerInfo* nextPlayer, int changesCounter);
#endif
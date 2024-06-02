#include "game.h"

//checkers_game project
//Ido Kadosh id- 208660688
// Gal Melman id- 319041950

void main() {
    Board* gameBoard = buildBoard();
    PlayGame(*gameBoard, 'T');
    free(gameBoard);
    return;
}



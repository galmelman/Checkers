# Checkers Game

This project implements a Checkers game in C, providing a command-line interface for two players to compete against each other.

## Project Structure

The project consists of several modules:

1. `board.c` / `board.h`: Handles the game board operations.
2. `game.c` / `game.h`: Manages the game flow and player turns.
3. `lists.c` / `lists.h`: Implements linked list data structures for move tracking.
4. `listsOfLists.c` / `listsOfLists.h`: Manages multiple move lists.
5. `trees.c` / `trees.h`: Implements tree data structures for move analysis.
6. `turns.c` / `turns.h`: Handles player turns and move execution.
7. `main.c`: The entry point of the program.

## Features

- Implements standard Checkers rules.
- Supports two players: 'T' (Top) and 'B' (Bottom).
- Calculates and tracks optimal moves for each player.
- Provides a visual representation of the game board.
- Tracks game statistics including number of moves and captures.

## How to Compile and Run

To compile the game, use a C compiler like gcc:

```
gcc main.c board.c game.c lists.c listsOfLists.c trees.c turns.c -o checkers_game
```

To run the game:

```
./checkers_game
```

## Game Play

- The game starts with player 'T' (Top).
- Players take turns moving their pieces.
- Capture moves are mandatory when available.
- The game ends when a player has no more pieces or when a piece reaches the opposite end of the board.

## Code Structure

- `Board`: Represents the game board as a 2D array.
- `Player`: Represents a player ('T' or 'B').
- `checkersPos`: Represents a position on the board.
- `SingleSourceMovesTree`: Represents possible moves for a single piece.
- `SingleSourceMovesList`: Represents a list of moves for a single piece.
- `MultipleSourceMovesList`: Represents lists of moves for multiple pieces.


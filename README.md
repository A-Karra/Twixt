# Twixt — Terminal Board Game

**Twixt** is a terminal-based two-player strategic game implemented in C. Players place pegs on a 24×24 board and can form *links* between their pegs using knight-move distances (like a chess knight). The goal is to create a continuous path across the board (top-to-bottom for Player 1, left-to-right for Player 2).

-----

## Features

  - 24×24 board (configurable via `board_size` macro).
  - Two-player gameplay (Player 1: Red, Player 2: Blue).
  - Automatic detection and creation of *links* between same-player pegs at knight-move offsets.
  - Link validity checking (prevents intersecting links except at endpoints).
  - Win detection via DFS (`pathFind`) across a graph of links.
  - Visual terminal UI with colored output and simple sound effects (in Unix Terminals).
  - Printable representation of the winning path.

-----

## Files

  - `main.c` — Main game loop, board initialization, user input handling.
  - `header.h` — Shared definitions and all game logic helpers (printing, pathfinding, link management, etc.).
  - `Makefile` — Build script for compiling the project.
  - `lightsaber.wav` — Optional sound file used when highlighting selections (not included in the repo; place it in the same directory if desired).

-----

## Build Instructions

A `Makefile` is provided for easy compilation. Ensure you have `gcc` and `make` installed.

1.  **Build the game:**
    ```bash
    make
    ```
2.  **Run the game:**
    ```bash
    ./game
    ```
3.  **Clean up build files:**
    ```bash
    make clean
    ```

The `Makefile` automatically links the math library (`-lm`) and sets the necessary flags (`-D_DEFAULT_SOURCE`) to compile `usleep` correctly.

-----

## Dependencies / Notes

  - `gcc` (or any C compiler) and `make`
  - `aplay` (optional) — used to play `lightsaber.wav`. If `aplay` is not present the game will silently continue; remove or comment the `system("aplay ...")` calls in `header.h` if you don't want sound.
  - **UNIX-like terminal** — Required. The game uses `system("clear")`, ANSI color escape codes, and `usleep` for its display and highlighting.

-----

## How to Play

1.  Run `./game` in your terminal.
2.  Players alternate turns. Player 1 (Red) goes first.
3.  Input a column as a capital letter (`A` through `X` for the 24×24 board) and a row as a number (`1` through `24`). Example input sequence for a move: `C` then `4`.
4.  After selecting a column and row, you will be shown a highlighted preview. Press `Enter` to confirm or type `c` to cancel the selection.
5.  **Move Restrictions:**
      * **Player 1 (Red)** cannot place pegs in the first column (`A`) or the last column (`X`).
      * **Player 2 (Blue)** cannot place pegs in the first row (`1`) or the last row (`24`).
6.  If a newly placed peg is a knight's move away from another peg of the same player, the game will automatically create a link if that link does not intersect existing links.
7.  The win condition is:
      * **Player 1 (Red)** connects the top row to the bottom row (a path from row 1 to row 24).
      * **Player 2 (Blue)** connects the leftmost column to the rightmost column (a path from column `A` to column `X`).

When a win is detected, the program prints a highlighted winning board and the links that participate in the winning path.

-----

## Code Structure (quick reference)

  - `#define board_size` — board dimension (changeable at compile time).
  - `typedef struct Link` — stores endpoints and which player owns the link.
  - `links_arr` / `link_count` — dynamic array of established links.
  - `printBanner()` — clears the screen and prints ASCII logo.
  - `printBoard(...)` — draws the board with color coding and optional highlights for selection.
  - `checkLinks(...)` — checks knight-move neighbors and attempts to create a link.
  - `isLinkValid(...)` — determines if a candidate link intersects existing links (permits shared endpoints).
  - `establishLink(...)` — appends a new `Link` to `links_arr` (uses `realloc`).
  - `pathFind(...)` — depth-first search over the graph of links to detect a continuous path.
  - `gameOver(...)` — iterates possible starting pegs and invokes `pathFind` to check for a winner.

-----

## Example Run

```
$ make
gcc -Wall -Wextra -std=c99 -g -D_DEFAULT_SOURCE -c -o main.o main.c
gcc -lm -o game main.o

$ ./game

<game starts — ASCII banner, board prints>

Player 1s turn: (enter move like C4 etc.)

Enter Coloumn: C
<board redraws with column C highlighted>
Enter row: 4
<board redraws with C4 and its row/col highlighted>
Press Enter to confirm or c to cancel:

<board updates>
...

!!! PLAYER 1 (RED) WINS !!!

--- WINNING BOARD STATE ---
<winning board shown with ★ and winning links listed>

```

-----

## License & Credits

This project is made by Aranya Karra, who is pursuing B.Tech in Computer Science at IIIT - H

----
# Twixt — Terminal Board Game

**Twixt** is a terminal-based two-player strategic game implemented in C. Players place pegs on a 24×24 board and can form _links_ between their pegs using knight-move distances (like a chess knight). The goal is to create a continuous path across the board (top-to-bottom for Player 1, left-to-right for Player 2).

---

## Features

- 24×24 board (configurable via `board_size` macro).
- Two-player gameplay (Player 1: Red, Player 2: Blue).
- Automatic detection and optional creation of *links* between same-player pegs at knight-move offsets.
- Link validity checking (prevents intersecting links except at endpoints).
- Win detection via DFS (recursion) across a graph of links.
- Visual terminal UI with colored output and simple sound effects (in Unix Terminals).
- Printable representation of the winning path.

---

## Files

- `main.c` — Main game loop, board initialization, user input handling.
- `header.h` — Shared definitions and all game logic helpers (printing, DFS, link management, etc.).
- `lightsaber.wav` — Optional sound file used when highlighting selections (not included in the repo; place it in the same directory if desired).


---

## Build Instructions

You can compile the code with `gcc`. The program uses standard C library functions and `math.h` (for `fabs`) so link with `-lm`.

```bash
gcc main.c -o twixt -lm
```

---

## Dependencies / Notes

- `gcc` (or any C compiler)
- `aplay` (optional) — used to play `lightsaber.wav`. If `aplay` is not present the game will silently continue; remove or comment the `system("aplay ...")` calls if you don't want sound.
- UNIX-like terminal (the game uses `system("clear")` for aesthetic and smooth gameplay, ANSI color escape codes and `usleep` for small highlights).


---

## How to Play

1. Run `./twixt` in your terminal.
2. Players alternate turns. Player 1 (Red) goes first.
3. Input a column as a capital letter (`A` through `X` for the 24×24 board) and a row as a number (`1` through `24`). Example input sequence for a move: `C` then `4`.
4. After selecting a column and row you will be shown a highlighted preview. Press `Enter` to confirm or type `c` to cancel the selection.
5. If a newly placed peg is a knight's move away from another peg of the same player, the game will (currently) automatically create a link if that link does not intersect existing links.
6. The win condition is:
   - Player 1 (red) connects top row to bottom row (path connecting a peg on row 1 to row 24 through links).
   - Player 2 (blue) connects leftmost column to rightmost column (path connecting a peg on column A to column X through links).

When a win is detected the program prints a highlighted winning board and the links that participate in the winning path.

---

## Code Structure (quick reference)

- `#define board_size` — board dimension (changeable at compile time).
- `typedef struct Link` — stores endpoints and which player owns the link.
- `links_arr` / `link_count` — dynamic array of established links.
- `printBanner()` — clears the screen and prints ASCII logo.
- `printBoard(...)` — draws the board with color coding and optional highlights for selection.
- `checkLinks(...)` — checks knight-move neighbors and attempts to create a link.
- `isLinkValid(...)` — determines if a candidate link intersects existing links (permits shared endpoints).
- `establishLink(...)` — appends a new `Link` to `links_arr` (uses `realloc`).
- `dfs(...)` — depth-first search over the graph of links to detect a continuous path for the active player.
- `gameOver(...)` — iterates possible starting pegs and invokes `dfs` to check for a winner.

---

## Example Run

```
$ ./twixt

<game starts — ASCII banner, board prints>

Player 1s turn:

Enter Coloumn: C
Enter row: 4
Press Enter to confirm or c to cancel:

<board updates>
...

!!! PLAYER 1 (RED) WINS !!!

--- WINNING BOARD STATE ---
<winning board shown with ★ and winning links listed>

```

---

## License & Credits

This project is made by Aranya Karra, who is pursuing B.Tech in Computer Science at IIIT - H

---

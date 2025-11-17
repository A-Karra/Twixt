#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define board_size 24

typedef struct Link{
    int r1;
    int c1;
    int r2;
    int c2;
    int owned_by_player;

} Link;

Link* links_arr = NULL;
int link_count = 0;

int pathFind(int r, int c, int turn, int board[board_size][board_size], int visited[board_size][board_size], int winning_path[board_size][board_size]);
int gameOver(int board[board_size][board_size], int visited[board_size][board_size], int turn);
void printBoard(int board[board_size][board_size],int hi_row, int hi_col,int turn);
int isLinkValid(int r1, int c1, int r2, int c2);
void establishLink(int r1, int c1, int r2, int c2,int turn);
void checkLinks(int board[board_size][board_size],int row,int col,int turn);
void printWinningBoard(int board[board_size][board_size], int winning_path[board_size][board_size], int turn);
void printBanner();


void printBanner(){
    system("clear");
    const char *logo = 
" /$$$$$$$$                           /$$                         /$$          \n"
"|__  $$__/                          |__/                        | $$          \n"
"   | $$          /$$  /$$  /$$       /$$       /$$   /$$       /$$$$$$        \n"
"   | $$         | $$ | $$ | $$      | $$      |  $$ /$$/      |_  $$_/        \n"
"   | $$         | $$ | $$ | $$      | $$       \\  $$$$/         | $$          \n"
"   | $$         | $$ | $$ | $$      | $$        >$$  $$         | $$ /$$      \n"
"   | $$         |  $$$$$/$$$$/      | $$       /$$/\\  $$        |  $$$$/      \n"
"   |__/          \\_____/\\___/       |__/      |__/  \\__/         \\___/        \n";

    printf("\033[0;32m\n\n%s\033[0m", logo);
}

int pathFind(int r, int c, int turn, int board[board_size][board_size], int visited[board_size][board_size], int winning_path[board_size][board_size]) {

    if (turn == 0 && r == board_size - 1) {
        winning_path[r][c] = 1; 
        return 1;
    }

    if (turn == 1 && c == board_size - 1) {
        winning_path[r][c] = 1; 
        return 1;
    }

    visited[r][c] = 1;

    for (int i = 0; i < link_count; i++) {
        if (links_arr[i].owned_by_player != turn) {
            continue;
        }

        int next_r = -1;
        int next_c = -1;

        if (links_arr[i].r1 == r && links_arr[i].c1 == c) {
            next_r = links_arr[i].r2;
            next_c = links_arr[i].c2;
        } else if (links_arr[i].r2 == r && links_arr[i].c2 == c) {
            next_r = links_arr[i].r1;
            next_c = links_arr[i].c1;
        }

        if (next_r != -1 && !visited[next_r][next_c]) {
            
            if (pathFind(next_r, next_c, turn, board, visited, winning_path) == 1) {
                winning_path[r][c] = 1;
                return 1;
            }
        }
        else continue;
    }
    return 0;
}


int gameOver(int board[board_size][board_size], int visited[board_size][board_size], int turn) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            visited[i][j] = 0;
        }
    }

    int winning_path[board_size][board_size] = {0};

    if (turn == 0) {
        for (int c = 0; c < board_size; c++) {
            if (board[0][c] == 0 && !visited[0][c]) {
                
                if (pathFind(0, c, turn, board, visited, winning_path) == 1) {
                    
                    printf("\033[1;31m\n\n!!! PLAYER 1 (RED) WINS !!!\n \033[0m");
                    
                    printBanner();
                    printWinningBoard(board, winning_path, turn);
                    return 1;
                }
            }
        }
    } else {
        for (int r = 0; r < board_size; r++) {
            if (board[r][0] == 1 && !visited[r][0]) {
                
                if (pathFind(r, 0, turn, board, visited, winning_path) == 1) {
                    printf("\033[1;34m\n\n!!! PLAYER 2 (BLUE) WINS !!!\n \033[0m");
                    
                    printWinningBoard(board, winning_path, turn);
                    return 1;
                }
            }
        }
    }

    // If no win was found
    return 0;
}

void printBoard(int board[board_size][board_size],int hi_row, int hi_col,int turn){
    printBanner();                                                       
    printf("\n\n\n-\t");
    for (char i = 'A'; i < 'A' + board_size; i++)
    {
        if((i=='B') || (i=='A'+board_size-1)) printf("\033[1;34m | \033[0m");
        printf(" %c ",i);
    }
    printf("\n");
    const char* highlight_color;
    if (turn == 0) {
        highlight_color = "\033[41m"; // Red Background
    } else {
        highlight_color = "\033[44m"; // Blue Background
    }
    
    int count = 0;
    int count2 = 0;
    for (int i = 0; i < board_size; i++)
    {

        if((i==1) || (i==board_size-1)){
            for (int j = 0; j < 3*board_size+13; j++)
            {
                printf("\033[1;31m-\033[0m");
            }
            printf("\n");
            
        }
        printf("%d\t",i+1);
        for (int j = 0; j < board_size; j++)
        {
            if((j==1) || (j==board_size-1)) printf("\033[1;34m | \033[0m");
            if (hi_row==i || hi_col==j) {
                printf("%s",highlight_color);
                usleep(10000);
            }
            if (hi_row==i && count == 0 ){
                system("aplay lightsaber.wav > /dev/null 2>&1 &");
                count=1;
            }
            if (hi_col==j && hi_row==-1 && count2 == 0 ){
                system("aplay lightsaber.wav > /dev/null 2>&1 &");
                count2=1;
            }
            
            if (board[i][j]==-1) printf("\033[1m ◦ \033[0m");
            else if(board[i][j]==0) printf("\033[1;31m • \033[0m");
            else if(board[i][j]==1) printf("\033[1;34m • \033[0m");
            if (hi_row==i || hi_col==j) {
                printf("\033[0m");
                fflush(stdout);
            }
        }
        printf("\n");
        
    }
    if (link_count>0) printf("Links: \n");
    for (int i = 0; i < link_count; i++)
    {
        // --- NEW --- Added color coding for links
        if (links_arr[i].owned_by_player == 0) printf("\033[1;31m");
        else printf("\033[1;34m");
        printf("\t%c%d <----> %c%d\n",links_arr[i].c1+'A',links_arr[i].r1+1,links_arr[i].c2+'A',links_arr[i].r2+1);
        printf("\033[0m");
    }
    
    return;
}
// Replace existing printWinningBoard with this to match printBoard layout/size
void printWinningBoard(int board[board_size][board_size], int winning_path[board_size][board_size], int turn) {
    printf("\n\n--- WINNING BOARD STATE ---\n\n");

    /* Print header row (columns) - matches printBoard */
    printf("-\t");
    for (char i = 'A'; i < 'A' + board_size; i++) {
        if ((i == 'B') || (i == 'A' + board_size - 1)) printf(" | ");
        printf(" %c ", i);
    }
    printf("\n");

    /* Print rows with the same separators and spacing as printBoard */
    for (int i = 0; i < board_size; i++) {
        if ((i == 1) || (i == board_size - 1)) {
            for (int k = 0; k < (int)(3 * board_size + 13); k++) {
                putchar('-');
            }
            putchar('\n');
        }

        printf("%d\t", i + 1);
        for (int j = 0; j < board_size; j++) {
            if ((j == 1) || (j == board_size - 1)) printf(" | ");

            /* Winning-path cell */
            if (winning_path[i][j] == 1) {
                if (turn == 0) {
                    printf("\033[1;31m %s \033[0m", "★");   // red star for player 0
                } else {
                    printf("\033[1;34m %s \033[0m", "★");   // blue star for player 1
                }
            }
            /* Normal cells (same symbols/spacing as printBoard) */
            else if (board[i][j] == -1) {
                printf(" ◦ ");
            } else if (board[i][j] == 0) {
                printf("\033[1;31m • \033[0m");
            } else if (board[i][j] == 1) {
                printf("\033[1;34m • \033[0m");
            }
        }
        printf("\n");
    }

    /* Print winning path links (same as before) */
    printf("\n--- WINNING PATH LINKS ---\n");
    for (int idx = 0; idx < link_count; idx++) {
        if (links_arr[idx].owned_by_player == turn &&
            winning_path[links_arr[idx].r1][links_arr[idx].c1] == 1 &&
            winning_path[links_arr[idx].r2][links_arr[idx].c2] == 1) 
        {
            if (turn == 0) printf("\033[1;31m");
            else printf("\033[1;34m");

            printf("\t%c%d <----> %c%d\n",
                   links_arr[idx].c1 + 'A', links_arr[idx].r1 + 1,
                   links_arr[idx].c2 + 'A', links_arr[idx].r2 + 1);

            printf("\033[0m");
        }
    }
}



int isLinkValid(int r1, int c1, int r2, int c2) {
    double x1 = (double)c1;
    double y1 = (double)r1;
    double x2 = (double)c2;
    double y2 = (double)r2;

    for (int i = 0; i < link_count; i++) {
        double x3 = (double)links_arr[i].c1;
        double y3 = (double)links_arr[i].r1;
        double x4 = (double)links_arr[i].c2;
        double y4 = (double)links_arr[i].r2;

        double D = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        if (fabs(D) < 1e-9) { 
            continue;
        } else {
            double Px_numerator = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4));
            double Py_numerator = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4));

            double Px = Px_numerator / D;
            double Py = Py_numerator / D;

            if (((Py >= y1 && Py <= y2) || (Py >= y2 && Py <= y1)) &&
                ((Py >= y3 && Py <= y4) || (Py >= y4 && Py <= y3)) &&
                ((Px >= x1 && Px <= x2) || (Px >= x2 && Px <= x1)) &&
                ((Px >= x3 && Px <= x4) || (Px >= x4 && Px <= x3))) 
            {
                
                double epsilon = 1e-9;

                int isEndpoint1 = (fabs(Px - x1) < epsilon && fabs(Py - y1) < epsilon);
                int isEndpoint2 = (fabs(Px - x2) < epsilon && fabs(Py - y2) < epsilon);
                int isEndpoint3 = (fabs(Px - x3) < epsilon && fabs(Py - y3) < epsilon);
                int isEndpoint4 = (fabs(Px - x4) < epsilon && fabs(Py - y4) < epsilon);

                if (isEndpoint1 || isEndpoint2 || isEndpoint3 || isEndpoint4) {
                    continue;
                } else {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void establishLink(int r1, int c1, int r2, int c2,int turn){
    link_count++;

    Link* temp = realloc(links_arr, link_count * sizeof(Link));

    if (temp == NULL) {
        printf("CRITICAL ERROR: Could not allocate memory for link!\n");
        link_count--; 
        return;
    }

    links_arr = temp;

    links_arr[link_count-1].r1 = r1;
    links_arr[link_count-1].c1 = c1;
    links_arr[link_count-1].r2 = r2;
    links_arr[link_count-1].c2 = c2;
    links_arr[link_count-1].owned_by_player = turn;
    printf("Link has been established\n");
}

void checkLinks(int board[board_size][board_size],int row,int col,int turn){
    int knightMoves[8][2] = {{1,2},{1,-2},{-1,2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}};
    for (int i = 0; i < 8; i++)
    {
        int new_row = row+knightMoves[i][0];
        int new_col = col+knightMoves[i][1];

        if (new_row<board_size && new_row>=0 && 
            new_col<board_size && new_col>=0 && 
            turn==board[new_row][new_col]){
            if(isLinkValid(row,col,new_row,new_col)){
                // printf("Link to %c%d? (y/n)",new_col+'A',new_row+1);
                char yes;
                // scanf(" %c",&yes);
                yes='Y';
                if (yes=='y' || yes=='Y'){
                    printf("Trying to establish Link b/w %c%d <---and---> %c%d\n", col+'A',row+1,new_col+'A',new_row+1);
                    establishLink(row,col,new_row,new_col,turn);
                    printBoard(board,-1,-1,turn);
                }
                else continue;
            }
            else continue;
        }
    }
}

#endif 
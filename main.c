#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include "header.h"

int main(){
    int board[board_size][board_size];
    int visited[board_size][board_size] = {0};

    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            board[i][j]=-1;
            visited[i][j]=0;
        }
        
    }
    int turn=0;
    printBoard(board,-1,-1,turn);
    
    while(1){ 

        printf("\n\n\n");
        char col;
        int row;
        int col_index;
        int row_index;

        int hi_row;
        int hi_col;

        if(!turn) {
            printf("\033[0;31mPlayer 1s turn: (enter move like C4 etc.) \033[0m\n");
            
            printf("\nEnter Coloumn: ");
            scanf(" %c",&col);
            col = toupper(col);
            col_index = (int)col - 'A';
            hi_col = col_index;

            printBoard(board,-1,hi_col,turn);
            printf("\n\n\n\033[0;31mPlayer 1s turn: (enter move like C4 etc.) \033[0m\n");
            printf("\nSelected col: %c\n",col);
            
            printf("Enter row: ");
            scanf("%d",&row);
            row_index = row - 1;
            hi_row = row_index;

            printBoard(board,hi_row,hi_col,turn);
            printf("\n\n\nA\033[0;31mPlayer 1s turn: (enter move like C4 etc.) \033[0m\n");
            printf("\nSelected col: %c\n",col);
            printf("Selected row: %d\n",row);
            
            printf("Press Enter to confirm or c to cancel: ");
            char cancel;
            char discard;
            scanf("%c",&discard);
            scanf("%c",&cancel);
            
            if (cancel=='c') continue;

            
            
            if(col_index == 0 || col_index == board_size-1){
                    printf("Invalid move! Coordinates out of bounds.\n");
                    continue;
            }

            if (row_index < 0 || row_index >= board_size || col_index < 0 || col_index >= board_size) {
                printf("Invalid move! Coordinates out of bounds.\n");
                continue;
            }

            if (board[row_index][col_index] == -1) { 
                board[row_index][col_index] = 0;
                printBoard(board,-1,-1,turn);
                checkLinks(board, row_index, col_index, turn);
            } else {
                printf("Invalid move! Spot is already taken.\n");
                continue;
            }
        }
        else if(turn) {
            printf("\n\n\n\033[1;34mPlayer 2s turn: (enter move like C4 etc.) \033[0m\n");
            
            printf("\nEnter Coloumn: ");
            scanf(" %c",&col);
            col = toupper(col);
            col_index = (int)col - 'A';
            hi_col = col_index;

            printBoard(board,-1,hi_col,turn);
            printf("\n\n\n\033[1;34mPlayer 2s turn: (enter move like C4 etc.) \033[0m\n");
            printf("\nSelected col: %c\n",col);
            
            printf("Enter row: ");
            scanf("%d",&row);
            row_index = row - 1;
            hi_row = row_index;

            printBoard(board,hi_row,hi_col,turn);
            printf("\n\n\n\033[1;34mPlayer 2s turn: (enter move like C4 etc.) \033[0m\n");
            printf("\nSelected col: %c\n",col);
            printf("Selected row: %d\n",row);
            
            printf("Press Enter to confirm or c to cancel: ");
            char cancel;
            char discard;
            scanf("%c",&discard);
            scanf("%c",&cancel);
            
            if (cancel=='c') continue;

            col_index = (int)col - 'A';
            row_index = row - 1;

            if (row_index==0 || row_index==board_size-1){
                printf("Invalid move! Coordinates out of bounds.\n");
                continue;
            }
            
            
            if (row_index < 0 || row_index >= board_size || col_index < 0 || col_index >= board_size ) {
                printf("Invalid move! Coordinates out of bounds.\n");
                continue;
            }

            if (board[row_index][col_index] == -1) { 
                board[row_index][col_index] = 1;
                printBoard(board,-1,-1,turn);
                checkLinks(board, row_index, col_index, turn);
            } else {
                printf("Invalid move! Spot is already taken.\n");
                continue;
            }
        }
        
        if (gameOver(board, visited, turn)) {
            
            break;
        }
        
        turn=1-turn;
    }

    free(links_arr);
    return 0;
}

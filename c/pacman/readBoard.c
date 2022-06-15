#include <stdio.h>

void read_board_from_file(char *filename, int board[30][40])
{
    FILE *base;
    base = fopen(filename, "r");
    int s = '0';
    int i=0, j=0;
    while ((s=fgetc(base)) != EOF)
    {
        if (s == '\n') {
            i++;
            j = 0;
            continue;
        }
        board[i][j] = s - '0';
        j++;
    }
}

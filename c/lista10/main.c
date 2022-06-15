#include <stdio.h>
#include <stdlib.h>

/*
    -1 - puste pole
    0 - kolko (user)
    1 - krzyzyk (ai)
*/

int board[3][3];
int check_board();

void ai()
{
    //random or defend
    int moveX = -1, moveY = -1;
    int columns[3] = {0,0,0};
    int rows[3] = {0,0,0};
    int diagonals[2] = {0,0};

    //posumuj kolumny i rows i diagonale i jak 2 to albo wygrywaj albo nie przegrywaj :))
}

void print_board()
{
    printf("    a b c\n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d   ", i+1);
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == -1) printf("E ");
            if (board[i][j] == 0) printf("O ");
            if (board[i][j] == 1) printf("X ");
        }
        printf("\n");
    }
}

void move()
{
    print_board(board);
    char pos[2];
    printf("Wybierz pole\n");
    scanf("%s", &pos[0]);
    int x, y;
    y = (int)(pos[1] - '0') - 1;
    if (pos[0] == 'a') x = 0;
    if (pos[0] == 'b') x = 1;
    if (pos[0] == 'c') x = 2;
    if (x > 2 || x < 0 || y > 2 || y < 0)
    {
        printf("Niepoprawne pole. \n");
        return move();
    }
    if (board[y][x] != -1)
    {
        printf("To pole jest już zajęte.\n");
        return move();
    }
    board[y][x] = 0;
    if (check_board() == -1)
    {
        system("cls");
        move();
    }
    print_board();
}

int check_board()
{
    //rows
    int rows[3] = { 0, 0, 0 };
    for (int i = 0; i < 3; i++)
    {
        int sign = board[i][0];
        for (int j = 0; j < 3; j++)
            if (board[i][j] == sign) rows[i]++;
    }
    for (int i = 0; i < 2; i++) if (rows[i] == 3) return board[i][0];
    //columns
    int columns[3] = { 0, 0, 0 };
    for (int i = 0; i < 3; i++)
    {
        int sign = board[0][i];
        for (int j = 0; j < 3; j++)
            if (board[j][i] == sign) columns[i]++;
    }
    for (int i = 0; i < 2; i++) if (columns[i] == 3) return board[0][i];
    //diagonals
    for (int i = 0; i < 3; i++)
    {
        int sign = board[1][1];
        if (board[0][0] == sign && board[2][2] == sign) return sign;
        if (board[0][2] == sign && board[2][0] == sign) return sign;
    }
    return -1;
}

int main()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = -1;
    move();
    return 0;
}

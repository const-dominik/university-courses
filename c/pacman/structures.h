#include <stdbool.h>
#include <gtk/gtk.h>

#ifndef STRUCTURES_H
#define STRUCTURES_H
typedef struct Pacman {
    int x;
    int y;
    int lives;
    int points;
    int moving_direction;
} pacman;

typedef struct Gamedata {
    bool difficulty; // false - easy, true - hard
    char username[15];
} gamedata;

typedef struct Instancedata {
    GtkWidget *grid;
    pacman *pac;
    int board[30][40];
} inst;
#endif // STRUCTURES_H

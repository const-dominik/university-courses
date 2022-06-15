#include <gtk/gtk.h>
#include "readBoard.h"
#include "structures.h"
#include "handleGrid.h"
#include "handleMove.h"

int board[30][40];
pacman pac;

void start_new_game(gamedata gdata)
{

    read_board_from_file("base.txt", board);
    if (!gdata.difficulty) pac.lives = 3;
    if (gdata.difficulty) pac.lives = 1;
    pac.moving_direction = -1;
    pac.points = 0;
    //temp
    pac.x = 20;
    pac.y = 10;

    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"PACMAN");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 40*32, 30*32);
    gtk_widget_show(window);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    generate_base_grid(grid, board);
    edit_grid_at(grid, 20, 10, "images/p-r.png");
    g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(key_press), grid);

    gtk_widget_show_all(window);
}

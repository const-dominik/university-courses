#include <gtk/gtk.h>
#include "structures.h"
void handle_move(GtkWidget *grid, int x, int y, char *img_name, int board[30][40], pacman *pac);
void move(GtkWidget *grid, pacman *pac, int board[30][40]);
void key_press(GtkWidget* widget, GdkEventKey *event, gpointer data);

#include <gtk/gtk.h>
#include "handleGrid.h"
#include "structures.h"

extern pacman pac;
extern int board[30][40];
int timeout = 0;

void handle_move(GtkWidget *grid, int x, int y, char *img_name)
{
    edit_grid_at(grid, pac.x, pac.y, img_name);
    if (board[y][x] != 0)
    {
        GtkWidget *image = gtk_grid_get_child_at(GTK_GRID(grid), pac.x, pac.y);
        gtk_image_clear(GTK_IMAGE(image));
        if (board[y][x] == 1) {
            pac.points++;
            printf("Score: %i\n", pac.points);
            if (pac.points == 798) // max points
            {
                printf("You won! :))");
                gtk_window_close(GTK_WINDOW(grid));
            }
        }
        if (board[y][x] == 3 || board[y][x] == 4) {
            pac.lives--;
            handle_move(grid, 20, 10, img_name);
            printf("Lives left: %d\n", pac.lives);
            if (pac.lives == 0) gtk_window_close(GTK_WINDOW(grid));
            return;
        }
        board[pac.y][pac.x] = 5;
        board[y][x] = 2;
        edit_grid_at(grid, x, y, img_name);
        pac.x = x;
        pac.y = y;
    };
    return;
}

int move(gpointer data)
{
    /*  0 - up, 1 - down, 2 - right, 3 - left */
    int dir = pac.moving_direction;
    if (dir == 0) handle_move(data, pac.x, pac.y-1, "images/p-u.png");
    if (dir == 1) handle_move(data, pac.x, pac.y+1, "images/p-d.png");
    if (dir == 2) handle_move(data, pac.x+1, pac.y, "images/p-r.png");
    if (dir == 3) handle_move(data, pac.x-1, pac.y, "images/p-l.png");
    return 1; //returns 1 so the interval never stops
}

void key_press(GtkWidget* widget, GdkEventKey *event, gpointer data)
{
    guint val = event->keyval;
    int dir = -1;
    if (val == GDK_KEY_Up) dir = 0;
    if (val == GDK_KEY_Down) dir = 1;
    if (val == GDK_KEY_Right) dir = 2;
    if (val == GDK_KEY_Left) dir = 3;
    pac.moving_direction = dir;
    if (!timeout)
    {
        timeout = 1;
        g_timeout_add(100, G_SOURCE_FUNC(move), data);
    }
}

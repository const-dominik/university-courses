#include <stdio.h>
#include <gtk/gtk.h>

/*0 - collision, 1 - fruit, 2 - pacman, 3 - ghost, 4 - ghost that's above fruit, 5 - empty*/

void generate_base_grid(GtkWidget *grid, int board[30][40])
{
    char *images[5] = { "images/collision.png", "images/fruit.png", "images/p-r.png", "images/ghost.png", "images/ghost.png" };
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 40; j++) {
            GtkWidget *image = gtk_image_new_from_file(images[board[i][j]]);
            gtk_grid_attach(GTK_GRID(grid), image, j, i, 1, 1);
        }
    }
}

void edit_grid_at(GtkWidget *grid, int x, int y, char *img_name)
{
    GtkWidget *image = gtk_grid_get_child_at(GTK_GRID(grid), x, y);
    gtk_image_clear(GTK_IMAGE(image));
    image = gtk_image_new_from_file(img_name);
    gtk_grid_attach(GTK_GRID(grid), image, x, y, 1, 1);
    gtk_widget_show(image);
}

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "newGameMenu.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    new_game_menu();
    gtk_main();

    return 0;
}

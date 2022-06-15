#include "structures.h"
#include "newGame.h"
#include <gtk/gtk.h>

gamedata data = { false, "" };

void change_difficulty(GtkRadioButton* self, gpointer cbdata)
{
    data.difficulty = !data.difficulty;
}

void change_username(GtkEditable* self, gpointer cbdata)
{
    strcpy(data.username, gtk_editable_get_chars(self, 0, 15));
}

void play(GtkButton *self, gpointer cbdata)
{
    gtk_window_close(cbdata);
    start_new_game(data);
}

void new_game_menu()
{
    GtkWidget *window, *radio1, *radio2, *box, *label1, *label2, *label3, *button, *entry;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), 0);
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous (GTK_BOX(box), TRUE);

    //difficulty choice
    label1 = gtk_label_new("Choose difficulty: ");
    radio1 = gtk_radio_button_new_with_label(NULL, "EASY");
    radio2 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio1), "HARD");
    g_signal_connect(G_OBJECT(radio2), "toggled", G_CALLBACK(change_difficulty), NULL);

    //username
    label2 = gtk_label_new("Enter your username: ");
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), 15);
    g_signal_connect(G_OBJECT(entry), "changed", G_CALLBACK(change_username), NULL);

    //start game
    label3 = gtk_label_new("PLAY");
    button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(button), label3);

    gtk_box_pack_start(GTK_BOX(box), label1, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(box), radio1, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(box), radio2, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(box), label2, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(box), entry, 1, 1, 0);
    gtk_box_pack_start(GTK_BOX(box), button, 1, 1, 0);
    gtk_container_add(GTK_CONTAINER (window), box);
    gtk_widget_show_all(window);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(play), window);
}


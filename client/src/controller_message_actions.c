#include "controller_message_actions.h"

static GtkGrid*   message_actions_grid = NULL;
static long selected_message = -1;
static GtkLabel* selected_message_label = NULL;


void callback_edit_message(GtkWidget *b, GdkEventButton *event,  char* text) {
    if (selected_message != -1)
        printf("edit message: %i\n", selected_message);
    
    GtkGrid* edit_grid = gtk_grid_new();
    gtk_grid_insert_row(edit_grid, 0);
    gtk_grid_insert_row(edit_grid, 1);

    GtkEntry* entry = gtk_entry_new();
    gtk_entry_set_text(entry, gtk_label_get_text(selected_message_label));

    GtkButton* send_edited = gtk_button_new_with_label("Send");

    gtk_grid_attach(edit_grid, entry, 0, 0, 1, 1);
    gtk_grid_attach(edit_grid, send_edited, 0, 1, 1, 1);

    GtkPopover* edit_popover = gtk_popover_new(b);
    gtk_popover_set_position(edit_popover, GTK_POS_RIGHT);

    gtk_container_add(GTK_CONTAINER(edit_popover), edit_grid);

    gtk_widget_show_all(edit_popover);
}

void callback_reply_message(GtkWidget *b, GdkEventButton *event,  char* text) {
    if (selected_message != -1) {
        printf("reply message: %i\n", selected_message);
    }
}

void callback_forward_message(GtkWidget *b, GdkEventButton *event,  char* text) {
    if (selected_message != -1)
        printf("forward message: %i\n", selected_message);
}


void create_message_actions_grid() {

    message_actions_grid = gtk_grid_new();
    

    GtkButton* edit = gtk_button_new_with_label("Edit");
    GtkButton* reply = gtk_button_new_with_label("Reply");
    GtkButton* forward = gtk_button_new_with_label("Forward");

    g_signal_connect(edit, "clicked", callback_edit_message, NULL);
    g_signal_connect(reply, "clicked", callback_reply_message, NULL);
    g_signal_connect(forward, "clicked", callback_forward_message, NULL);

    gtk_grid_insert_column(message_actions_grid, 0);
    gtk_grid_insert_row(message_actions_grid, 0);
    gtk_grid_insert_row(message_actions_grid, 1);
    gtk_grid_insert_row(message_actions_grid, 2);

    gtk_grid_attach(message_actions_grid, edit, 0, 0, 1, 1);
    gtk_grid_attach(message_actions_grid, reply, 0, 1, 1, 1);
    gtk_grid_attach(message_actions_grid, forward, 0, 2, 1, 1);

}

void callback_message_actions_popover_closed(GtkWidget* popover, GdkEventButton* event, gpointer* data) {
    gtk_widget_destroy(popover);
    selected_message = -1;
    selected_message_label = NULL;
    message_actions_grid = NULL;
}

void show_message_actions_popover(GtkWidget* label) {
    if (message_actions_grid == NULL) {
        create_message_actions_grid();
    }

    GtkWidget* message_popover =  gtk_popover_new (label);
    selected_message_label = label;
    gtk_container_add(GTK_CONTAINER(message_popover), GTK_WIDGET(message_actions_grid));
    gtk_popover_set_position(message_popover, GTK_POS_RIGHT);
    gtk_widget_show_all(message_popover);
    gtk_popover_popup(message_popover);
    g_signal_connect(message_popover, "closed", callback_message_actions_popover_closed, NULL);
}

void callback_click_message(GtkWidget *b, GdkEventButton *event,  t_model_message* model_message) {

    printf("message id: %zu\n", model_message->id);
    // GtkMenu* menu = gtk_menu_new();
    // GtkMenuItem* edit = gtk_menu_item_new_with_label("Edit");
    // gtk_menu_shell_append(GTK_MENU_SHELL(menu), edit);

    GList* childs = gtk_container_get_children(GTK_CONTAINER(b));
    GtkLabel* label = GTK_LABEL(childs->data);
    
    show_message_actions_popover(label);
    selected_message = (long)model_message->id;

    g_list_free(childs);
}
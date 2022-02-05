#include "choose_chat.h"



void choose_chat(GtkButton *b, t_current_window_info *current_window_info) {
	printf("You selected: %s\n", gtk_button_get_label (b));


    set_in_protocol_string(get_cookies(), "TO USER", gtk_button_get_label(b));

    int count = 0;
    int *count_tmp = (int*)malloc(sizeof(int));
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "chat_window_grid"));


    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(chat_window_grid));
    
    for(iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    
    g_list_free(children);

    t_model_message **model_message = get_all_messages_from_chat((char*)gtk_button_get_label (b), &count);

    set_current_user_to_talk((char*)gtk_button_get_label (b));

    for (int i = 0; i < 20; i++)
    {
        GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade"));
        gtk_grid_insert_row(GTK_GRID(chat_window_grid), i);
        gtk_grid_attach(GTK_GRID(chat_window_grid), GTK_WIDGET(gtk_builder_get_object(message_builder, "invisible_label")), 1, i, 1, 1);
    }
    current_window_info->message_position_y = count + 20;

    view_messages(model_message, current_window_info, count);

}


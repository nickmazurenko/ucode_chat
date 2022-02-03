#include "view_chat_window.h"

//tmp to delete
static char *current_user_to_talk = NULL;

 char *get_current_user_to_talk(void) {
    return current_user_to_talk;
}

 void set_current_user_to_talk(char *new_user_to_talk) {
    
    if(current_user_to_talk) {
        mx_strdel(&current_user_to_talk);
    }
    current_user_to_talk = mx_strdup(new_user_to_talk);

}

void view_chat_window(t_current_window_info *current_layout_info)
{

    // add css for  messages

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("messages.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    int count = 0;
    
    char tmp[1024];
    int row = 0;

    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
    {
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    }
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("chat_window.glade"), NULL); ///////rename --> done

    GtkWidget *gtk_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_scrolled"));

    gtk_scrolled_window_set_policy(gtk_scrolled_window, GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));

    GtkWidget *send_message_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "send_message_button"));

    g_signal_connect(send_message_button, "clicked", G_CALLBACK(send_message_button_clicked), current_layout_info);

    GtkWidget *chat_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_viewport"));
    
    GtkAdjustment *adjustment = gtk_viewport_get_vadjustment(chat_viewport);
    
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));

    GtkLayout *chat_window_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "chat_window_layout")); /// rename --> done

    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid"));

    GtkWidget *home_chats_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_scrolled_window")); 

    gtk_scrolled_window_set_policy(home_chats_scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    // gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout)); // ya huy znaet kakoy layout ebanut` zdes`

    // gtk_container_add(GTK_CONTAINER(home_page_layout), GTK_WIDGET(chat_window_layout));

    current_layout_info->layout_exists = true;

    row = 0;
    gtk_grid_insert_column(GTK_GRID(chat_window_grid), 0);
    gtk_grid_insert_column(GTK_GRID(chat_window_grid), 1);

    int* count_tmp = malloc(sizeof(int));
    *count_tmp = count + 20;

    current_layout_info->data = (void *)(count_tmp);
    

    gtk_widget_show_all(current_layout_info->main_window);
    
}

void view_messages(t_model_message **model_message, t_current_window_info *current_layout_info, int size)
{
    GtkWidget *label[size];
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid"));

    for (int message_id = 0; message_id < size; message_id++)
    {
        GtkWidget *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade"));

        gtk_grid_insert_row(GTK_GRID(chat_window_grid), message_id + 20);
        if (!strcmp(model_message[message_id]->from_user, get_from_protocol_string(get_cookies(), "USERNAME")))
        {

            label[message_id] = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_label"));

            gtk_label_set_text(GTK_LABEL(label[message_id]), model_message[message_id]->data);

            gtk_grid_attach(GTK_GRID(chat_window_grid), label[message_id], 1, message_id + 20, 1, 1);
        }
        else
        {

            label[message_id] = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_label"));
            gtk_label_set_text(GTK_LABEL(label[message_id]), model_message[message_id]->data);

            gtk_label_set_xalign(GTK_LABEL(label[message_id]), 0.5);
            gtk_label_set_justify(GTK_LABEL(label[message_id]), GTK_JUSTIFY_LEFT);
            gtk_grid_attach(GTK_GRID(chat_window_grid), label[message_id], 0, message_id + 20, 1, 1);
        }
    }

}

void view_message(t_model_message *model_message, t_current_window_info *current_layout_info)
{
    GtkWidget *label;
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid"));

    int current_id = *((int*)(current_layout_info->data)) + 1;

    GtkWidget *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade"));

    gtk_grid_insert_row(GTK_GRID(chat_window_grid), current_id);
    if (!strcmp(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME")))
    {

        label = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_label"));

        gtk_label_set_text(GTK_LABEL(label), model_message->data);

        gtk_grid_attach(GTK_GRID(chat_window_grid), label, 1, current_id, 1, 1);
    }
    else
    {

        label = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_label"));
        gtk_label_set_text(GTK_LABEL(label), model_message->data);

        gtk_label_set_xalign(GTK_LABEL(label), 0.5);
        gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT);
        gtk_grid_attach(GTK_GRID(chat_window_grid), label, 0, current_id, 1, 1);
    }
    current_layout_info->data = (void*)current_id;
}

void send_message_button_clicked(GtkWidget *widget, t_current_window_info *current_window_info)
{
    GtkWidget *type_message_entry = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "type_message_entry"));

    char *message_str = mx_strdup(gtk_entry_get_text(type_message_entry));
    // t_model_message *message = controller_send_message("a", MESSAGE_TEXT, message_str);
    t_model_message *message = NULL;
    if(current_user_to_talk) 
        message = controller_send_message(get_current_user_to_talk(), MESSAGE_TEXT, message_str);
    
    gtk_entry_set_text(type_message_entry, "");

    view_message(message, current_window_info);
}

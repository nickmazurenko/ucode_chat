#include "view_messages.h"


char *get_current_user_to_talk(void) {
    return get_from_protocol_string(get_cookies(), "TO USER");
}

void set_current_user_to_talk(char *new_user_to_talk) {
    
    if(get_from_protocol_string(get_cookies(), "TO USER")) {
        set_in_protocol_string(get_cookies(), "TO USER", new_user_to_talk);
    } else {
        add_to_protocol_string(get_cookies(), "TO USER", new_user_to_talk);
    }
    
}


void view_messages(t_model_message **model_message, t_current_window_info *current_layout_info, int size) 
{ 
    GtkWidget *label[size]; 
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid")); 
 
    for (int message_id = 0; message_id < size; message_id++) 
    { 
        if(model_message[message_id]->data_type == MESSAGE_TEXT){
            view_message(model_message[message_id], current_layout_info); 
        } else if (model_message[message_id]->data_type == MESSAGE_FILE) {
            view_file(model_message[message_id], current_layout_info);
        }  
    } 
 
} 
 
void view_message(t_model_message *model_message, t_current_window_info *current_layout_info) 
{ 
    GtkWidget *label; 
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid")); 
 
    int current_id = current_layout_info->message_position_y + 1; 
 
    GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade")); 
 
    gtk_grid_insert_row(GTK_GRID(chat_window_grid), current_id); 

    GtkWidget* box = gtk_event_box_new();

    if (!strcmp(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"))) 
    { 
 
        label = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_label")); 
        gtk_label_set_text(GTK_LABEL(label), model_message->data);

        gtk_container_add(GTK_CONTAINER(box), label);
 
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 1, current_id, 1, 1); 
        gtk_widget_show (box);

    } 
 
    else 
    { 
 
        label = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_label")); 
        gtk_label_set_text(GTK_LABEL(label), model_message->data); 

        gtk_container_add(GTK_CONTAINER(box), label);

        gtk_label_set_xalign(GTK_LABEL(label), 0.5); 
        gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_LEFT); 
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 0, current_id, 1, 1); 
        gtk_widget_show (box);

    } 

    g_signal_connect(box, "button_press_event", callback_click_message, model_message);
 
    current_layout_info->message_position_y = current_id; 
 
    GtkWidget *chat_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_viewport")); 
     
    GtkAdjustment *adjustment = gtk_viewport_get_vadjustment(GTK_VIEWPORT(chat_viewport)); 
    gtk_adjustment_set_upper(adjustment, gtk_adjustment_get_upper(adjustment) + 500); 
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment)); 
} 

void view_file(t_model_message *model_message, t_current_window_info *current_layout_info){
    GtkWidget *image;
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid")); 

    int current_id = current_layout_info->message_position_y + 1; 

    gtk_grid_insert_row(GTK_GRID(chat_window_grid), current_id); 

    GtkWidget* box = gtk_event_box_new();

    if(!strcmp(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"))){
        
        t_model_resource *msg_resource = get_resource_by_id(model_message->data);
        char * real_path = request_file_if_not_exist(msg_resource->path);

        GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size(real_path, 100, 100, NULL);
        if (image_pixbuf) {
            GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_image.glade")); 

            image = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_image"));
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        } else {
            GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade")); 
            image = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_label")); 
            gtk_label_set_text(GTK_LABEL(image), "CLICK TO OPEN");
        }
        gtk_container_add(GTK_CONTAINER(box), image);      
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 1, current_id, 1, 1); 
        gtk_widget_show (box);

    } else {
        t_model_resource *msg_resource = get_resource_by_id(model_message->data);
        char * real_path = request_file_if_not_exist(msg_resource->path);

        GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size(real_path, 100, 100, NULL);
        if (image_pixbuf) {
            GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_image.glade")); 

            image = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_image"));
            gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        } else {
            GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade")); 
            image = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_label")); 
            gtk_label_set_text(GTK_LABEL(image), "CLICK TO OPEN");
        }
        gtk_container_add(GTK_CONTAINER(box), image);      
        gtk_grid_attach(GTK_GRID(chat_window_grid), box, 0, current_id, 1, 1); 
        gtk_widget_show (box);
    }


    g_signal_connect(box, "button_press_event", callback_click_message, model_message);
 
    current_layout_info->message_position_y = current_id; 
 
    GtkWidget *chat_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_viewport")); 
     
    GtkAdjustment *adjustment = gtk_viewport_get_vadjustment(GTK_VIEWPORT(chat_viewport)); 
    gtk_adjustment_set_upper(adjustment, gtk_adjustment_get_upper(adjustment) + 500); 
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment)); 
    
}


void send_message_button_clicked(GtkWidget *widget, t_current_window_info *current_window_info)
{
    GtkWidget *type_message_entry = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "type_message_entry"));
    char *message_str = mx_strdup((char*)gtk_entry_get_text(GTK_ENTRY(type_message_entry)));
    t_model_message *message = NULL;
    char *to_user = get_current_user_to_talk();
    if(to_user) 
        message = controller_send_message(to_user, MESSAGE_TEXT, message_str);
    
    if (message != NULL) {
        gtk_entry_set_text(GTK_ENTRY(type_message_entry), "");
        view_message(message, current_window_info);
    }
}

void send_file_as_message(GtkWidget *widget, t_current_window_info * current_window_info){ 
 
    GtkWidget *file_chooser = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "gtkfile_chooser_button")); 
 
    char *selected_file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser)); 
    t_model_message *message = NULL;
    char *to_user = get_current_user_to_talk();
    if(to_user) 
        message = controller_send_message(to_user, MESSAGE_FILE, selected_file);
    if (message != NULL) {
        gtk_file_chooser_unselect_all(GTK_FILE_CHOOSER(file_chooser));
        view_file(message, current_window_info);
    }
}
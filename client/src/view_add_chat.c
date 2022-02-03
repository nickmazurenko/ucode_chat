#include "controller_start_chat.h"


void add_chat_clicked(GtkWidget *widget, t_current_window_info *current_window_info) {
    
    GtkWidget *add_chat_entry = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "add_chat_entry"));

    char *user_to_find = (char*)gtk_entry_get_text(GTK_ENTRY(add_chat_entry));
   

    if(user_to_find && strlen(user_to_find) > 0) {
        if(send_start_chat_request(user_to_find)) {
            add_chat(user_to_find, current_window_info);
            gtk_widget_show_all(current_window_info->main_window);
        } else {
            NULL;
        }
    }
    gtk_entry_set_text(GTK_ENTRY(add_chat_entry), "");

}

void set_add_chat_on_button(GtkWidget *button, t_current_window_info *current_window_info) {

    // int questions_number = set_quiz_from_file(&quiz_questions, "quiz");

    // printf("%s\n", cJSON_Print(quiz_questions));

    gtk_button_set_image (GTK_BUTTON (button), gtk_image_new_from_icon_name ("open-menu-symbolic", GTK_ICON_SIZE_BUTTON));

    GtkWidget *add_chat_popover;

    gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("add_chat.glade"), NULL);


	GtkWidget *add_chat_layout = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "add_chat_layout"));
    
    GtkWidget *add_chat = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "add_chat"));

    add_chat_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (add_chat_popover), add_chat_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), add_chat_popover);

    g_signal_connect (G_OBJECT (add_chat), "clicked", G_CALLBACK (add_chat_clicked), current_window_info);
}
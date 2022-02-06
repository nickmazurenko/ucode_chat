#include "view_stone_age_page.h"


static guint thread_id = 0;


// gboolean callback_update_messages(gpointer* user_data) {

//     t_current_window_info *current_window_info = (t_current_window_info*)user_data;
//     int count = 0;
//     t_model_message** messages = controller_get_new_messages(&count);
//     // g_source_remove(thread_id);
//     if (count != 0) {
//         // view_messages(messages, current_window_info, count);
//         for (int i = 0; i < count; i++) {
//             if(!strcmp(messages[i]->from_user, get_current_user_to_talk()))
//                 view_message(messages[i], current_window_info);
//             free_model_message(&(messages[i]));
//         }
//         mx_printstr("\a");
//         fflush(stdout);
//         free(messages);
//     }

//     // thread_id = g_timeout_add(10000, callback_update_messages, current_window_info);
//     // thread_id =g_timeout_add_seconds(10, callback_update_messages, current_window_info);

//     return TRUE;
// }


// void	choose_chat(GtkButton *b, t_current_window_info *current_window_info) {
// 	printf("You selected: %s\n", gtk_button_get_label (b));


//     set_in_protocol_string(get_cookies(), "TO USER", gtk_button_get_label(b));

//     int count = 0;
//     int *count_tmp = (int*)malloc(sizeof(int));
//     GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "chat_window_grid"));


//     GList *children, *iter;

//     children = gtk_container_get_children(GTK_CONTAINER(chat_window_grid));
    
//     for(iter = children; iter != NULL; iter = g_list_next(iter))
//         gtk_widget_destroy(GTK_WIDGET(iter->data));
    
//     g_list_free(children);

//     t_model_message **model_message = get_all_messages_from_chat((char*)gtk_button_get_label (b), &count);

//     set_current_user_to_talk((char*)gtk_button_get_label (b));

//     for (int i = 0; i < 20; i++)
//     {
//         GtkBuilder *message_builder = gtk_builder_new_from_file(get_path_to_glade("message_labels.glade"));
//         gtk_grid_insert_row(GTK_GRID(chat_window_grid), i);
//         gtk_grid_attach(GTK_GRID(chat_window_grid), GTK_WIDGET(gtk_builder_get_object(message_builder, "invisible_label")), 1, i, 1, 1);
//     }
//     current_window_info->message_position_y = count + 20;

//     view_messages(model_message, current_window_info, count);

//     // thread_id = g_timeout_add(10000, callback_update_messages, current_window_info);
// }
    


void view_stone_age_page(t_current_window_info *current_layout_info)
{

    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("stone_age_era.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
    GtkWidget *button[1000];

    char tmp[1024];
    int column = 0;
    
    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
    {
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    }
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("stone_age_era.glade"), NULL);
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("quiz.glade"), NULL);
    
///////// TODO: NADO ?
    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));

    GtkWidget *home_page_fixed = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_page_fixed"));

    GtkWidget *home_chats_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_viewport"));

    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_grid"));
/////////
    GtkWidget *home_chats_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_scrolled_window")); 
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(home_chats_scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

    GtkWidget *profile_info_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "profile_info_button"));
    GtkWidget *profile_info_icon_img = gtk_image_new_from_file("./client/resources/static/images/sa_profile_info_icon.png");
    gtk_button_set_image(GTK_BUTTON(profile_info_button), profile_info_icon_img);

    GtkWidget *quiz_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "quiz_button"));
    GtkWidget *quiz_icon_img = gtk_image_new_from_file("./client/resources/static/images/sa_quiz_icon.png");
    gtk_button_set_image(GTK_BUTTON(quiz_button), quiz_icon_img);


    GtkWidget *shop_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "shop_button"));
    GtkWidget *shop_icon_img = gtk_image_new_from_file("./client/resources/static/images/sa_shop_icon.png");
    gtk_button_set_image(GTK_BUTTON(shop_button), shop_icon_img);

    GtkWidget *settings_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "settings_button"));
    GtkWidget *settings_icon_img = gtk_image_new_from_file("./client/resources/static/images/sa_settings_icon.png");
    gtk_button_set_image(GTK_BUTTON(settings_button), settings_icon_img);

    GtkWidget *add_chat_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "add_chat_button"));


    
    set_quiz_on_button(quiz_button);
    
    set_add_chat_on_button(GTK_WIDGET(add_chat_button), current_layout_info);

    set_user_info_on_button(profile_info_button, current_layout_info);


    // view_chat_window(current_layout_info);
    
    int user_chats_count = 0; 
    char **user_chats = get_all_user_chats(get_from_protocol_string(get_cookies(), "USERNAME"), &user_chats_count); 

    add_chats(user_chats, current_layout_info, user_chats_count);

    for(int i = 0; i < user_chats_count;i++){ 
        printf("USER CHATS: %s\n\n", user_chats[i]); 
    }

    // TODO: add era checker;
    // add_draw_area(current_layout_info);
 


    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));
    current_layout_info->layout_exists = true;


    // g_signal_connect(draw_button, "clicked", G_CALLBACK(add_drawing_area_clicked), current_layout_info);
	column = 0;

        gtk_widget_show_all(GTK_WIDGET(home_page_layout));
    thread_id = g_timeout_add_seconds(10, callback_update_messages, current_layout_info);


}

// char *request_file_if_not_exist(char *file) {
//     char *path = mx_replace_substr(file, "./server", "./client");
//     if(is_client_file(path)) {
//         return path;
//     } else {
//         char *server_path = mx_replace_substr(file, "./server", "");
//         get_file(server_path);
//         return path;
//     }
// }

// bool is_client_file(char *path) {
//     FILE *file;
//     if(!(file = fopen(path, "r"))) {
//         return 0;
//     } else {
//         fclose(file);
//         return 1;
//     }
// }

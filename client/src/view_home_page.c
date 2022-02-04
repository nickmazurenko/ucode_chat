#include "view_home_page.h"
#include "controller_get_messages.h"

static int current_chat_count = 0;
static guint thread_id = 0;

int get_current_chat_count() {
    return current_chat_count;
}

gboolean callback_update_messages(gpointer* user_data) {

    t_current_window_info *current_window_info = (t_current_window_info*)user_data;
    int count = 0;
    t_model_message** messages = controller_get_new_messages(&count);
    // g_source_remove(thread_id);
    if (count != 0) {
        // view_messages(messages, current_window_info, count);
        for (int i = 0; i < count; i++) {
            view_message(messages[i], current_window_info);
            free_model_message(&(messages[i]));
        }
        mx_printstr("\a");
        fflush(stdout);
        free(messages);
    }

    // thread_id = g_timeout_add(10000, callback_update_messages, current_window_info);
    // thread_id =g_timeout_add_seconds(10, callback_update_messages, current_window_info);

    return TRUE;
}


void	on_column(GtkButton *b, t_current_window_info *current_window_info) {
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
    // *count_tmp = count + 20;
    // current_window_info->data = (void *)(count_tmp);

    current_window_info->message_position_y = count + 20;

    view_messages(model_message, current_window_info, count);

    // thread_id = g_timeout_add(10000, callback_update_messages, current_window_info);
}
    

gboolean add_drawing_area_clicked(GtkWidget *widget, t_current_window_info *current_window_info) {
    
    add_draw_area(current_window_info);


    return TRUE;
}



void view_home_page(t_current_window_info *current_layout_info)
{
    GtkWidget *button[1000];

    char tmp[1024];
    int column = 0;
    
    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
    {
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    }
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("home_page.glade"), NULL);
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("quiz.glade"), NULL);

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));

    GtkWidget *home_page_fixed = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_page_fixed"));

    GtkWidget *home_chats_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_viewport"));

    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_grid"));

    GtkWidget *quiz_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "quiz_button"));

    GtkWidget *add_chat_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "add_chat_button"));


    GtkWidget *menu_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "menu_button"));


    // GtkWidget *draw_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "draw_button"));
    
    set_quiz_on_button(quiz_button);
    
    set_add_chat_on_button(GTK_WIDGET(add_chat_button), current_layout_info);

    view_chat_window(current_layout_info);
    
    int user_chats_count = 0; 
    char **user_chats = get_all_user_chats(get_from_protocol_string(get_cookies(), "USERNAME"), &user_chats_count); 

    add_chats(user_chats, current_layout_info, user_chats_count);

    for(int i = 0; i < user_chats_count;i++){ 
        printf("USER CHATS: %s\n\n", user_chats[i]); 
    }

    // TODO: add era checker;
    // add_draw_area(current_layout_info);
 
    set_user_info_on_button(menu_button);


    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));
    current_layout_info->layout_exists = true;

    FILE *f1 = fopen("functions.txt", "r");

	if (f1 == NULL ) {
		printf("File finctions.txt not found\n");
		// return EXIT_FAILURE;
		}
    // g_signal_connect(draw_button, "clicked", G_CALLBACK(add_drawing_area_clicked), current_layout_info);
	column = 0;

        gtk_widget_show_all(GTK_WIDGET(home_page_layout));
    thread_id = g_timeout_add_seconds(10, callback_update_messages, current_layout_info);


}

void add_chats(char **username, t_current_window_info *current_window_info, int count) {
    for(int chat_index = 0; chat_index < count; chat_index++) {
        add_chat(username[chat_index], current_window_info);
    }
}


void add_chat(char *username, t_current_window_info *current_window_info) {
    gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("user_chat_button.glade"), NULL);
    

    // gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("home_page.glade"), NULL);

    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "person_chat_button"));
    // GtkWidget *button;
    GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "user_image"));

    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "home_chats_grid"));

    t_model_resource *avatar = send_get_avatar_request(username);
    insert_data_resource(avatar);


    GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size(get_path_to_image("rock.png"), 80, 80, NULL);

    gtk_grid_insert_column (GTK_GRID(home_chats_grid), get_current_chat_count());

    // gtk_grid_attach (GTK_GRID(home_chats_grid), button, get_current_chat_count(), 1, 1, 1);

    	// gtk_grid_insert_column (GTK_GRID(home_chats_grid), get_current_chat_count());

		// button = gtk_button_new_with_label (username);
        gtk_button_set_label(GTK_BUTTON(button), username);

	    gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);
        
        

		// gtk_button_set_alignment (GTK_BUTTON(button), 0.5, 0.0); // hor left, ver center
        gtk_widget_set_size_request(button, 100, 100);
		gtk_grid_attach (GTK_GRID(home_chats_grid), button, get_current_chat_count(), 1, 1, 1);
        
		g_signal_connect(button, "clicked", G_CALLBACK(on_column), current_window_info);

    current_chat_count++;

}
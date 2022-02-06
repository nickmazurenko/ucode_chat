#include "view_last_era.h"

static guint thread_id = 0;

void view_last_era(t_current_window_info *current_layout_info) {

    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("last_era.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *button[1000];

    char tmp[1024];
    int column = 0;

    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("last_era.glade"), NULL);
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("quiz.glade"), NULL);

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));

    GtkWidget *home_page_fixed = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_page_fixed"));

    GtkWidget *home_chats_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_viewport"));

    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_grid"));

    GtkWidget *choose_chat_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "choose_chat_grid"));

    ////
    GtkWidget *home_chats_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_scrolled_window")); 
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(home_chats_scrolled_window), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
    ////

    GtkWidget *profile_info_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "profile_info_button"));
    GtkWidget *profile_info_icon_img = gtk_image_new_from_file("./client/resources/static/images/e_profile_info_icon.png");
    gtk_button_set_image(GTK_BUTTON(profile_info_button), profile_info_icon_img);

    GtkWidget *quiz_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "quiz_button"));
    GtkWidget *quiz_icon_img = gtk_image_new_from_file("./client/resources/static/images/e_quiz_icon.png");
    gtk_button_set_image(GTK_BUTTON(quiz_button), quiz_icon_img);
    // GtkWidget *menu_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "menu_button"));

    GtkWidget *shop_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "shop_button"));
    GtkWidget *shop_icon_img = gtk_image_new_from_file("./client/resources/static/images/e_shop_icon.png");
    gtk_button_set_image(GTK_BUTTON(shop_button), shop_icon_img);

    GtkWidget *settings_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "settings_button"));
    GtkWidget *settings_icon_img = gtk_image_new_from_file("./client/resources/static/images/e_settings_icon.png");
    gtk_button_set_image(GTK_BUTTON(settings_button), settings_icon_img);

    GtkWidget *add_chat_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "add_chat_button"));


    // GtkWidget *menu_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "menu_button"));


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
 
    set_user_info_on_button(profile_info_button, current_layout_info);
    set_setting_on_button(settings_button, current_layout_info);
    set_shop_on_button(shop_button);

    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));
    current_layout_info->layout_exists = true;




    // FILE *f1 = fopen("functions.txt", "r");

	// if (f1 == NULL ) {
	// 	printf("File finctions.txt not found\n");
	// 	// return EXIT_FAILURE;
	// 	}



    // g_signal_connect(draw_button, "clicked", G_CALLBACK(add_drawing_area_clicked), current_layout_info);
	column = 0;

        gtk_widget_show_all(GTK_WIDGET(home_page_layout));
    thread_id = g_timeout_add_seconds(10, callback_update_messages, current_layout_info);
    // thread_id = g_timeout_add_seconds(10, callback_update_messages, current_layout_info);
}

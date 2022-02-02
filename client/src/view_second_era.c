#include "view_second_era.h"

void view_second_era(t_current_window_info *current_layout_info)
{
    GtkWidget *button[1000];

    char tmp[1024];
    int column = 0;
    t_second_era_elements *second_era_elements = create_second_era_elements();

    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("second_era.glade"), NULL);
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("quiz.glade"), NULL);

    second_era_elements->entry = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "type_message_entry"));

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));
    GtkWidget *home_page_fixed = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_page_fixed"));
    GtkWidget *home_chats_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_viewport"));
    GtkWidget *home_chats_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_grid"));

    GtkWidget *buttons_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "choose_word_2era_grid"));
    GtkWidget *button_refresh_words = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button_refresh_words"));
    second_era_elements->buttons[0] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_1"));
    second_era_elements->buttons[1] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_2"));
    second_era_elements->buttons[2] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_3"));
    second_era_elements->buttons[3] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_4"));
    second_era_elements->buttons[4] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button1_5"));
    second_era_elements->buttons[5] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_1"));
    second_era_elements->buttons[6] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_2"));
    second_era_elements->buttons[7] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_3"));
    second_era_elements->buttons[8] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_4"));
    second_era_elements->buttons[9] = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "button2_5"));

    GtkWidget *home_chats_scrolled_window = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "home_chats_scrolled_window")); 
    
    gtk_scrolled_window_set_policy(home_chats_scrolled_window, GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    GtkWidget *quiz_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "quiz_button"));
    set_quiz_on_button(quiz_button);
    GtkWidget *menu_button = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "menu_button"));
    set_user_info_on_button(menu_button);

    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));
    current_layout_info->layout_exists = true;


    FILE *f1 = fopen("functions.txt", "r");

	if (f1 == NULL ) {
		printf("File finctions.txt not found\n");
		// return EXIT_FAILURE;
	}


	while (1) {
		if (fgets(tmp, 1024, f1) == NULL) {
			fclose(f1);
			break;
		}

		tmp[strlen(tmp)-1] = 0; // remove newline byte
		
		button[column] = gtk_button_new_with_label (tmp);
		gtk_button_set_alignment (GTK_BUTTON(button[column]), 0.5, 0.0); // hor left, ver center
        gtk_widget_set_size_request(button[column], 100, 100);
		gtk_grid_attach (GTK_GRID(home_chats_grid), button[column], column, 1, 1, 1); // (..., ..., 1, 1) 2,1 3,1 4,1 5,1 1,2 2,2 3,2 4,2 5,2
        
		g_signal_connect(button[column], "clicked", G_CALLBACK(on_column), NULL);
		column++;
	}

    if(!second_era_elements->words)
        second_era_elements->words = get_words_from_file("second_era_words");
    count_words(second_era_elements);
    set_words_on_buttons(second_era_elements);

    g_signal_connect(button_refresh_words, "clicked", G_CALLBACK(refresh_words), second_era_elements);

    g_signal_connect(second_era_elements->buttons[0], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[1], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[2], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[3], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[4], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[5], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[6], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[7], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[8], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    g_signal_connect(second_era_elements->buttons[9], "clicked", G_CALLBACK(add_word_to_message), second_era_elements);
    

    // gtk_widget_show_all(home_page_layout);
}

void set_words_on_buttons(t_second_era_elements *second_era_elements) {
    for (int i = second_era_elements->page * 10 - 10, ind = 0; ind < 10; i++, ind++) {
        if (!second_era_elements->words[i])
            i = 0;
        gtk_button_set_label(GTK_BUTTON(second_era_elements->buttons[ind]), second_era_elements->words[i]);
    }
}

void refresh_words(GtkWidget *widget, t_second_era_elements *second_era_elements) {
    if (second_era_elements->page < second_era_elements->word_count / 10 + 1)
        second_era_elements->page++;
    else
        second_era_elements->page = 1;
    
    set_words_on_buttons(second_era_elements);
}

char **get_words_from_file(char *file_name) {
    char *file = mx_file_to_str(file_name);    
    char **words_arr = mx_strsplit(file, '\n');

    return words_arr;
}

t_second_era_elements *create_second_era_elements() {
    t_second_era_elements *second_era_elements = (t_second_era_elements *)malloc(sizeof(t_second_era_elements));
    second_era_elements->buttons = (GtkWidget **)(malloc(sizeof(GtkWidget *) * 10));
    second_era_elements->words = NULL;
    second_era_elements->page = 1;
    second_era_elements->message = NULL;
    second_era_elements->word_count = 0;
    second_era_elements->entry = NULL;

    return second_era_elements; 
}

void add_word_to_message(GtkWidget *widget, t_second_era_elements *second_era_elements) {
    char *word = gtk_button_get_label(GTK_BUTTON(widget));

    char* buff = NULL;
    if(second_era_elements->message) {
        if((strlen(second_era_elements->message)) <= 140) {

            if (second_era_elements->message) {
                buff = second_era_elements->message;
                second_era_elements->message = mx_strjoin(second_era_elements->message, " ");
                free(buff);
            }

            buff = second_era_elements->message;
            second_era_elements->message = mx_strjoin(second_era_elements->message, word);
         
            if (buff) 
                free(buff);
            
                gtk_entry_set_text(second_era_elements->entry, second_era_elements->message);
        }
    } else {

        buff = second_era_elements->message;
        second_era_elements->message = mx_strjoin(second_era_elements->message, word);

            if (buff) 
                free(buff);
            
        gtk_entry_set_text(second_era_elements->entry, second_era_elements->message);
    }
    printf("%s\n", second_era_elements->message);
}

void count_words(t_second_era_elements *second_era_elements) {
   int word_count = 0;
    for (int i = 0; second_era_elements->words[i]; i++){
        word_count++;
    }

    second_era_elements->word_count = word_count;
}

void clear_second_era_elements(t_second_era_elements *second_era_elements) {
    free(second_era_elements->message);

    for (int i = 0; i < second_era_elements->word_count; i++)
        free(second_era_elements->words[i]);
    free(second_era_elements->words);
}

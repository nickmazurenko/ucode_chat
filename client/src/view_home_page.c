#include "view_home_page.h"

void	on_column(GtkButton *b) {
	printf("You selected: %s\n", gtk_button_get_label (b));
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
    
    set_quiz_on_button(quiz_button);


    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));
    current_layout_info->layout_exists = true;

    FILE *f1 = fopen("functions.txt", "r");

	if (f1 == NULL ) {
		printf("File finctions.txt not found\n");
		// return EXIT_FAILURE;
		}

	column = 0;
	while (1) {
		if (fgets(tmp, 1024, f1) == NULL) {
			fclose(f1);
			break;
			}
		tmp[strlen(tmp)-1] = 0; // remove newline byte
		gtk_grid_insert_column (GTK_GRID(home_chats_grid), column);

		button[column] = gtk_button_new_with_label (tmp);
		gtk_button_set_alignment (GTK_BUTTON(button[column]), 0.5, 0.0); // hor left, ver center
        gtk_widget_set_size_request(button[column], 100, 100);
		gtk_grid_attach (GTK_GRID(home_chats_grid), button[column], column, 1, 1, 1);
		g_signal_connect(button[column], "clicked", G_CALLBACK(on_column), NULL);
		column ++;
		}
        gtk_widget_show_all(home_page_layout);

}
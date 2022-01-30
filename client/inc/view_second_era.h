#ifndef VIEW_SECOND_ERA_H
#define VIEW_SECOND_ERA_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "view_tools.h"
#include "quiz.h"
#include "resources.h"

typedef struct s_second_era_elements {
    GtkWidget **buttons;
    char **words;
    int word_count;
    int page;
    char *message;
    GtkWidget *entry;
}               t_second_era_elements;

t_second_era_elements *create_second_era_elements();
void view_second_era(t_current_window_info *current_layout_info);
char **get_words_from_file(char *file_name);
void set_words_on_buttons(t_second_era_elements *second_era_elements);
void refresh_words(GtkWidget *widget, t_second_era_elements *second_era_elements);
void add_word_to_message(GtkWidget *widget, t_second_era_elements *second_era_ellements);
void count_words(t_second_era_elements *second_era_elements);


#endif
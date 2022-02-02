#ifndef VIEW_HOME_PAGE_H
#define VIEW_HOME_PAGE_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "drawing_area.h"
#include "view_tools.h"
#include "quiz.h"
#include "user_info.h"
#include "resources.h"
#include "view_chat_window.h"

void view_home_page(t_current_window_info *current_layout_info);
void	on_column(GtkButton *b);
int get_current_chat_count();

void add_chat(char *username, t_current_window_info *current_window_info);

#endif
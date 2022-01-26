#ifndef VIEW_HOME_PAGE_H
#define VIEW_HOME_PAGE_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "view_tools.h"
#include "quiz.h"
#include "resources.h"

void view_home_page(t_current_window_info *current_layout_info);
void	on_column(GtkButton *b);

#endif
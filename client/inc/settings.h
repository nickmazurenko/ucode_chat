#ifndef SETTINGS_H
#define SETTINGS_H

#include "protocol.h"
#include "view_tools.h"
#include "libmx.h"
#include "resources.h"

void edit_info_on_button(GtkWidget *button, const char *title);
// void view_edit_window_on_button(t_current_window_info *current_layout_info);
void set_settings_on_button(GtkWidget *button);

#endif
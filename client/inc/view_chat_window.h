#ifndef VIEW_CHAT_WINDOW_H
#define VIEW_CHAT_WINDOW_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "drawing_area.h"
#include "view_tools.h"
#include "model_message.h"
#include "quiz.h"
#include "resources.h"

void view_chat_window(t_current_window_info *current_layout_info);

void view_message(t_model_message** model_message, t_current_window_info *current_layout_info, int size);

#endif

#ifndef CHOOSE_CHAT_H
#define CHOOSE_CHAT_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "drawing_area.h"
#include "view_tools.h"
#include "quiz.h"
#include "user_info.h"
#include "resources.h"
#include "view_chat_window.h"
#include "controller_start_chat.h"
#include "controller_get_messages.h"
#include "get_resources_request.h"
#include "user_data_request.h"


void	choose_chat(GtkButton *b, t_current_window_info *current_window_info);

#endif
#ifndef CONTROLLER_MESSAGE_ACTIONS
#define CONTROLLER_MESSAGE_ACTIONS

#include <gtk/gtk.h>
#include "model_message.h"
#include "model_resource.h"
#include "database_client.h"

void callback_click_message(GtkWidget *b, GdkEventButton *event,  t_model_message* model_message);
void set_selected_message(long id);
long get_selected_message();

#endif

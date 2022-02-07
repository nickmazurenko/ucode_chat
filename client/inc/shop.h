#ifndef SHOP_H
#define SHOP_H

#include "protocol.h"
#include "view_tools.h"
#include "libmx.h"
#include "resources.h"
#include "user_data_request.h"
#include "user_data.h"
#include "model_user_data.h"
#include "model_store.h"

void set_shop_on_button(GtkWidget *button);
void money_view(GtkWidget *widget, GtkWidget *builder);

#endif

#include "controller.h"
#include "view.h"
#include "resources.h"
#include "set_avatar_request.h"
#include "send_file.h"
#include "get_file.h"

#include "user_data.h"

//temp
#include "drawing_area.h"

#include "controller_send_message.h"



int main(int argc, char*argv[]) {

    gtk_init(&argc, &argv);
    GtkBuilder* main_window_builder = gtk_builder_new_from_file(get_path_to_glade("main_window.glade"));
    // gtk_builder_add_from_file(main_window_builder, get_path_to_glade("main_window.glade"), NULL);
    
    GtkWidget *new_window = GTK_WIDGET(gtk_builder_get_object(main_window_builder, "main_window"));
    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("sign.css"), NULL);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                              GTK_STYLE_PROVIDER(cssProvider),
                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    t_current_window_info *sign_in_layout_info = NULL;
    
    sign_in_layout_info = create_current_window_info();
    sign_in_layout_info->main_window = new_window;
    sign_in_layout_info->builder = main_window_builder;
    view_sign_in(sign_in_layout_info);
    gtk_widget_show(new_window);
    gtk_main();

    // generate_cookies();
    // cJSON_DeleteItemFromObject(get_cookies(), "USERNAME");
    // add_to_protocol_string(get_cookies(), "USERNAME", "r");

    // cJSON_DeleteItemFromObject(get_cookies(), "TOKEN");
    // add_to_protocol_string(get_cookies(), "TOKEN", "r");

    // controller_send_message("t", MESSAGE_TEXT, "hello6");

}

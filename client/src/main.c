#include "controller.h"
#include "view.h"
#include "resources.h"
#include "set_avatar_request.h"
#include "send_file.h"
#include "get_file.h"

//temp
#include "drawing_area.h"

int main(int argc, char*argv[]) {

    gtk_init(&argc, &argv);
    GtkBuilder* main_window_builder = gtk_builder_new();
    gtk_builder_add_from_file(main_window_builder, get_path_to_glade("main_window.glade"), NULL);
    
    GtkWindow *new_window = GTK_WINDOW(gtk_builder_get_object(main_window_builder, "main_window"));
    
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("sign.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                              GTK_STYLE_PROVIDER(cssProvider),
                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    t_current_window_info *sign_in_layout_info = NULL;
    
    sign_in_layout_info = create_current_window_info();
    sign_in_layout_info->main_window = GTK_WIDGET(new_window);
    view_sign_in(sign_in_layout_info);
    // add_draw_area(sign_in_layout_info);
	// GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(sign_in_layout_info->builder, "draw"));
    // gtk_widget_set_events(draw_area, GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);



    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();
}

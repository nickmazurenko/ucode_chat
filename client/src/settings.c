#include "settings.h"

void edit_info_on_button(GtkWidget *button, const gchar *title) {
    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("settings.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
                                            
    GtkWidget *user_info_popover;
    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("edit_info.glade"));
    GtkWidget *user_info_layout = GTK_WIDGET(gtk_builder_get_object(builder, "edit_info_layout"));
    GtkLabel *edit_title = GTK_LABEL( gtk_builder_get_object(builder, "edit_title"));
    gtk_label_set_text(GTK_LABEL(edit_title), title);
    
    user_info_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (user_info_popover), user_info_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), user_info_popover);
    gtk_popover_set_position(GTK_POPOVER(user_info_popover), GTK_POS_RIGHT);
}

void set_setting_on_button(GtkWidget *button, t_current_window_info *current_layout_info) {

    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("settings.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *settings_popover;
    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("settings.glade"));
    GtkWidget *settings_layout = GTK_WIDGET(gtk_builder_get_object(builder, "settings_layout"));
    
    settings_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (settings_popover), settings_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), settings_popover);
    gtk_popover_set_position(GTK_POPOVER(settings_popover), GTK_POS_RIGHT);
    GtkWidget *set_new_photo = GTK_BUTTON(gtk_builder_get_object(builder, "set_new_photo"));
    GtkWidget *edit_name = GTK_BUTTON(gtk_builder_get_object(builder, "edit_name"));
    GtkWidget *edit_personal_info = GTK_BUTTON(gtk_builder_get_object(builder, "edit_personal_info"));
    GtkWidget *edit_phone_number = GTK_BUTTON(gtk_builder_get_object(builder, "edit_phone_number"));
    GtkWidget *edit_email = GTK_BUTTON(gtk_builder_get_object(builder, "edit_email"));
    GtkWidget *log_out = GTK_BUTTON(gtk_builder_get_object(builder, "log_out"));

    // g_signal_connect(edit_name, "clicked", view_edit_window_on_button, current_layout_info);

    // g_signal_connect(edit_name, "clicked", G_CALLBACK(edit_name), builder);

    edit_info_on_button(edit_name, gtk_button_get_label(edit_name));
    edit_info_on_button(edit_personal_info, gtk_button_get_label(edit_personal_info));
    edit_info_on_button(edit_phone_number, gtk_button_get_label(edit_phone_number));
    edit_info_on_button(edit_email, gtk_button_get_label(edit_email));

}

// void edit_name(GtkWidget* widget, GtkBuilder *builder) {
    
// }

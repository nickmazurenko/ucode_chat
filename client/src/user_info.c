#include "user_info.h"


void set_user_info_on_button(GtkWidget *button) {


    GtkWidget *user_info_popover;
    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("user_info.glade"));
    GtkWidget *user_info_layout = GTK_WIDGET(gtk_builder_get_object(builder, "user_info_layout"));
    
    user_info_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (user_info_popover), user_info_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), user_info_popover);
    gtk_popover_set_position(user_info_popover, GTK_POS_RIGHT);
    // gtk_widget_show_all (user_info_popover); TODO: mojet delete ?

    GtkLabel *status_info = GTK_LABEL( gtk_builder_get_object(builder, "status_info"));
    GtkLabel *phone_info = GTK_LABEL( gtk_builder_get_object(builder, "phone_info"));
    GtkLabel *mail_info = GTK_LABEL( gtk_builder_get_object(builder, "mail_info"));
    GtkLabel *era_info = GTK_LABEL( gtk_builder_get_object(builder, "era_info"));
    GtkLabel *level_info = GTK_LABEL( gtk_builder_get_object(builder, "level_info"));



    gtk_label_set_text(status_info, "info form database");
    gtk_label_set_text(phone_info, "info form database");
    gtk_label_set_text(mail_info, "info form database");
    gtk_label_set_text(era_info, "info form database");
    gtk_label_set_text(level_info, "info form database");

}

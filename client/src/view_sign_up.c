#include "view_sign_up.h"

void sign_up_clicked(GtkWidget *widget, GtkEntry** fields) {

    gchar* username = gtk_entry_get_text(fields[0]);
    gchar* password = gtk_entry_get_text(fields[1]);  

    controller_sign_up(username, password);
}

void view_sign_up(GtkWidget* window) {

    gtk_window_set_title(GTK_WINDOW(window) ,"Sign Up");

    GtkWidget* username_text_field;
    GtkWidget* password_text_field;

    GtkWidget* fixed_container = gtk_fixed_new();

    GtkWidget* username_label = gtk_label_new("Nickname");
    GtkWidget* password_label = gtk_label_new("Password");

    username_text_field = gtk_entry_new();
    gtk_widget_set_size_request(username_text_field, 50, 40);
    password_text_field = gtk_entry_new();
    gtk_widget_set_size_request(password_text_field, 50, 40);

    GtkEntry** text_fields = (GtkEntry**)malloc(sizeof(GtkEntry*));
    text_fields[0] = username_text_field;
    text_fields[1] = password_text_field;

    GtkWidget* sign_up_button = gtk_button_new_with_label("Sign Up");

    g_signal_connect(G_OBJECT(sign_up_button), "clicked", G_CALLBACK(sign_up_clicked), text_fields);

    gtk_fixed_put(GTK_FIXED(fixed_container), username_label, 100, 60);
    gtk_fixed_put(GTK_FIXED(fixed_container), password_label, 100, 160);
    gtk_fixed_put(GTK_FIXED(fixed_container), username_text_field, 200, 50);
    gtk_fixed_put(GTK_FIXED(fixed_container), password_text_field, 200, 150);
    gtk_fixed_put(GTK_FIXED(fixed_container), sign_up_button, 200, 275);

    gtk_container_add(window, fixed_container);


    gtk_widget_show_all(window);
}
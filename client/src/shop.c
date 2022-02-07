#include "shop.h"


void set_shop_on_button(GtkWidget *button) {
    send_set_user_era_request("a", "a", 0);

    GtkCssProvider *cssProvider = gtk_css_provider_new(); 

    t_model_user_data* model_user_data = send_user_data_request(get_from_protocol_string(get_cookies(), "USERNAME"));
    t_model_store** model_store = send_store_request(model_user_data->era);

    GtkBuilder *builder;
    if (model_user_data->era == 0) {
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("stone_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_stone_age.glade"));
    }
    else if (model_user_data->era == 1) {
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("egypt_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_egypt.glade"));
    }
    else if (model_user_data->era == 2) {
        model_user_data->era = 3;
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("enlightment_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_enlightment.glade"));
    }
    else if (model_user_data->era == 3) {
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("enlightment_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_enlightment.glade"));
    }
    // else if (model_user_data->era == 4) {
        // gtk_css_provider_load_from_path(cssProvider, get_path_to_style("shop.css"), NULL);
    //     builder = gtk_builder_new_from_file(get_path_to_glade("shop.glade"));
    //     // only one item
    // }
    // GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("shop.glade"));

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *shop_popover;

    GtkWidget *shop_layout = GTK_WIDGET(gtk_builder_get_object(builder, "shop_layout"));

   
    shop_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (shop_popover), shop_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), shop_popover);
    gtk_popover_set_position(GTK_POPOVER(shop_popover), GTK_POS_RIGHT);

    GtkBuilder *builder_explanation = gtk_builder_new_from_file(get_path_to_glade("shop_explanation.glade"));
    GtkWidget *shop_layout_explanation = GTK_WIDGET(gtk_builder_get_object(builder_explanation, "shop_explanation_layout"));
    GtkWidget *explanation_button = GTK_WIDGET(gtk_builder_get_object(builder, "explanation_button"));

    GtkWidget *shop_item1 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item1"));
    GtkWidget *shop_item2 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item2"));
    GtkWidget *shop_item3 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item3"));
    GtkWidget *shop_item4 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item4"));
    GtkWidget *shop_item5 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item5"));
    GtkWidget *shop_item6 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item6"));

    printf("\n\n THERE \n\n");

    for (int i = 0; i < 6; i++) {
    printf("\n\n %s \n\n", model_store[i]->path); }

    GdkPixbuf *image_pixbuf1 = gdk_pixbuf_new_from_file_at_size(model_store[0]->path, -1, -1, NULL);
    GtkWidget *image_shop_item1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item1), image_pixbuf1);
    gtk_button_set_image(shop_item1, image_shop_item1);

    GdkPixbuf *image_pixbuf2 = gdk_pixbuf_new_from_file_at_size(model_store[1]->path, -1, -1, NULL);
    GtkWidget *image_shop_item2 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item2), image_pixbuf2);
    gtk_button_set_image(shop_item2, image_shop_item2);

    GdkPixbuf *image_pixbuf3 = gdk_pixbuf_new_from_file_at_size(model_store[2]->path, -1, -1, NULL);
    GtkWidget *image_shop_item3 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item3), image_pixbuf3);
    gtk_button_set_image(shop_item3, image_shop_item3);

    GdkPixbuf *image_pixbuf4 = gdk_pixbuf_new_from_file_at_size(model_store[3]->path, -1, -1, NULL);
    GtkWidget *image_shop_item4 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item4), image_pixbuf4);
    gtk_button_set_image(shop_item4, image_shop_item4);

    GdkPixbuf *image_pixbuf5 = gdk_pixbuf_new_from_file_at_size(model_store[4]->path, -1, -1, NULL);
    GtkWidget *image_shop_item5 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item5), image_pixbuf5);
    gtk_button_set_image(shop_item5, image_shop_item5);

    GdkPixbuf *image_pixbuf6 = gdk_pixbuf_new_from_file_at_size(model_store[5]->path, -1, -1, NULL);
    GtkWidget *image_shop_item6 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item6), image_pixbuf6);
    gtk_button_set_image(shop_item6, image_shop_item6);




    GtkWidget* shop_popover_explanation = gtk_popover_new (explanation_button);
    gtk_container_add (GTK_CONTAINER (shop_popover_explanation), shop_layout_explanation);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (explanation_button), shop_popover_explanation);
    gtk_popover_set_position(GTK_POPOVER(shop_popover_explanation), GTK_POS_RIGHT);

    g_signal_connect(button, "clicked", G_CALLBACK(money_view), builder);

    // g_signal_connect(shop_item1, "clicked", G_CALLBACK(buy_item), model_user_data);
    // g_signal_connect(shop_item2, "clicked", G_CALLBACK(buy_item), model_user_data);
    // g_signal_connect(shop_item3, "clicked", G_CALLBACK(buy_item), model_user_data);
    // g_signal_connect(shop_item4, "clicked", G_CALLBACK(buy_item), model_user_data);
    // g_signal_connect(shop_item5, "clicked", G_CALLBACK(buy_item), model_user_data);
    // g_signal_connect(shop_item6, "clicked", G_CALLBACK(buy_item), model_user_data);

}

void money_view(GtkWidget *widget, GtkWidget *builder) {
    GtkLabel *money_label = GTK_LABEL(gtk_builder_get_object(builder, "money_label"));
    gtk_label_set_text(money_label, mx_itoa(send_money_request_by_username(get_from_protocol_string(get_cookies(), "USERNAME"))));
}

// void buy_item(GtkWidget *widget, t_model_user_data* model_user_data) {
    // if (model_user_data->id == 1) {
    //     // change era 
    //     send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 2);
    // }

    // if (model_user_data->id == 2) {
    //     // clear stone
    // }

    // if (model_user_data->id == 3) {
    //     // change rock
    // }

    // if (model_user_data->id == 4) {
    //     // change rock
    // }

    // if (model_user_data->id == 5) {
    //     // change rock
    // }

    // if (model_user_data->id == 6) {
    //     // change rock
    // }

    // if (model_user_data->id == 7) {
    //     // change era 
    //     send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 4);
    // }

    // //8-12 add words

    // if (model_user_data->id == 19) {
    //     // change era 
    //     send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 5);
    // }

    // if (model_user_data->id == 20) {
    //     // unlock sending files
    // }

    // if (model_user_data->id == 21) {
    //     // educate
    // }

    // if (model_user_data->id == 22) {
    //     // change background
    //     // add new function
    // }

    // if (model_user_data->id == 23) {
    //     // change background
    // }

    // if (model_user_data->id == 24) {
    //     // change background
    // }

    // if (model_user_data->id == 25) {
    //     // change era, gift
    //     send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 0);
    // }
// }

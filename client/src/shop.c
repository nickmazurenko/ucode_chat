#include "shop.h"

void set_shop_on_button(GtkWidget *button) {
    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("shop.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *shop_popover;
    // GtkWidget *shop_popover_explanation;
    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("shop.glade"));
    GtkWidget *shop_layout = GTK_WIDGET(gtk_builder_get_object(builder, "shop_layout"));
    
    shop_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (shop_popover), shop_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), shop_popover);
    gtk_popover_set_position(GTK_POPOVER(shop_popover), GTK_POS_RIGHT);

    // GtkBuilder *builder_explanation = gtk_builder_new_from_file(get_path_to_glade("shop_explanation.glade"));
    // GtkWidget *shop_layout_explanation = GTK_WIDGET(gtk_builder_get_object(builder, "shop_explanation_layout"));
    // GtkWidget *explanation_button = GTK_WIDGET(gtk_builder_get_object(builder, "explanation_button"));

    // shop_popover_explanation = gtk_popover_new (explanation_button);
    // gtk_container_add (GTK_CONTAINER (shop_popover_explanation), shop_layout_explanation);
    // gtk_menu_button_set_popover (GTK_MENU_BUTTON (explanation_button), shop_popover_explanation);
    // gtk_popover_set_position(GTK_POPOVER(shop_popover_explanation), GTK_POS_RIGHT);

}

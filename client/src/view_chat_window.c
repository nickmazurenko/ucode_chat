#include "view_chat_window.h"
    
void view_chat_window(t_current_window_info *current_layout_info)
{

    // add css for  messages 

    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("messages.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    t_model_message** model_message = (t_model_message**)malloc(sizeof(t_model_message*) * 5);

    char tmp[1024];
    int row = 0;
    
    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));
    if (current_layout_info->layout_exists)
    {
        gtk_widget_destroy(GTK_WIDGET(sign_in_layout));
    }
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("chat_window.glade"), NULL);///////rename --> done

    GtkLayout *home_page_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "home_page_layout"));

    GtkLayout *chat_window_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "chat_window_layout"));///rename --> done

    GtkWidget *chat_window_fixed = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_fixed"));

    GtkWidget *chat_window_viewport = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_viewport"));

    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid"));

    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(home_page_layout));//ya huy znaet kakoy layout ebanut` zdes`

    gtk_container_add(GTK_CONTAINER(home_page_layout), GTK_WIDGET(chat_window_layout));

    current_layout_info->layout_exists = true;

	    row = 0;
        gtk_grid_insert_column (GTK_GRID(chat_window_grid), 0);
        gtk_grid_insert_column (GTK_GRID(chat_window_grid), 1);

        model_message[0] = new_model_message();
        model_message[0]->from_user = 1;
        mx_strcpy(model_message[0]->data, "LOH LOH LOH");

        model_message[1] = new_model_message();
        model_message[1]->to_user = 1;
        mx_strcpy(model_message[1]->data, "HUY HUY HUY");
        
        model_message[2] = new_model_message();
        model_message[2]->to_user = 1;
        mx_strcpy(model_message[2]->data, "JOPA JOPA");

        model_message[3] = new_model_message();
        model_message[3]->from_user = 1;
        mx_strcpy(model_message[3]->data, "HUY JOPA LOH");

        model_message[4] = new_model_message();
        model_message[4]->to_user = 1;
        mx_strcpy(model_message[4]->data, "PIZDEC");

        view_message(model_message, current_layout_info, 5);

        
        gtk_widget_show_all(current_layout_info->main_window);

}



void view_message(t_model_message** model_message, t_current_window_info *current_layout_info, int size){
    GtkWidget *label[size];
    GtkWidget *chat_window_grid = GTK_WIDGET(gtk_builder_get_object(current_layout_info->builder, "chat_window_grid"));


    
    for(int i = 0; i < size; i++) {
        GtkWidget *message_builder = gtk_builder_new_from_file(get_path_to_glade ("message_labels.glade"));

         gtk_grid_insert_row (GTK_GRID(chat_window_grid), i);

        if(model_message[i]->from_user == 1){
        

        label[i] = GTK_WIDGET(gtk_builder_get_object(message_builder, "current_user_msg_label"));

        gtk_label_set_text(GTK_LABEL(label[i]), model_message[i]->data);


        gtk_label_set_xalign (GTK_LABEL(label[i]), 0.5);
        gtk_label_set_justify (GTK_LABEL(label[i]), GTK_JUSTIFY_RIGHT);// mb GTK_JUSTIFY_LEFT
        gtk_grid_attach (GTK_GRID(chat_window_grid), label[i], 1, i, 1, 1);
        
        } 
        
        else if(model_message[i]->to_user == 1) { //// !!!!!!!!!!!!!! mb prosto else sdelat`, huy znaet
        

        label[i] = GTK_WIDGET(gtk_builder_get_object(message_builder, "other_user_msg_label"));
        gtk_label_set_text(GTK_LABEL(label[i]), model_message[i]->data);

        gtk_label_set_xalign (GTK_LABEL(label[i]), 0.5);
        gtk_label_set_justify (GTK_LABEL(label[i]), GTK_JUSTIFY_LEFT);
        gtk_grid_attach (GTK_GRID(chat_window_grid), label[i], 0, i, 1, 1);
        
        }

    }
    
}


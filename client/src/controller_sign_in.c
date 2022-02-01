#include "controller_sign_in.h"

int controller_sign_in(char* user_name, char* password) {

    t_model_user* user = new_model_user(user_name, password);
    int exit_status;
    if(send_sign_in_request(user)){
        exit_status = 0;
    }else {
        exit_status = 1;
    }
    free_model_user(&user);
    return exit_status;
}

void controller_view_user_era(GtkWidget **sign_in_info, t_current_window_info *current_window_info) {

    generate_cookies((char *)gtk_entry_get_text(sign_in_info[0]), (char *)gtk_entry_get_text(sign_in_info[1]));

    controller_get_messages();

    // change window to second era
    // view_second_era(current_window_info);

    // change window to text chat era
    view_home_page(current_window_info);

}


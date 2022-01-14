#include "controller_sign_up.h"

bool is_new_user(char* user_name) {
    return true;
}

void controller_sign_up(char* user_name, char* password) {

    if (is_new_user(user_name)) {

        t_model_user* user = new_model_user(user_name, password);
        send_sign_up_request(user);
        free_model_user(&user);
    }

}
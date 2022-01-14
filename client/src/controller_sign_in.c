#include "controller_sign_in.h"

void controller_sign_in(char* user_name, char* password) {

    t_model_user* user = new_model_user(user_name, password);
    send_sign_in_request(user);
    free_model_user(&user);

}
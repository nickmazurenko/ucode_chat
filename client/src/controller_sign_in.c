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
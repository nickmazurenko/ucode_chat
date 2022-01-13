#include "model_msg.h"

t_model_msg* new_model_msg() {

    t_model_msg* model_msg = (t_model_msg*)malloc(sizeof(t_model_msg));

    model_msg->id = 0;
    model_msg->from = -1;
    model_msg->to   = -1;
    model_msg->chat_id = -1;
    model_msg->date = NULL;
    model_msg->data = NULL;

    return model_msg;
}
char*        to_string_model_msg(t_model_msg* model_msg) {

    char* id  = mx_itoa(model_msg->id);
    char* from = mx_itoa(model_msg->from);
    char* to   = mx_itoa(model_msg->to);
    char* chat_id = mx_itoa(model_msg->chat_id);
    char* date    = mx_strdup(model_msg->date);
    t_model_data* data    = mx_strnew(model_msg->data);
    char* data_str = to_string_model_data(data);

    long index = 0;


}

t_model_msg* from_string_model_msg(char* string);
void         free_model_msg(t_model_msg** model_msg);

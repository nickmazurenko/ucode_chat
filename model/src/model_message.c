#include "model_message.h"

t_model_message* new_model_message() {

    t_model_message* model_message = (t_model_message*)malloc(sizeof(t_model_message));
    model_message->id        = 0;
    model_message->from_user = 0;
    model_message->to_user   = 0;
    model_message->data_type = MESSAGE_TEXT;
    model_message->data      = mx_strnew(BUFFER_SIZE);
    model_message->date      = mx_strnew(1024);
    model_message->status    = MESSAGE_SENDED;

    return model_message;
}

char*         to_string_model_message(t_model_message* model_message) {

    cJSON* message = cJSON_CreateObject();

    add_to_protocol_number(message, "id", model_message->id);
    add_to_protocol_number(message, "from_user", model_message->from_user);
    add_to_protocol_number(message, "to_user", model_message->to_user);
    add_to_protocol_number(message, "data_type", model_message->data_type);
    add_to_protocol_string(message, "data", model_message->data);
    add_to_protocol_string(message, "date", model_message->date);
    add_to_protocol_number(message, "status", model_message->status);

    char* message_str = cJSON_Print(message);

    cJSON_Delete(message);
    return message_str;
}

t_model_message* from_string_model_message(char* json) {

    cJSON* message = cJSON_Parse(json);

    t_model_message* model_message = new_model_message();

    model_message->id = get_from_protocol_number(message, "id");
    model_message->from_user = get_from_protocol_number(message, "from_user");
    model_message->to_user = get_from_protocol_number(message, "to_user");
    model_message->data_type = (int)get_from_protocol_number(message, "data_type");
    model_message->status    = (int)get_from_protocol_number(message, "status");

    char* data = get_from_protocol_string(message, "data");
    char* date = get_from_protocol_string(message, "date");

    strcpy(model_message->data, data);
    strcpy(model_message->date, date);


    cJSON_Delete(message);

    return model_message;
}
void          free_model_message(t_model_message** model_message) {

    free((*model_message)->data);
    free(*model_message);

    *model_message = NULL;

}

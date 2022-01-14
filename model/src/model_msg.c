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
    char* data = to_string_model_data(model_msg->data);
    
    long index = 0;
    char* string = mx_strnew(STR_SIZE + model_msg->data->size);

    int length = strlen(id);
    memcpy(string, id, length);
    index += length;
    memcpy(string + index++, ";", 1);

    length = strlen(from);
    memcpy(string + index, from, length);
    index += length;
    memcpy(string + index++, ";", 1);

    length = strlen(to);
    memcpy(string + index, to, length);
    index += length;
    memcpy(string + index++, ";", 1);

    length = strlen(chat_id);
    memcpy(string + index, chat_id, length);
    index += length;
    memcpy(string + index++, ";", 1);

    length = strlen(date);
    memcpy(string + index, date, length);
    index += length;
    memcpy(string + index++, ";", 1);

    long model_data_length = model_data_string_length(data);
    if (index + model_data_length > STR_SIZE + model_msg->data->size) {
        string = realloc(string, index + model_data_length + 1);
    }

    memcpy(string + index, data, model_data_length);
    index += model_data_length;
    memcpy(string + index++, ";", 1);

    free(id);
    free(from);
    free(to);
    free(chat_id);
    free(date);
    free(data);

    return string;
}

t_model_msg* from_string_model_msg(char* string) {

    char* buff = mx_strnew(STR_SIZE);
    int count_of_delimeter = 0;
    t_model_msg* model_msg = new_model_msg();
    long buff_index = 0;
    long str_index = 0;

    for ( ; count_of_delimeter != 1; str_index++ ) {
        if (string[str_index] == ';') count_of_delimeter++;
        else buff[buff_index++] = string[str_index];
    }

    model_msg->id = atol(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;

    for ( ; count_of_delimeter != 2; str_index++ ) {
        if (string[str_index] == ';') count_of_delimeter++;
        else buff[buff_index++] = string[str_index];
    }

    model_msg->from = atol(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;


    for ( ; count_of_delimeter != 3; str_index++ ) {
        if (string[str_index] == ';') count_of_delimeter++;
        else buff[buff_index++] = string[str_index];
    }

    model_msg->to = atol(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;

    for ( ; count_of_delimeter != 4; str_index++ ) {
        if (string[str_index] == ';') count_of_delimeter++;
        else buff[buff_index++] = string[str_index];
    }

    model_msg->chat_id = atol(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;

    for ( ; count_of_delimeter != 5; str_index++ ) {
        if (string[str_index] == ';') count_of_delimeter++;
        else buff[buff_index++] = string[str_index];
    }

    model_msg->date = mx_strdup(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;

    model_msg->data = from_string_model_data(string + str_index);

    free(buff);
    return model_msg;
}
void         free_model_msg(t_model_msg** model_msg) {

    free((*model_msg)->date);
    free_model_data(&(*model_msg)->data);;

    free(*model_msg);
    *model_msg = NULL;

}

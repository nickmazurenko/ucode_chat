#include "model_data.h"

t_model_data* new_model_data(e_model_data_types type, long size, char* string) {

    t_model_data* model_data = (t_model_data*)malloc(sizeof(t_model_data));
    model_data->id = 0;
    model_data->type = type;
    model_data->size = size;

    if ( size >= 0 ) {
        model_data->string = mx_strnew(model_data->size);
        memcpy(model_data->string, string, size);
    } else {
        if (string != NULL) {
                model_data->string = mx_strnew(mx_strlen(string));
                strcpy(model_data->string, string);
        } else {
            model_data->string = mx_strnew(0);
        }
    }
    
    return model_data;
}

char*   to_string_model_data(t_model_data* data) {

    char* type = mx_itoa(data->type);
    long  type_len = mx_strlen(type);
    char* id   = mx_itoa(data->id);
    long  id_len   = mx_strlen(id);
    char* size = mx_itoa(data->size);
    long  size_len = mx_strlen(size);

    long index = 0;

    long current_size = STR_SIZE;
    char* string = mx_strnew(current_size);

    memcpy(string, type, type_len);
    index = type_len;

    memcpy(string + index, id, id_len);
    index += id_len;
    memcpy(string + index++, ";", 1);

    memcpy(string + index, size, size_len);
    index += size_len;
    memcpy(string + index++, ";", 1);

    long int_size = data->size;
    if (int_size < 0) int_size = mx_strlen(data->string);
    
    memcpy(string + index, data->string, int_size);
    index += int_size;

    free(type);
    free(id);
    free(size);

    return string;
}

t_model_data*   from_string_model_data(char* string) {

    // type
    // id
    // size

    if (string == NULL) return NULL;
    if (string[0] == '\0') return NULL;

    long str_index = 0;
    char* buff = mx_strnew(STR_SIZE);
    long buff_index = 0;
    for ( ; string[str_index] != ';'; str_index++) {
        buff[buff_index] = string[str_index];
        buff_index++;
    }
    int type = atoi(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;

    for (;string[str_index] != ';'; str_index++) {
        buff[buff_index] = string[str_index];
        buff_index++;
    }
    long id = atol(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;

    for (;string[str_index] != ';'; str_index++) {
        buff[buff_index] = string[str_index];
        buff_index++;
    }
    long size = atol(buff);
    memset(buff, '\0', buff_index);
    buff_index = 0;
    str_index++;

    char* str = mx_strnew(size);
    memcpy(str, string + str_index, size);

    t_model_data* model_data = new_model_data(type, size, str);
    model_data->id = id;

    free(str);
    free(buff);

    return model_data;
}

void free_model_data(t_model_data** data) {

    free((*data)->string);
    free(*data);

    *data = NULL;

}

long model_data_string_length(char* model_data_str) {

    if (model_data_str == NULL) return 0;

    t_model_data* model_data = from_string_model_data(model_data_str);
    long length = 0;
    int count_of_delimeter = 0;

    for (long str_index = 0; count_of_delimeter != 2; str_index++) {
        if (model_data_str[str_index] != ';') length++;
        else count_of_delimeter++;
    }

    free_model_data(&model_data);
    
    return length + model_data->size + 3;
}

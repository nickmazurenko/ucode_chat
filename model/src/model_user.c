#include "model_user.h"

t_model_user* new_model_user(char* name, char* password) {

    t_model_user* model_user = (t_model_user*)malloc(sizeof(t_model_user));
    model_user->id = 0;
    model_user->name = mx_strdup(name);
    model_user->password = mx_strdup(password);

    return model_user;
}

char*         to_string_model_user(t_model_user* model_user) {

    char* string = NULL;
    char* buff = mx_itoa(model_user->id);

    string = mx_strjoin(string, buff);
    free(buff);
    buff = string;

    string = mx_strjoin(string, ";");
    free(buff);
    buff = string;

    string = mx_strjoin(string, model_user->name);
    free(buff);
    buff = string;

    string = mx_strjoin(string, ";");
    free(buff);
    buff = string;

    string = mx_strjoin(string, model_user->password);
    free(buff);
    buff = string;

    string = mx_strjoin(string, ";");
    free(buff);

    return string;
}

t_model_user* from_string_model_user(char* string) {

    char* buff = mx_strnew(256);
    
    t_model_user* model_user = new_model_user("", "");
    int index = mx_get_char_index(string, ';');

    if (index < 0) {
        mx_strdel(&buff);
        return NULL;
    }

    int last_index = index;
    mx_strncpy(buff, string, index);
    model_user->id = atol(buff);
    memset(buff, '\0', index);

    index = mx_get_char_index(string + last_index + 1, ';');
    if (index < 0) {
        mx_strdel(&buff);
        free_model_user(&model_user);
        return NULL;
    }

    mx_strncpy(buff, string + last_index + 1, index);
    free(model_user->name);
    model_user->name = mx_strdup(buff);
    memset(buff, '\0', index);
    
    last_index = last_index + 1 + index;
    index = mx_get_char_index(string + last_index + 1, ';');
    if (index < 0) {
        mx_strdel(&buff);
        free_model_user(&model_user);
        return NULL;
    }

    mx_strncpy(buff, string + last_index + 1, index);
    free(model_user->password);
    model_user->password = mx_strdup(buff);


    mx_strdel(&buff);
    return model_user;
}

void          free_model_user(t_model_user** model_user) {

    free((*model_user)->name);
    free((*model_user)->password);
    free(*model_user);
    *model_user = NULL;
}

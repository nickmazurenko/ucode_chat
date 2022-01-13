#ifndef MODEL_MSG_H
#define MODEL_MSG_H

#include "libmx.h"
#include "model_data.h"

typedef struct s_model_msg {

    size_t id;
    long   chat_id;
    size_t from;
    size_t to;
    char*  date;
    t_model_data* data;

}              t_model_msg;

t_model_msg* new_model_msg();
char*        to_string_model_msg(t_model_msg* model_msg);
t_model_msg* from_string_model_msg(char* string);
void         free_model_msg(t_model_msg** model_msg);

#endif

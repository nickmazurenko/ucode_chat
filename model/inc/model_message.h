#ifndef MODEL_MESSAGE_H
#define MODEL_MESSAGE_H

#include "libmx.h"
#include "protocol.h"
#include "string.h"
#include "stdlib.h"

typedef enum   message_data_types {

    MESSAGE_TEXT,
    MESSAGE_FILE,
    MESSAGE_STONE,
    NUMBER_OF_MESSAGE_TYPES

}             e_message_data_types;

typedef struct s_model_message {

    size_t               id;
    size_t               from_user;
    size_t               to_user;
    e_message_data_types data_type;
    char*                data;
}              t_model_message;

t_model_message* new_model_message();
char*         to_string_model_message(t_model_message*);
t_model_message* from_string_model_message(char*);
void          free_model_message(t_model_message**);

#endif

#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include "libmx.h"
#include <string.h>

typedef enum model_data_types {

    TEXT,
    FILE

}            e_model_data_types;

typedef struct s_model_data {

    size_t id; 
    e_model_data_types type;
    long         size;
    char*        string;

}             t_model_data;


t_model_data* new_model_data(e_model_data_types type, long size, char* string);
char*   to_string_model_data(t_model_data* data);
t_model_data* from_string_model_data(char* string);
t_model_data* free_model_data(t_model_data** data);

#endif

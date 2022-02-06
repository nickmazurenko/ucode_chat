#include "controller_get_messages.h"

void controller_get_messages(){
    init_tables();
    cJSON *current_user_messages  = get_all_my_messages(get_cookies());
    int count = cJSON_GetArraySize(current_user_messages);
    printf("\n\nCOUNT %i\n\n", count);
    for(int message_id = 0; message_id < count; message_id++) {
        insert_data_message(from_string_model_message(cJSON_GetArrayItem(current_user_messages, message_id)->valuestring));
    }
}

t_model_message** controller_get_new_messages(int* count) {

    cJSON *current_user_messages  = get_my_new_messages(get_cookies());
    *count = cJSON_GetArraySize(current_user_messages);

    t_model_message** model_messages = NULL;

    if (*count == 0) {
        printf("no new\n");
        fflush(stdout);
    } else {
        model_messages = (t_model_message**)malloc(sizeof(t_model_message*) * *count);
        for(int message_id = 0; message_id < *count; message_id++) {
            t_model_message* model_message = from_string_model_message(cJSON_GetArrayItem(current_user_messages, message_id)->valuestring);
            model_messages[message_id] = model_message;
            insert_data_message(model_message);
        }
    }
    cJSON_Delete(current_user_messages);
    return model_messages;
}



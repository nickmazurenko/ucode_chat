#include "controller_get_messages.h"


void controller_get_messages(){
    init_tables();
    cJSON *current_user_messages  = get_all_my_messages(get_cookies());
    int count = cJSON_GetArraySize(current_user_messages);

    for(int message_id = 0; message_id < count; message_id++) {
        insert_data_message(from_string_model_message(cJSON_GetArrayItem(current_user_messages, message_id)->valuestring));
    }
}



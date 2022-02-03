#include "controller_send_message.h"

//  int controller_send_message(char* to, e_message_data_types data_type, char* data) {

//     t_model_message* model_message = new_model_message();

//     cJSON* protocol = create_protocol();
//     add_to_protocol_string(protocol, "FROM", get_from_protocol_string(get_cookies(), "USERNAME"));
//     add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(get_cookies(), "TOKEN"));


//     strcpy(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"));
//     strcpy(model_message->to_user, to);
//     model_message->data_type = data_type;

//     strcpy(model_message->data, data);
    
//     printf("%s\n", to_string_model_message(model_message));
//     fflush(stdout);

//     char* response = send_message(model_message, protocol);

//     // TODO: in response get message id and add to db this message

//     return 0;
// }


 t_model_message *controller_send_message(char* to, e_message_data_types data_type, char* data) {

    if (to != NULL) {
        t_model_message* model_message = new_model_message();

        cJSON* protocol = create_protocol();
        add_to_protocol_string(protocol, "FROM", get_from_protocol_string(get_cookies(), "USERNAME"));
        add_to_protocol_string(protocol, "TOKEN", get_from_protocol_string(get_cookies(), "TOKEN"));


        strcpy(model_message->from_user, get_from_protocol_string(get_cookies(), "USERNAME"));
        strcpy(model_message->to_user, to);
        model_message->data_type = data_type;

        strcpy(model_message->data, data);
        
        // printf("%s\n", to_string_model_message(model_message));
        // fflush(stdout);

        char* response = send_message(model_message, protocol);

        // TODO: in response get message id and add to db this message --> done
        
        // change and check
        t_model_message * model_message_tmp = from_string_model_message(get_from_protocol_string(cJSON_Parse(response), "DATA"));


        insert_data_message(model_message_tmp);


        

        return model_message_tmp;
    }
    else
        return NULL;
    
}

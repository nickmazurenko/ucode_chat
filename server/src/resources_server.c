#include "resources_server.h"


char* add_resources(cJSON* request){

    // fprintf(stderr,"\n\nBEFORE REQUEST: %s\n\n", cJSON_Print(request));
    char *to_parse = get_from_protocol_string(request, "DATA");
    cJSON *data_from_request =  cJSON_Parse(to_parse);

    fprintf(stderr,"\n\nAFTER REQUEST: %s\n\n", cJSON_Print(data_from_request));

    char* username = get_from_protocol_string(data_from_request, "FROM");
    char* token    = get_from_protocol_string(data_from_request, "TOKEN");

    cJSON* response = create_protocol();
 
    if (is_verified_user(username, token)) {

        char* message_json = get_from_protocol_string(data_from_request, "DATA");
        t_model_message* model_message = from_string_model_message(message_json);
        strcpy(model_message->date, get_from_protocol_string(data_from_request, "DATE"));
        model_message->status = MESSAGE_SENT;

        t_model_resource *model_resource = new_model_resource();
        strcpy(model_resource->path, model_message->data);
        strcpy(model_resource->name, model_message->data);
        // int msg_id = insert_data_message(model_message);
        int resource_id = insert_data_resource(model_resource);
        model_message->id = resource_id;
        model_resource->id = resource_id;


        add_to_protocol_string(response, "DATA", to_string_model_resource(model_resource));

        free_model_message(&model_message);
        free_model_resource(&model_resource);
        
        
    } else {
        add_to_protocol_string(response, "DATA", "ERROR");
    }
    // fprintf(stderr, "\n\nTHERE\n\n");
    
    char* response_json = cJSON_Print(response);
    cJSON_Delete(response);

    return response_json;

}

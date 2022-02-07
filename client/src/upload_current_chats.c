#include "choose_chat.h"

void upload_chats(char *from_user, t_current_window_info *current_window_info) {
    int user_chats_count = 0; 
    char **user_chats = get_all_user_chats(get_from_protocol_string(get_cookies(), "USERNAME"), &user_chats_count); 
    
    for(int chat_index = 0; chat_index < user_chats_count; chat_index++) {
        if(!strcmp(user_chats[chat_index], from_user)) {
            return;
        }
    }
    add_chat(from_user, current_window_info);
}
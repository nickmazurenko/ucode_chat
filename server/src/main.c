#include "server.h"

int main() {

    // run_server();
    // init_tables();

    t_model_user* user = new_model_user("Hel", "World");
    insert_data_user(user->name, user->password);
}

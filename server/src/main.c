#include "server.h"

int main() {

    init_tables();
    run_server();

    // t_model_user* user = new_model_user("Hel", "World");
    // insert_data_user(user->name, user->password);
}

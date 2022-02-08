#include "server.h"
// #include "user_data_actions.h"

int main() {

    init_tables();
    // update_user_money("a", 500);
    run_server();

    // t_model_user* user = new_model_user("Hel", "World");
    // insert_data_user(user->name, user->password);
}

#include "resources.h"

char* get_path_to_resources() {

    size_t path_max = 1024;
    char* pwd = mx_strnew(path_max);

    if (getcwd(pwd, path_max)) {
        printf("getcwd is null in get path to resources\n");
        free(pwd);
        return NULL;
    };

    char* resources = NULL;
    if (pwd[strlen(pwd) - 1] == '/') {
        resources = "client/resources/";
    } else {
        resources = "/client/resources/";
    }

    resources = mx_strjoin(pwd, resources);
    free(pwd);
    return resources;
}

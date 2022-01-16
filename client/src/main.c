#include "controller.h"
#include "view.h"
#include "set_avatar_request.h"

int main(int argc, char*argv[]) {

    // GtkWidget* window;

    // gtk_init(&argc, &argv);

    // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // gtk_window_set_default_size(GTK_WINDOW(window), DEFAULT_WIDTH, DEFAULT_HEIGHT);
    // gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // // view_sign_up(window);
    // view_sign_in(window);

    // gtk_main();

    FILE* file_file = fopen("todo", "r");
    fseek(file_file, 0, SEEK_END);
    size_t file_size = ftell(file_file);
    fseek(file_file, 0, SEEK_SET);
    fclose(file_file);

    printf("file_size: %lu\n", (size_t)file_size);

    char* file_str = mx_strnew(file_size);

    int file = open("todo", O_RDONLY);
    read(file, file_str, file_size);
    close(file);

    send_set_avatar_request(file_str, file_size);
}

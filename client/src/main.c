#include "controller.h"
#include "view.h"
#include "set_avatar_request.h"
#include "send_file.h"

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

    // send_file("bigimage.jpeg", "OK", "127.0.0.1", 5000);
    send_set_avatar_request("bigimage.jpeg");
}

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "xqueue.h"
#include <gtk/gtk.h>

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void call_process(GtkWidget *widget, gpointer data)
{

}

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *quit_button = gtk_button_new_with_label("Quit");   
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    //g_signal_connect(GTK_OBJECT(quit_button), "clicked", G_CALLBACK(destroy),"quit_button"); 
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 
    gtk_container_add(GTK_CONTAINER(window), quit_button);
    gtk_widget_show_all(window);
   
    Xqueue * xqueue = new Xqueue();
    
    pid_t pid = fork();
    
    if(pid == 0)
    {
        xqueue->new_process("processes/n_factorial",2);
        xqueue->kill_process("processes/n_factorial");
    }
    else
    {
        wait();
        gtk_main();
    }

    return 0;
}

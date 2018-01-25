#include <unistd.h>
#include "process_queue.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>

void destroy(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Process_Queue *ip = (Process_Queue*) data;
        kill(ip->Child_Pid("processes/n_factorial"), SIGTERM);    
    }
    gtk_main_quit(); 
}

void start_process(GtkWidget *widget, gpointer data)
{
    if(data != NULL)
    {
    
    }
}

int main(int argc, char **argv)
{
    // create a process queue processes
    Process_Queue *ip = new Process_Queue();
    
    // load the built-in processes into the idle process queue
    // new_process(string Process_Path, int Nice)
    ip->new_process("processes/n_factorial", 2);
    ip->new_process("processes/n_fibonacci", 2);
    ip->new_process("processes/ascii_image", 7);
    ip->new_process("processes/crypto"); //default nice is 10
    ip->new_process("processes/echo", 4);
    ip->new_process("processes/n_countdown"); 
    
    // initialize necessary for X11 and GTK libraries
    XInitThreads();
    gtk_init(&argc, &argv);
    
    // create the GTK window and objects
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *quit_button = gtk_button_new_with_label("Quit"); 
    
    // connect actions to callback functions
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    g_signal_connect(GTK_OBJECT(quit_button), "clicked", G_CALLBACK(destroy), ip);
    
    // configure window
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 
    
    // add objects to window
    gtk_container_add(GTK_CONTAINER(window), quit_button);
    
    // one became two
    pid_t pid = fork();
    
    // child block
    if(pid == 0)
    {   
        execlp("processes/n_factorial","n_factorial", NULL);
    }
    // parent block
    else
    {
        // display the window
        ip->Child_Pid("processes/n_factorial", pid);
        gtk_widget_show_all(window);
        gtk_main();
    }
    
    delete(ip);
    
    return 0;
}

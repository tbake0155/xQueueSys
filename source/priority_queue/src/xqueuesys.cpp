#include <unistd.h>
#include "process_queue.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>

struct Callback_Data
{
    Process_Queue *pq;
    char *process_path; // a process that is being handled
};

void path_to_name()
{

}

void destroy(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->kill_all_processes("SIGTERM");    
    }
    gtk_main_quit(); 
}

void start_process(GtkWidget *widget, gpointer data)
{
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->run_process(cb->process_path);
    }
}

//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//
//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//
//~~//~~//~~//~~//~~//~~//~~// main //~~//~~//~~//~~//~~//~~//~~//
//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//
//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//~~//
int main(int argc, char **argv)
{
    // create a process queue processes
    Process_Queue *pq = new Process_Queue();
    
    // keep it together
    Callback_Data *cb_data = new Callback_Data();
    cb_data->pq = pq;
    cb_data->process_path = new char();
    
    // load the built-in processes into the idle process queue
    // new_process(string Process_Path, int Nice)
    pq->new_process("processes/n_factorial", 2);
    pq->new_process("processes/n_fibonacci", 2);
    pq->new_process("processes/ascii_image", 7);
    pq->new_process("processes/crypto"); //default nice is 10
    pq->new_process("processes/echo", 4);
    pq->new_process("processes/n_countdown"); 
    
    // initialize necessary for X11 and GTK libraries
    XInitThreads();
    gtk_init(&argc, &argv);
    
    // create the GTK window and objects
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *table = gtk_table_new (14, 5, TRUE);
    GtkWidget *quit_button = gtk_button_new_with_label("Quit"); 
    GtkWidget *scheduled_list = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *idle_list = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *gtklist;
    GtkWidget *list_item;
    GtkWidget *frame;
    GList *dlist;
    guint i;
    gchar buffer[64];
    
    // connect actions to callback functions
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    g_signal_connect(GTK_OBJECT(quit_button), "clicked", G_CALLBACK(destroy), cb_data);
    
    // configure window
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 
    gtk_window_resize(GTK_WINDOW(window), 800, 600);
    
    // add table to window
    gtk_container_add (GTK_CONTAINER (window), table);
    
    // attach widgets to table
    gtk_table_attach_defaults (GTK_TABLE(table), scheduled_list, 0, 2, 0, 8);
    gtk_table_attach_defaults (GTK_TABLE(table), idle_list, 3, 5, 0, 8);
    gtk_table_attach_defaults (GTK_TABLE(table), quit_button, 4, 5, 13, 14);

    // one became two
    pid_t pid = fork();
    
    // child block
    if(pid == 0)
    {     
        // listen for callbacks, react to them
        // and quit when told to quit  
        //while(pq->num_processes() > 0)
        //{
            pq->run_process("processes/n_factorial");
        //}
    }
    // parent block
    else
    {
        // display the window for xQueueSys
        // this will be GTK's thread only
        gtk_widget_show_all(window);
        gtk_main();
    }
    
    delete(pq);
    
    return 0;
}

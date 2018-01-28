#include <unistd.h>
#include "process_queue.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <thread>
#include <chrono>

struct Callback_Data
{
    Process_Queue *pq;
    GtkWidget *scheduled_list;
    GtkWidget *idle_list;
    GtkWidget *window;
};

void destroy(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->kill_all_processes("SIGTERM");    
    }
    gtk_main_quit(); 
}

static gboolean refresh_list(gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->add_processes_to_lists(cb->scheduled_list, cb->idle_list);   
        gtk_widget_show_all(cb->window);
    } 
}

void schedule(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        refresh_list(data);    
    }
}

void deschedule(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        refresh_list(data);    
    }
}

void block(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        refresh_list(data);    
    }
}

void pause_process(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        //TODO
    }
}

void stop_process(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        //TODO
    }
}

void stop_all_processes(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        //TODO
    }
}

void load_default_processes(Process_Queue *pq)
{
    // load the built-in processes into the idle process queue
    // new_process(string Process_Path, int Nice)
    pq->new_process("processes/n_factorial", 2);
    pq->new_process("processes/n_fibonacci", 2);
    pq->new_process("processes/ascii_image", 7);
    pq->new_process("processes/crypto"); //default nice is 10
    pq->new_process("processes/echo", 4);
    pq->new_process("processes/n_countdown"); 
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
    
    // load the built-in processes (if available)
    load_default_processes(pq);
    
    // initialize necessary for X11 and GTK libraries
    XInitThreads(); // prevents errors due to multithreading with windows
    gtk_init(&argc, &argv); 
    
    // create the GTK window and main table widget
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 
    gtk_window_resize(GTK_WINDOW(window), 800, 600);
    
    // will contain all other widget objects
    GtkWidget *table = gtk_table_new (14, 20, TRUE); 
    
    // create buttons
    GtkWidget *schedule_button = gtk_button_new_with_label("Schedule"); 
    GtkWidget *deschedule_button = gtk_button_new_with_label("Deschedule"); 
    GtkWidget *block_button = gtk_button_new_with_label("Block");
    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    GtkWidget *pause_button = gtk_button_new_with_label("Pause");
    GtkWidget *stop_button = gtk_button_new_with_label("Stop");
    GtkWidget *stop_all_button = gtk_button_new_with_label("Stop All");
            
    // create scrollable lists
    GtkWidget *scheduled_scrolled = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *idle_scrolled = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *scheduled_list = gtk_list_new();
    GtkWidget *idle_list = gtk_list_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scheduled_scrolled), scheduled_list);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(idle_scrolled), idle_list);

    // attach scrollable list to table
    gtk_table_attach_defaults (GTK_TABLE(table), idle_scrolled, 0, 8, 1, 9);
    gtk_table_attach_defaults (GTK_TABLE(table), scheduled_scrolled, 12, 20, 1, 9);
    
    // attach buttons 
    gtk_table_attach_defaults (GTK_TABLE(table), schedule_button, 9, 11, 2, 3);  
    gtk_table_attach_defaults (GTK_TABLE(table), deschedule_button, 9, 11, 4, 5); 
    gtk_table_attach_defaults (GTK_TABLE(table), block_button, 9, 11, 7, 8);
    gtk_table_attach_defaults (GTK_TABLE(table), pause_button, 12, 14, 9, 10); 
    gtk_table_attach_defaults (GTK_TABLE(table), stop_button, 15, 17, 9, 10);
    gtk_table_attach_defaults (GTK_TABLE(table), stop_all_button, 18, 20, 9, 10);
    gtk_table_attach_defaults (GTK_TABLE(table), quit_button, 16, 20, 13, 14);
  
    // add table to window
    gtk_container_add (GTK_CONTAINER (window), table);
    
    // keep it together
    Callback_Data *cb_data = new Callback_Data();
    cb_data->pq = pq;
    cb_data->scheduled_list = scheduled_list;
    cb_data->idle_list = idle_list;
    cb_data->window = window;
    
    // connect actions to callback functions
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    g_signal_connect(GTK_OBJECT(quit_button), "clicked", G_CALLBACK(destroy), cb_data);
    g_signal_connect(GTK_OBJECT(schedule_button), "clicked", G_CALLBACK(schedule), cb_data);
    g_signal_connect(GTK_OBJECT(deschedule_button), "clicked", G_CALLBACK(deschedule), cb_data);
    g_signal_connect(GTK_OBJECT(block_button), "clicked", G_CALLBACK(block), cb_data);
    g_signal_connect(GTK_OBJECT(pause_button), "clicked", G_CALLBACK(pause_process), cb_data);
    g_signal_connect(GTK_OBJECT(stop_button), "clicked", G_CALLBACK(stop_process), cb_data);
    g_signal_connect(GTK_OBJECT(stop_all_button), "clicked", G_CALLBACK(stop_all_processes), cb_data);

    // load the pre-loaded processes into the idle process list
    refresh_list(cb_data);
    
    // display the window for xQueueSys
    gtk_widget_show_all(window);
    gtk_main();
    
    // clean up this mess
    delete(pq);
    delete(cb_data);

    return 0;
}

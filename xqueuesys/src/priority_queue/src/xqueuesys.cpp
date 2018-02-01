#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "process_queue.h"
#include <gtk/gtk.h>
#include <X11/Xlib.h>

// declaration and definition of simple struct to hold
// callback data
struct Callback_Data
{
    Process_Queue *pq;
    GtkWidget *scheduled_list;
    GtkWidget *idle_list;
    GtkWidget *window;
    GtkWidget *dialog;
    GtkWidget **textboxes;
    GtkWidget **buttons;
};

// function declarations for callback functions (primarily)
// 
// these functions would be wrapped in a class ideally, possibly
// made as static functions 
void select_scheduled(GtkList *list, GtkWidget *widget, gpointer data); // TODO not working
void deselect_scheduled(GtkList *list, GtkWidget *widget, gpointer data); // TODO not working
void destroy(GtkWidget *widget, gpointer data);
static gboolean refresh_list(gpointer data);
void process_from_file(GtkWidget *widget, gpointer data);
void add_process(GtkWidget *widget, gpointer data);
void remove_process(GtkWidget *widget, gpointer data);
void edit_process(GtkWidget *widget, gpointer data); //TODO (MAYBE)
static void process_tracker_handler(int signum);
static void we_stopped_handler(int signum);
void schedule(GtkWidget *widget, gpointer data);
void deschedule(GtkWidget *widget, gpointer data);
void allow(GtkWidget *widget, gpointer data);
void block(GtkWidget *widget, gpointer data);
void continue_process(GtkWidget *widget, gpointer data);
void pause_process(GtkWidget *widget, gpointer data);
void stop_process(GtkWidget *widget, gpointer data);
void load_default_processes(Process_Queue *pq);

// global access required for signals, ideally this would be changed
Callback_Data *cb_data = new Callback_Data();

/*
 * xqueuesys main() - sets up gtk window, connects signals to callbacks
 *                    then hands over control to gtk_main()
 */
int main(int argc, char **argv)
{
    // initialize necessary for X11 and GTK libraries
    XInitThreads(); // prevents errors due to multithreading
    gtk_init(&argc, &argv); 
    
    // create the GTK window and main table widget
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 
    gtk_window_resize(GTK_WINDOW(window), 800, 600);
    
    // will contain all other widget objects
    GtkWidget *table = gtk_table_new (15, 20, TRUE); 
    
    // create buttons
    GtkWidget *schedule_button = gtk_button_new_with_label("Schedule"); 
    GtkWidget *deschedule_button = gtk_button_new_with_label("Deschedule"); 
    GtkWidget *allow_button = gtk_button_new_with_label("Allow");
    GtkWidget *block_button = gtk_button_new_with_label("Block");
    //GtkWidget *edit_button = gtk_button_new_with_label("Edit");
    GtkWidget *continue_button = gtk_button_new_with_label("Continue");
    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    GtkWidget *pause_button = gtk_button_new_with_label("Pause");
    GtkWidget *stop_button = gtk_button_new_with_label("Stop");
    GtkWidget *add_button = gtk_button_new_with_label("Add Process"); // add process
    GtkWidget *remove_button = gtk_button_new_with_label("Remove"); // remove process
    GtkWidget *from_file_button = gtk_button_new_with_label("Locate File");
    
    // file open box
    GtkWidget *dialog = gtk_file_chooser_dialog_new ("Select Process", NULL,  GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    
    // add process text box
    GtkWidget *process_textbox = gtk_entry_new();
    GtkWidget *nice_textbox = gtk_entry_new();
    GtkWidget *args_textbox = gtk_entry_new();
                
    // create scrollable lists
    GtkWidget *scheduled_scrolled = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *idle_scrolled = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *scheduled_list = gtk_list_new();
    GtkWidget *idle_list = gtk_list_new();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scheduled_scrolled), scheduled_list);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(idle_scrolled), idle_list);

    // labels above tables
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Process"), 0, 2, 1, 2);    
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Nice"), 4, 5, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Status"), 5, 8, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Process"), 12, 14, 1, 2);    
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Nice"), 16, 17, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Status"), 17, 20, 1, 2);
    
    // attach process text box
    gtk_table_attach_defaults (GTK_TABLE(table), process_textbox, 1,7, 12, 13);
    gtk_table_attach_defaults (GTK_TABLE(table), args_textbox, 1,7, 13, 14);
    gtk_table_attach_defaults (GTK_TABLE(table), nice_textbox, 1,7, 14, 15);
    
    // labels for text box
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Path"), 0, 1, 12, 13);
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Args"), 0, 1, 13, 14);
    gtk_table_attach_defaults (GTK_TABLE(table), gtk_label_new("Nice"), 0, 1, 14, 15);
    
    // attach scrollable list to table
    gtk_table_attach_defaults (GTK_TABLE(table), idle_scrolled, 0, 8, 2, 10);
    gtk_table_attach_defaults (GTK_TABLE(table), scheduled_scrolled, 12, 20, 2, 10);
    
    // attach buttons 
    gtk_table_attach_defaults (GTK_TABLE(table), schedule_button, 9, 11, 4, 5);  
    gtk_table_attach_defaults (GTK_TABLE(table), deschedule_button, 9, 11, 7, 8);
    gtk_table_attach_defaults (GTK_TABLE(table), allow_button, 0, 2, 10, 11); 
    gtk_table_attach_defaults (GTK_TABLE(table), block_button, 2, 4, 10, 11);
    //gtk_table_attach_defaults (GTK_TABLE(table), edit_button, 4, 6, 10, 11);
    gtk_table_attach_defaults (GTK_TABLE(table), continue_button, 12, 14, 10, 11); 
    gtk_table_attach_defaults (GTK_TABLE(table), pause_button, 14, 16, 10, 11); 
    gtk_table_attach_defaults (GTK_TABLE(table), stop_button, 18, 20, 10, 11);
    gtk_table_attach_defaults (GTK_TABLE(table), quit_button, 16, 20, 14, 15);
    gtk_table_attach_defaults (GTK_TABLE(table), add_button, 7, 9, 13, 15);
    gtk_table_attach_defaults (GTK_TABLE(table), remove_button, 6, 8, 10, 11); 
    gtk_table_attach_defaults (GTK_TABLE(table), from_file_button, 7, 9, 12, 13);
  
    // add table to window
    gtk_container_add (GTK_CONTAINER (window), table);
    
    // create a process queue processes
    Process_Queue *pq = new Process_Queue(); 
    
    // load built-in processes
    load_default_processes(pq);
    
    // keep it together - cb_data holds all pointers used in callbacks
    cb_data->pq = pq;
    cb_data->scheduled_list = scheduled_list;
    cb_data->idle_list = idle_list;
    cb_data->window = window;
    cb_data->dialog = dialog;
    GtkWidget *textbox_list[3] = {process_textbox, args_textbox, nice_textbox};
    cb_data->textboxes  = textbox_list;
    GtkWidget *button_list[8] = {schedule_button, deschedule_button, allow_button, block_button, quit_button, pause_button, stop_button, add_button};
    cb_data->buttons =  button_list;
    
    
    // connect actions to callback functions
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    g_signal_connect(GTK_OBJECT(quit_button), "clicked", G_CALLBACK(destroy), cb_data);
    g_signal_connect(GTK_OBJECT(schedule_button), "clicked", G_CALLBACK(schedule), cb_data);
    g_signal_connect(GTK_OBJECT(deschedule_button), "clicked", G_CALLBACK(deschedule), cb_data);
    g_signal_connect(GTK_OBJECT(allow_button), "clicked", G_CALLBACK(allow), cb_data);
    g_signal_connect(GTK_OBJECT(block_button), "clicked", G_CALLBACK(block), cb_data);
    g_signal_connect(GTK_OBJECT(pause_button), "clicked", G_CALLBACK(pause_process), cb_data);
    g_signal_connect(GTK_OBJECT(stop_button), "clicked", G_CALLBACK(stop_process), cb_data);
    g_signal_connect (process_textbox, "activate", G_CALLBACK(add_process), cb_data);
    g_signal_connect (GTK_OBJECT(add_button), "clicked", G_CALLBACK(add_process), cb_data);
    g_signal_connect (GTK_OBJECT(remove_button), "clicked", G_CALLBACK(remove_process), cb_data);
    //g_signal_connect (GTK_OBJECT(edit_button), "clicked", G_CALLBACK(edit_process), cb_data);
    g_signal_connect (GTK_OBJECT(from_file_button), "clicked", G_CALLBACK(process_from_file), cb_data);
    g_signal_connect(GTK_OBJECT(continue_button), "clicked", G_CALLBACK(continue_process), cb_data);
   
    // listen for process_tracker to complete
    signal(SIGUSR1, process_tracker_handler);
    signal(SIGUSR2, we_stopped_handler);


    // load the pre-loaded processes into the idle process list
    refresh_list(cb_data);
    
    // display the window for xQueueSys
    gtk_widget_show_all(window);

    // yield program control over to gtk, it is all callbacks from here
    gtk_main();
    
    // clean up
    delete(pq);
    delete(cb_data);

    return 0;
} //end of main


/*
 * select_scheduled(GtkWidget*, gpointer)
 */
void select_scheduled(GtkList *list, GtkWidget *widget, gpointer data) // TODO not working
{
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        
        // allow buttons 
        gtk_widget_set_sensitive (cb->buttons[5], TRUE); // pause button
        gtk_widget_set_sensitive (cb->buttons[6], TRUE); // stop button
    } 
    
}

/*
 * deselect_scheduled(GtkWidget*, gpointer) -
 */
void deselect_scheduled(GtkList *list, GtkWidget *widget, gpointer data) // TODO not working
{
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        
        // disallow buttons 
        gtk_widget_set_sensitive (cb->buttons[5], FALSE); // pause button
        gtk_widget_set_sensitive (cb->buttons[6], FALSE); // stop button
    } 
}

/*
 * destroy(GtkWidget*, gpointer) -
 */
void destroy(GtkWidget *widget, gpointer data)
{ 
    int status;
    
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        if(!cb->pq->no_running_process())
        {   
            kill(cb->pq->Running_Process_Pid(), SIGUSR1);  
            waitpid(cb->pq->Running_Process_Pid(), &status, 0);
        }
    }
    gtk_main_quit(); 
}

/*
 * refresh_list(gpointer) -
 */
static gboolean refresh_list(gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->add_processes_to_lists(cb->scheduled_list, cb->idle_list);   
        gtk_widget_show_all(cb->window);
    } 
}

/*
 * process_from_file(GtkWidget*, gpointer) -
 */
void process_from_file(GtkWidget *widget, gpointer data)
{
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        
        if (gtk_dialog_run (GTK_DIALOG (cb->dialog)) == GTK_RESPONSE_ACCEPT)
        {
            char *filename;
            filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (cb->dialog));
            gtk_entry_set_text(GTK_ENTRY(cb->textboxes[0]), filename);
        }
        gtk_widget_destroy (cb->dialog);
        cb->dialog = gtk_file_chooser_dialog_new ("Select Process", NULL,  GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    } 
}

/*
 * add_process(GtkWidget*, gpointer) -
 */
void add_process(GtkWidget *widget, gpointer data)
{
    if(data != NULL)
    {      
        Callback_Data *cb = (Callback_Data*) data;  
        
        const gchar *entry_text;
        entry_text = gtk_entry_get_text (GTK_ENTRY(cb->textboxes[0]));
        std::string entry = entry_text;

        if(entry!= "")
        {
            std::string process_data = entry_text;
            cb_data->pq->add_process(process_data);
            
            entry_text = gtk_entry_get_text(GTK_ENTRY(cb->textboxes[2]));
            entry = entry_text;
            if(entry != "")
            {
                int how_nice = atoi(entry_text);
                if(how_nice >0 && how_nice <= 20)
                {
                    cb_data->pq->Child_Nice(process_data, how_nice);
                }
            }
            entry_text = gtk_entry_get_text(GTK_ENTRY(cb->textboxes[1]));
            entry = entry_text;
            if(entry != "")
            {
                cb_data->pq->Child_Args(process_data, entry);
            } 
        }
        refresh_list(cb);    
    }   
}

/*
 * remove_process(GtkWidget*, gpointer)
 */
void remove_process(GtkWidget *widget, gpointer data)
{
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        GList *dlist = GTK_LIST(cb->idle_list)->selection;
        if(dlist != NULL)
        {
            GtkWidget *selected_item = GTK_WIDGET(dlist->data);
            GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_item));
            std::string process_data = gtk_label_get_text(GTK_LABEL(label));
            if(cb->pq != NULL)
            {
                cb->pq->remove_process(process_data);
            }
            else
            {
                // TODO you might want to terminate the program here
            }
        }
        else
        {
            // do nothing
        }
        refresh_list(data);      
    }
}

/*
 * edit_process(GtkWidget*, gpointer)
 */
void edit_process(GtkWidget *widget, gpointer data) //TODO (MAYBE)
{
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        GList *dlist = GTK_LIST(cb->idle_list)->selection;
        if(dlist != NULL)
        {
            GtkWidget *selected_item = GTK_WIDGET(dlist->data);
            GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_item));
            std::string process_data = gtk_label_get_text(GTK_LABEL(label));
            if(cb->pq != NULL)
            {
                // TODO you might want to terminate the program here
            }
            else
            {
                // TODO you might want to terminate the program here
            }
        }
        else
        {
            // do nothing
        }
        refresh_list(data);      
    }
}

/*
 * process_tracker_handler(int) - 
 */
static void process_tracker_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        if(cb_data != NULL)
        {
            cb_data->pq->done();
            refresh_list(cb_data);
            if(cb_data->pq->no_running_process())
            {
                cb_data->pq->run_process(cb_data->pq->next_up());
            }
        }
    }
    else
    {
        // do nothing
    }
    refresh_list(cb_data);    
}

/*
 * we_stopped_handler(int) -
 */
static void we_stopped_handler(int signum)
{
    if (signum == SIGUSR2)
    {
        if(cb_data != NULL)
        {
            if(cb_data->pq->no_running_process())
            {
                cb_data->pq->run_process(cb_data->pq->next_up());
            }
        } 
    }   
}

/*
 * schedule(GtkWidget*, gpointer) -
 */
void schedule(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        GList *dlist = GTK_LIST(cb->idle_list)->selection;
        if(dlist != NULL)
        {
            GtkWidget *selected_item = GTK_WIDGET(dlist->data);
            GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_item));
            std::string process_data = gtk_label_get_text(GTK_LABEL(label));
            if(cb->pq != NULL)
            {
                cb->pq->schedule(process_data);
                if(cb->pq->no_running_process())
                {
                    cb->pq->run_process(cb->pq->next_up());
                }
            }
            else
            {
                // TODO you might want to terminate the program here
            }
        }
        else
        {
            // do nothing
        }
    }
    refresh_list(data);    
}

/*
 * deschedule(GtkWidget*, gpointer) -
 */
void deschedule(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        GList *dlist = GTK_LIST(cb->scheduled_list)->selection;
        if(dlist != NULL)
        {
            GtkWidget *selected_item = GTK_WIDGET(dlist->data);
            GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_item));
            std::string process_data = gtk_label_get_text(GTK_LABEL(label));
            if(cb->pq != NULL)
            {
                cb->pq->deschedule(process_data);
            }
            else
            {
                // TODO you might want to terminate the program here
            }
        }
        else
        {
            // do nothing
        }
        refresh_list(data);    
    }
}

/*
 * allow(GtkWidget*, gpointer) -
 */
void allow(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        GList *dlist = GTK_LIST(cb->idle_list)->selection;
        if(dlist != NULL)
        {
            GtkWidget *selected_item = GTK_WIDGET(dlist->data);
            GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_item));
            std::string process_data = gtk_label_get_text(GTK_LABEL(label));
            if(cb->pq != NULL)
            {
                cb->pq->allow(process_data);
            }
            else
            {
                // TODO you might want to terminate the program here
            }
        }
        else
        {
            // do nothing
        }
    }
    refresh_list(data);    
}

/*
 * block(GtkWidget*, gpointer) -
 */
void block(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        GList *dlist = GTK_LIST(cb->idle_list)->selection;
        if(dlist != NULL)
        {
            GtkWidget *selected_item = GTK_WIDGET(dlist->data);
            GtkWidget *label = gtk_bin_get_child(GTK_BIN(selected_item));
            std::string process_data = gtk_label_get_text(GTK_LABEL(label));
            if(cb->pq != NULL)
            {
                cb->pq->block(process_data);
            }
            else
            {
                // TODO you might want to terminate the program here
            }
        }
        else
        {
            // do nothing
        }
    }
    refresh_list(data);    
}

/*
 * continue_process(GtkWidget*, gpointer) -
 */
void continue_process(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->pause_process(true);
        refresh_list(data);    
    }
}

/*
 * pause_process(GtkWidget*, gpointer) -
 */
void pause_process(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->pause_process(false);
        refresh_list(data);    
    }
}

/* 
 * stop_process(GtkWidget*, gpointer) -
 */
void stop_process(GtkWidget *widget, gpointer data)
{ 
    if(data != NULL)
    {
        Callback_Data *cb = (Callback_Data*) data;
        cb->pq->stop_process();
        refresh_list(data);    
    }
}

/*
 * load_default_processes(Process_Queue*) -
 */
void load_default_processes(Process_Queue *pq)
{
    // load the built-in processes into the idle process queue
    // new_process(string Process_Path, int Nice)
    pq->new_process("processes/n_factorial", 2);
    pq->new_process("processes/n_fibonacci", 2);
    pq->new_process("processes/ascii_image", 7);
    pq->new_process("processes/crypto"); //default nice is 10
    pq->new_process("processes/recho", 4);
    pq->new_process("processes/n_countdown"); 
}

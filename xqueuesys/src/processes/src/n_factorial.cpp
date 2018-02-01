#include <iostream>
#include <gtk/gtk.h>
#include <X11/Xlib.h>

void destroy(GtkWidget *widget, gpointer data)
{ 
    gtk_main_quit(); 
}

void factor(long &n, long &factorial, bool &factorial_done)
{
    if(n == 0)
    {
        factorial_done = true;
    }
    else
    {
        long nminusone = n - 1;
        long factorialite = factorial;
        factor(nminusone, factorialite, factorial_done);
        factorial =  n * factorialite;
    }
}

int main(int argc, char** argv)
{
    // initialize necessary for X11 and GTK libraries
    XInitThreads();
    gtk_init(&argc, &argv);
    
    // create the GTK window and objects
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *quit_button = gtk_button_new_with_label("Quit"); 
    
    // connect actions to callback functions
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL); 
    g_signal_connect(GTK_OBJECT(quit_button), "clicked", G_CALLBACK(destroy), NULL);
    
    // configure window
    gtk_container_set_border_width(GTK_CONTAINER(window), 20); 
    
    // add objects to window
    gtk_container_add(GTK_CONTAINER(window), quit_button);

    long n = 314;
    
    if(argc > 1)
    {
        n = long(argv[1]);
    }
    else
    {
        // do nothing
    }
    
    long factorial = 0;
    bool factorial_done = false;
    
    factor(n, factorial, factorial_done);

    std::string result = "The factorial of " + std::to_string(n) + " is " + std::to_string(factorial);

    // display the window
    gtk_widget_show_all(window);
    gtk_main();
      
    return 0;
}

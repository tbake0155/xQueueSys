#include <iostream>
#include <gtk/gtk.h>
#include <X11/Xlib.h>

int main(int argc, char** argv)
{
    long n = 10000;
    
    if(argc > 1)
    {
        n = long(argv[1]);
    }
    else
    {
        // do nothing
    }
    
    std::cout << "It's the final countdown!" << std::endl;
    
    for(int i=0; i<n; i++)
    {
        std::cout << "\r" << n << std::flush;
    }
    
    return 0;
}

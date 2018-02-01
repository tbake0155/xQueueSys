#include <iostream>

int main(int argc, char** argv)
{
    std::string message = "no message";
    
    if(argc > 1)
    {
        message = argv[1];
    }
    else
    {
        //do nothing
    }
    
    while(message != "quit")
    {
        std::cout << "message: " << message << std::endl;
        std::cout << "\nEnter a new message: ";
        std::cin >> message;
        std::cin.ignore('\n', 100);
    }
    
    std::cout << "You've decided to quit, Goodbye!" << std::endl;
    
    return 0;
}

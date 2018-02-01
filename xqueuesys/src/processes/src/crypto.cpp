#include <iostream>

// simple XOR encryption
std::string encrypt(std::string message, char key)
{
    std::string encrypted = "";
 
    for (int i=0; i<message.size(); i++)
    {
        encrypted += message[i] ^ (int(key) + i) % 255;
    }
    
    return encrypted;
}

int main(int argc, char** argv)
{
    std::string message = "no message";
    char key = 'k';
    
    if(argc > 2)
    {
        message = argv[1];
        key = argv[2][0];
    }
    else
    {
        //do nothing
    }
    
    while(message != "quit")
    {
        std::cout << "message: " << message << std::endl;
        std::cout << "encryped message: " << encrypt(message, key) << std::endl;
        std::cout << "\nEnter a new message: ";
        std::cin >> message;
        std::cin.ignore('\n', 100);
    }
    
    std::cout << "You've decided to quit, Goodbye!" << std::endl;
    
    return 0;
}

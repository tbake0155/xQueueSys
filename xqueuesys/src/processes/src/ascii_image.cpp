#include <iostream>

int main(int argc, char** argv)
{
    bool foreverandever = true;
    
    std::string image1 = "nothing";
    std::string image2 = "to";
    std::string image3 = "see";
    std::string image4 = "here";
    std::string image5 = "!";
    
    if(argc > 1)
    {
        if(argv[1] == "false")
        {
            foreverandever = false;
        }
        else
        {
            // do nothing
        }
    }
        std::cout << "\r" << image1 << std::flush;
        std::cout << "\r" << image2 << std::flush;
        std::cout << "\r" << image3 << std::flush;
        std::cout << "\r" << image4 << std::flush;
        std::cout << "\r" << image5 << std::flush;



    return 0;
}

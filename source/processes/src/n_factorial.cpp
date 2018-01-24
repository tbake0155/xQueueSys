#include <iostream>
#include <thread>
#include <chrono>

void factor(long * n, long * factorial, bool * factorial_done)
{
    if(*n == 0)
    {
        *factorial_done = true;
    }
    else
    {
        long nminusone = *n - 1;
        long factorialite = *factorial;
        factor(&nminusone, &factorialite, factorial_done);
        *factorial =  *n * factorialite;
    }
}

int main(int argc, char** argv)
{
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
    
    std::cout << "Calculating factorial" << std::endl;
    
    bool factorial_done = false;
    
    std::thread thread_one(&factor, &n, &factorial, &factorial_done);
    
    while(factorial_done == false)
    {
        std::cout << "\r" << "\\" << std::flush;
        std::cout << "\r" << "-" << std::flush;
        std::cout << "\r" << "/" << std::flush;
        std::cout << "\r" << "-" << std::flush;
    }
    
    thread_one.join();
    
    std::cout << "\n The factorial of " << n << " is " << factorial << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10)); 
    
    return 0;
}

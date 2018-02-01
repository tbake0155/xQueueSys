#include <iostream>

void fib(long * n, long * fibonacci, bool * fib_done)
{
    long fib1 = 1;
    long fib2 = 1;
    
    for(int i=0; i<*n; i++)
    {
        long fib = fib1 + fib2;
        fib2 = fib1;
        fib1 = fib;
    }
    
    *fibonacci = fib1;
}

int main(int argc, char** argv)
{
    long n = 14;
    
    if(argc > 1)
    {
        n = long(argv[1]);
    }
    else
    {
        // do nothing
    }
    
    long fibonacci_number = 0;
    
    std::cout << "Calculating fibonacci number" << std::endl;
    
    bool fib_done = false;
    
   fib(&n, &fibonacci_number, &fib_done);

    std::cout << "\n The " << n << "the Fibonacci number is " << fibonacci_number << std::endl;
    
    return 0;
}

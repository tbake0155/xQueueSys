#include "process.h"
#include <signal.h>
#include <unistd.h>

Process::Process(std::string process_name, int how_nice)
{
    pid_t PID = fork();
    std::string execute = std::string("xterm -e ") + std::string("'") + process_name + std::string("'");
    const char * process_ptr = &execute[0];
    
    if (PID == 0)
    {
        system(process_ptr);
    }
    
    else
    {
        this->process = process_name;
        this->pid = PID;
        this->nice = how_nice;
        this->counter = 0;
    }
}

Process::Process(std::string process_name)
{
    pid_t PID = fork();
    
    std::string execute = std::string("xterm -e ") + std::string("'") + process_name + std::string("'");
    const char * process_ptr = &execute[0];
    
    if (PID == 0)
    {
        system(process_ptr);
    }
    
    else
    {
        this->process = process_name;
        this->pid = PID;
        this->nice = 10;
        this->counter = 0;
    }
}

void Process::harikari()
{
    kill(this->pid, SIGKILL);
}

void Process::pheonixrising()
{
    pid_t PID = fork();
    
    std::string execute = std::string("xterm -e ") + std::string("'") + this->process + std::string("'");
    const char * process_ptr = &execute[0];
    
    if (PID == 0)
    {
        system(process_ptr);
    }

    else
    {
        this->pid = PID;
        this->counter = 0;
    }
}

#include "process_queue.h"
#include <signal.h>
#include <unistd.h>

bool process_sort(Process proc1, Process proc2)
{
    return proc1.Nice() <= proc2.Nice();
}

void Process_Queue::add_process(Process new_process)
{
    processes.emplace_back(new_process);
    processes.sort(process_sort);
}

void Process_Queue::remove_process(Process old_process)
{    
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Pid() == old_process.Pid())
        {
            this->processes.erase(process_itr);
            break;
        }
        process_itr++;
    }
}

void Process_Queue::new_process(std::string process_name)
{
    Process process(process_name);
    this->add_process(process);
}

void Process_Queue::new_process(std::string process_name, int how_nice)
{
    Process process(process_name, how_nice);
    this->add_process(process);
}

void Process_Queue::Child_Pid(std::string Process_Path, pid_t Child_Pid)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            process_itr->Pid(Child_Pid);
            break;
        }
        process_itr++;
    }
     
}

pid_t Process_Queue::Child_Pid(std::string Process_Path)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            return process_itr->Pid();
        }
        process_itr++;
    }
    
    return -1;
}

std::string Process_Queue::Child_Process(std::string Process_Path)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            process_itr->Process_Path();
            break;
        }
        process_itr++;
    }
}

std::string Process_Queue::Child_Status(std::string Process_Path)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            process_itr->Status();
            break;
        }
        process_itr++;
    }
}

void Process_Queue::Child_Status(std::string Process_Path, std::string Child_Status)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            process_itr->Status(Child_Status);
            break;
        }
        process_itr++;
    }     
}

void Process_Queue::kill_process(std::string Process_Path, std::string method)
{
    if(method == "SIGTERM")
    {
        std::list<Process>::iterator process_itr = this->processes.begin();
    
        while(process_itr != this->processes.end())
        {
            if(process_itr->Process_Path() == Process_Path)
            {
                kill(process_itr->Pid(), SIGTERM);
            }
            process_itr++;
        }
    }
    else if(method == "SIGKILL")
    {
        std::list<Process>::iterator process_itr = this->processes.begin();
    
        while(process_itr != this->processes.end())
        {
            if(process_itr->Process_Path() == Process_Path)
            {
                kill(process_itr->Pid(), SIGKILL);
            }
            process_itr++;
        }
    }
    else
    {
        // don't kill anything
    } 
}

void Process_Queue::kill_process(std::string Process_Path)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            kill(process_itr->Pid(), SIGTERM);
        }
        process_itr++;
    }
}

// etorw ehs redrum
void Process_Queue::kill_all_processes(std::string method)
{
    if(method == "SIGTERM")
    {
        std::list<Process>::iterator process_itr = this->processes.begin();
    
        while(process_itr != this->processes.end())
        {
            kill(process_itr->Pid(), SIGTERM);
            process_itr++;
        }
    }
    else if(method == "SIGKILL")
    {
        std::list<Process>::iterator process_itr = this->processes.begin();
    
        while(process_itr != this->processes.end())
        {
            kill(process_itr->Pid(), SIGKILL);
            process_itr++;
        }
    }
    else
    {
        // don't kill anything
    }
}

void Process_Queue::run_process(const char *Process_Path)
{
   // create another child process inside this child process
   pid_t child_pid = fork();
        
   // child block
   if(child_pid == 0)
   {
       // execute process and allow this child to become the new process
       execlp(Process_Path,Process_Path, NULL);
   }
   // parent block
   else
   {
       // assign variables for program
       this->Child_Pid(Process_Path, child_pid);
       this->Child_Status(Process_Path, "running");
   }
}








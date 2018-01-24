#include "process_queue.h"

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
    old_process.harikari();
    
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

void Process_Queue::kill_process(std::string process_name)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Name() == process_name)
        {
            this->remove_process(*process_itr);
            break;
        }
        process_itr++;
    }
}

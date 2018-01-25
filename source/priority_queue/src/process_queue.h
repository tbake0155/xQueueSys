#ifndef PROCESS_QUEUE_H_INCLUDED
#define PROCESS_QUEUE_H_INCLUDED

#include "process.h"
#include <list>

class Process_Queue
{
    private:
        std::list<Process> processes;
        
    public:
        Process_Queue(){}
        void new_process(std::string process_name);
        void new_process(std::string process_name, int how_nice);
        void add_process(Process new_process);
        void remove_process(Process old_process);
        void Child_Pid(std::string Process_Path, pid_t Child_Pid);
        pid_t  Child_Pid(std::string Process_Path);
        std::string Child_Process(std::string Process_Path);
};
#endif // PROCESS_QUEUE_H

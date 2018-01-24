#ifndef PROCESS_QUEUE_H_INCLUDED
#define PROCESS_QUEUE_H_INCLUDED

#include "process.h"
#include <list>

class Process_Queue
{
    private:
        long counter;
        std::list<Process> processes;
        void add_process(Process new_process);
        void remove_process(Process old_process);
        
    public:
        Process_Queue(){this->counter=0;}
        long Counter(){return counter;}
        void Counter(long new_counter){counter = new_counter;}
        void reset_count(){counter = 0;}
        void new_process(std::string process_name);
        void new_process(std::string process_name, int how_nice);
        void kill_process(std::string process_name);
};
#endif // PROCESS_QUEUE_H

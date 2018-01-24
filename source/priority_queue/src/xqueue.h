#ifndef XQUEUE_H_INCLUDED
#define XQUEUE_H_INCLUDED

#include "process_queue.h"

class Xqueue
{
    private:
        long counter;
        Process_Queue pq;
        
    public:
        Xqueue(){this->counter=0;}
        ~Xqueue(){};
        long Counter(){return counter;}
        void Counter(long new_counter){counter = new_counter;}
        void reset_count(){counter = 0;}
        void new_process(std::string process_name);
        void new_process(std::string process_name, int how_nice);
        void kill_process(std::string process_name);
};
#endif // XQUEUE_H_INCLUDED

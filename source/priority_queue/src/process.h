#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <iostream>

class Process
{
    private:
        std::string process;
        long counter;
        pid_t pid;
        int nice;
        Process(){} // can't touch this
      
    public:
        Process(std::string process_name, int how_nice);
        Process(std::string process_name);
        ~Process(){}
        void harikari();
        void pheonixrising();
        long Counter(){return counter;}
        void Counter(long new_counter){counter = new_counter;}
        void reset_count(){counter = 0;}
        std::string Process_Name(){return process;}
        int Pid(){return pid;}
        void Pid(int manual_pid){pid = manual_pid;}
        int Nice(){return nice;}
        void Nice(int new_nice){nice = new_nice;}
        int default_nice(){return 10;}
};
#endif // PROCESS_H

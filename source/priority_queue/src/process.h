#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <iostream>

class Process
{
    private:
        std::string process_path;
        std::string status; // idle, waiting, running, blocked
        pid_t pid;
        int nice;
        Process(){} // can't touch this
      
    public:
        Process(std::string Process_Path, int How_Nice);
        Process(std::string Process_Path);
        ~Process(){}
        std::string Process_Path(){return this->process_path;}
        void Pid(pid_t Pid){this->pid=Pid;}
        pid_t Pid(){return this->pid;}
        void Nice(int Nice){this->nice=Nice;}
        int Nice(){return this->nice;}
        std::string Status(){return this->status;}
        void Status(std::string Child_Status){this->status=Child_Status;}
};
#endif // PROCESS_H

#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <iostream>

class Process
{
    private:
        std::string process_path;
        std::string status; // idle, waiting, running, blocked, failed
        std::string args;
        int status_num;
        pid_t pid;
        int nice;
        Process(){} // can't touch this
      
    public:
        Process(std::string Process_Path, int How_Nice, std::string args);
        Process(std::string Process_Path, int How_Nice);
        Process(std::string Process_Path);
        ~Process(){}
        std::string Process_Path(){return this->process_path;}
        std::string Args(){return this->args;}
        void Args(std::string Args){this->args=Args;}
        void Pid(pid_t Pid){this->pid=Pid;}
        pid_t Pid(){return this->pid;}
        void Nice(int Nice){this->nice=Nice;}
        int Nice(){return this->nice;}
        std::string Status(){return this->status;}
        void Status(std::string Child_Status){this->status=Child_Status; this->set_status_num();}
        std::string path_to_name(std::string path); 
        std::string path_to_name();
        std::string Scrollable_List_Data(bool include_pid);
        bool match_process(std::string process_data, bool include_pid);
        void set_status_num();
        bool operator<(Process const& other)const;
        bool operator==(Process const& other)const;
        bool operator!=(Process const& other)const;
};
#endif // PROCESS_H

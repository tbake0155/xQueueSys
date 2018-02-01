#ifndef PROCESS_QUEUE_H_INCLUDED
#define PROCESS_QUEUE_H_INCLUDED

#include "process.h"
#include <list>
#include <gtk/gtk.h>

class Process_Queue
{
    private:
        std::list<Process> processes;
        
    public:
        Process_Queue();
        int num_processes(){return this->processes.size();}
        void new_process(std::string process_name);
        void new_process(std::string process_name, int how_nice);
        void new_process(std::string process_name, int how_nice, std::string Args);
        void add_process(Process new_process);
        void remove_process(Process old_process);
        void remove_process(std::string process_data);
        void Child_Args(std::string Process_Path, std::string Child_Args);
        std::string Child_Args(std::string Process_Path);
        void Child_Nice(std::string Process_Path, int Child_Nice);
        int Child_Nice(std::string Process_Path);
        void Child_Pid(std::string Process_Path, pid_t Child_Pid);
        pid_t  Child_Pid(std::string Process_Path);
        std::string Child_Process(std::string Process_Path);
        void Child_Status(std::string Process_Path, std::string Status);
        std::string Child_Status(std::string Status);
        void kill_process(std::string Process_Path);
        void kill_process(std::string Process_Path, std::string method);
        void kill_all_processes(std::string method);
        bool run_process(std::string Process_Path);
        void load_processes_from_file(std::string File_Path); // TODO
        void add_processes_to_lists(GtkWidget *scheduled_list, GtkWidget *idle_list);
        void scheduler(std::list<Process>::iterator process_itr);
        void schedule(std::string process_data);
        void deschedule(std::string process_data);
        void allow(std::string process_data);
        void block(std::string process_data);
        bool no_running_process();
        std::string next_up();
        void done();
        void pause_process();
        void stop_process();
        pid_t Running_Process_Pid();
};
#endif // PROCESS_QUEUE_H

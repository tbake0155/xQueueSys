/*
 * process_queue.h - class declaration for Process_Queue object
 */

#ifndef PROCESS_QUEUE_H_INCLUDED
#define PROCESS_QUEUE_H_INCLUDED

#include "process.h"
#include <list>
#include <gtk/gtk.h>

/*
 * Process_Queue - class wrapper for a list of processes
 */
class Process_Queue
{
    private:
    
       std::list<Process> processes; // list of processes
        
    public:
    
       /*
        * constructor - default constructor is all that is available
        */
       Process_Queue();
       
       /*
        * destructor - default constructor, let this->processes die how
        *              std::list is defaulted to die
        */ 
        ~Process_Queue(){}        

       /*        
        * Child_Args(string, string) - set child args by matching process path
        */          
        void Child_Args(std::string Process_Path, std::string Child_Args);
        
       /*        
        * Child_Args(string) - get child args by matching process path
        */         
        std::string Child_Args(std::string Process_Path);
        
       /*        
        * Child_Nice(string, int) -  set child nice by matching process path
        */         
        void Child_Nice(std::string Process_Path, int Child_Nice);
        
       /*        
        * Child_Nice(string) - get child nice by matching process path
        */          
        int Child_Nice(std::string Process_Path);
        
       /*        
        * Child_Pid(string, pid_t) -  set child pid by matching process path
        */         
        void Child_Pid(std::string Process_Path, pid_t Child_Pid);
        
       /*        
        * Child_Pid(string) -  get child pid by matching process path
        */         
        pid_t  Child_Pid(std::string Process_Path); // ONLY VALID IF RUNNING!
        
       /*        
        * Child_Status(string, string) -  set child status by matching process path
        */ 
        void Child_Status(std::string Process_Path, std::string Status);
        
       /*        
        * Child_Pid(string) -  get child pid by matching process path
        */           
        std::string Child_Status(std::string Status);
        
        /*
         * num_process() - get the number of elements in processes
         */
        int num_processes(){return this->processes.size();}
        
        /*
         * new_process(string) - create new process with only the path
         */
        void new_process(std::string process_name);
        
        /*
         * new_process(string, int) - create new process with path and nice
         */     
        void new_process(std::string process_name, int how_nice);
        
        /*
         * new_process(string, int, string) - create new process with path,
         *                                    nice and args
         */ 
        void new_process(std::string process_name, int how_nice, std::string Args);
        
        /*
         * add_process(Process) - add a process that already exist somewhere elst
         */         
        void add_process(Process new_process);
        
        /*
         * remove_process(Process) - remove a process by matching the process
         *                           directly
         */          
        void remove_process(Process old_process);
        
        /*
         * remove_process(string) - remove a process by matching its path
         */          
        void remove_process(std::string process_data);
        
        /*
         * kill_process(string) - kill a process by matching its path
         */              
        void kill_process(std::string Process_Path);
        
        /*
         * kill_process(string, string) - kill a process by matching its path
         *                                using the specified method (check 
         *                                definition for more details)
         */         
        void kill_process(std::string Process_Path, std::string method);
        
        /*
         * kill_all_processes(string) - kill all processes using the 
         *                              specified method (check definition 
         *                              for more details)
         */ 
        void kill_all_processes(std::string method);
        
        /*
         * run_process(string) - launches process tracker, which 
         *                       calls exec(Process_Path)
         */            
        bool run_process(std::string Process_Path);
        
        /*
         * add_processes_to_lists(GtkWidget*, GtkWidget*) - split the processes
         *                                                  into scheduled/idle,
         *                                                  destroy the old list,
         *                                                  rebuild the list with 
         *                                                  our divided processes
         */         
        void add_processes_to_lists(GtkWidget *scheduled_list, GtkWidget *idle_list);
        
        /*
         * schedule(string) - schedule an idle process
         *
         * button clicked : "Schedule"
         */          
        void schedule(std::string process_data);
        
        /*
         * deschedule(string) - deschedule a scheduled process
         *
         * button clicked : "Deschedule"
         */           
        void deschedule(std::string process_data);
        
        /*
         * allow(string) - allow an idle process to be scheduled
         *
         * button clicked : "Allow"
         */         
        void allow(std::string process_data);
        
        /*
         * block(string) - block an idle process from being scheduled
         *
         * button clicked : "Block"
         */           
        void block(std::string process_data);      
        
        /*
         * pause_process(string) - pause/continue a running process,
         *                         calls SIGTSTP/SIGCONT respectively
         *
         * button clicked : "Pause"
         */            
        void pause_process(bool paused);
        
        /*
         * stop_process(string) - terminate a running or paused process
         *
         * button clicked : "Stop"
         */          
        void stop_process();
        
        /*
         * no_running_process() - checks for a running process
         */         
        bool no_running_process();
        
        /*
         * next_up() - finds the next waiting process with highest priority
         */          
        std::string next_up();
        
        /*
         * done() - change the status of the current running process to idle
         */        
        void done();
        
        /*
         * Running_Process_Pid() - returns the Pid of the instance of 
         *                         process_tracker that is running the 
         *                         process 
         */        
        pid_t Running_Process_Pid();
        
        /*
         * load_processes_from_file() - allow user to load many processes at 
         *                              one time by specifying path, nice and args
         *                              in a text file, one line per process
         */        
        void load_processes_from_file(std::string File_Path); // TODO
};
#endif // PROCESS_QUEUE_H

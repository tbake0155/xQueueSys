#include "process_queue.h"
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <thread>
#include <chrono>

#define WRITE 1
#define READ 0

#define MSGSIZE  8

/*
 * constructor - default constructor is all that is available
 */
Process_Queue::Process_Queue()
{

}

/*        
 * Child_Args(string, string) - set child args by matching process path
 */  
void Process_Queue::Child_Args(std::string Process_Path, std::string Child_Args)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            process_itr->Args(Child_Args);
            break;
        }
        process_itr++;
    }
     
}

/*        
 * Child_Args(string) - get child args by matching process path
 */  
std::string Process_Queue::Child_Args(std::string Process_Path)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            return process_itr->Args();
            break;
        }
        process_itr++;
    }
    
    return "";
}

/*        
 * Child_Nice(string, int) -  set child nice by matching process path
 */         
void Process_Queue::Child_Nice(std::string Process_Path, int Child_Nice)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            process_itr->Nice(Child_Nice);
            break;
        }
        process_itr++;
    }    
}
        
/*        
 * Child_Nice(string) - get child nice by matching process path
 */          
int Process_Queue::Child_Nice(std::string Process_Path)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            return process_itr->Nice();
        }
        process_itr++;
    }
    
    return -1;
}

/*        
 * Child_Pid(string, pid_t) -  set child pid by matching process path
 */         
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
        
/*        
 * Child_Pid(string) -  get child pid by matching process path
 */         
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

/*        
 * Child_Status(string, string) -  set child status by matching process path
 */       
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

/*        
 * Child_Status(string) -  get child Status by matching process path
 */     
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
        
/*
 * new_process(string) - create new process with only the path
 */
void Process_Queue::new_process(std::string process_name)
{
    Process process(process_name);
    this->add_process(process);
}

/*
 * new_process(string, int) - create new process with path and nice
 */
void Process_Queue::new_process(std::string process_name, int how_nice)
{
    Process process(process_name, how_nice);
    this->add_process(process);
}

/*
 * new_process(string, int, string) - create new process with path,
 *                                    nice and args
 */
void Process_Queue::new_process(std::string process_name, int how_nice, std::string Args)
{
    Process process(process_name, how_nice, Args);
    this->add_process(process);
}
 
/*
 * add_process(Process) - add a process that already exist somewhere elst
 */         
void Process_Queue::add_process(Process new_process)
{
    this->processes.emplace_back(new_process);
    this->processes.sort();
}
        
/*
 * remove_process(Process) - remove a process by matching the process
 *                           directly
 */          
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
        
/*
 * remove_process(string) - remove a process by matching its path
 */          
void Process_Queue::remove_process(std::string process_data)
{    
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Scrollable_List_Data(false) == process_data)
        {
            this->processes.erase(process_itr);
            break;
        }
        process_itr++;
    }
}
         
/*
 * kill_process(string) - kill a process by matching its path
 */              
void Process_Queue::kill_process(std::string Process_Path)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Process_Path() == Process_Path)
        {
            kill(process_itr->Pid(), SIGUSR1);
        }
        process_itr++;
    }
}
        
/*
 * kill_process(string, string) - kill a process by matching its path
 *                                using the specified method
 */         
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
    else if(method == "SIGUSR1")
    {
        std::list<Process>::iterator process_itr = this->processes.begin();
    
        while(process_itr != this->processes.end())
        {
            if(process_itr->Process_Path() == Process_Path)
            {
                kill(process_itr->Pid(), SIGUSR1);
            }
            process_itr++;
        }
    }
    else
    {
        // don't kill anything
    } 
}
        
/*
 * kill_all_processes(string) - kill all processes using the 
 *                              specified method
 */ 
// etorw ehs redrum
void Process_Queue::kill_all_processes(std::string method)
{
    if(method == "SIGTERM")
    {
        std::list<Process>::iterator process_itr = this->processes.begin();
    
        while(process_itr != this->processes.end())
        {
            kill(process_itr->Pid(), SIGUSR1);
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
 
/*
 * run_process(string) - launches process tracker, which 
 *                       calls exec(Process_Path)
 */            
bool Process_Queue::run_process(std::string Process_Path)
{
   if(Process_Path.length() < 1)
   {
        return 1; // there were no running processes
   }
   
   char c;
   key_t key;
   std::string Args;
   int p1[2];
   int p2[2];
   int status;
   
   pipe(p1);
   pipe(p2);

   key = 2222;
   
   Args = this->Child_Args(Process_Path);
   
   std::string tracker = "process_tracker/process_tracker";
   
   pid_t parent_pid = getpid();
        
   char* args[5] = {&tracker[0], (char*)&key, &Process_Path[0], (char*)&parent_pid, &Args[0]};        

   pid_t pid = fork();
    
   if(pid == 0)
   {
      pid_t child_pid = fork();

      if(child_pid == 0)
      {
          char buffer[MSGSIZE];
          int fork_check = 999;
          write(p1[WRITE], "success", MSGSIZE);
          fork_check = execlp(args[0], args[0], args[1], args[2], args[3], (char*)NULL);
          read(p1[READ], buffer, MSGSIZE); // read "success" from the buffer to clear it
          write(p1[WRITE], "fail", MSGSIZE); // if we get here there was an error
          close(p1[WRITE]);
          exit(0); // we do not want this thread alive
      }
      else
      {
            write(p2[WRITE], (char*)&child_pid, MSGSIZE);
            exit(0); // gtks parent thread is waitpid'ing for this call
      }

   }
   else
   {
       waitpid(pid, &status, 0); // gtk must wait until the grandchild is execlp'd away
       char inbuf[MSGSIZE];   
       read(p1[READ], inbuf, MSGSIZE);     

       std::string buff = inbuf;

       if(buff == "fail")
       {
           this->Child_Status(Process_Path, "failed");
       }
       else
       {
           char inbuf[MSGSIZE];   
           read(p2[READ], inbuf, MSGSIZE);     
           int pipe_pid = *(int*)inbuf;
           
           this->Child_Status(Process_Path, "running");
           this->Child_Pid(Process_Path, pipe_pid);
       }

   }
   return 0;
}
        
/*
 * add_processes_to_lists(GtkWidget*, GtkWidget*) - split the processes
 *                                                  into scheduled/idle,
 *                                                  destroy the old list,
 *                                                  rebuild the list with 
 *                                                  our divided processes
 */         
void Process_Queue::add_processes_to_lists(GtkWidget *scheduled_list, GtkWidget *idle_list)
{
    GdkColor red;
    gdk_color_parse ("dark red", &red);
    
    GdkColor gray;
    gdk_color_parse ("gray", &gray);
        
    GdkColor blue;
    gdk_color_parse ("dark blue", &blue);
    
    GdkColor li_blue;
    gdk_color_parse ("light blue", &li_blue);

    GtkWidget *list_item;
    GtkWidget *label;
    
    gtk_container_foreach (GTK_CONTAINER (scheduled_list), (GtkCallback) gtk_widget_destroy, NULL);
    gtk_container_foreach (GTK_CONTAINER (idle_list), (GtkCallback) gtk_widget_destroy, NULL);
    
    this->processes.sort();
    
    std::list<Process>::iterator process_itr = this->processes.begin();
    while(process_itr != this->processes.end())
    {
        if(process_itr->Status() == "idle" || process_itr->Status() == "blocked")
        {
            label = gtk_label_new(process_itr->Scrollable_List_Data(false).c_str());
            gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
            gtk_widget_modify_font (label,pango_font_description_from_string ("Monospace"));
            if(process_itr->Status() == "blocked")
            {
                gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &red);
            }
            list_item = gtk_list_item_new();
            gtk_container_add(GTK_CONTAINER(list_item), label);
            gtk_container_add(GTK_CONTAINER(idle_list), list_item);
        }
        else
        {
            label = gtk_label_new(process_itr->Scrollable_List_Data(false).c_str());
            gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
            gtk_widget_modify_font (label,pango_font_description_from_string ("Monospace"));
            if(process_itr->Status() == "running")
            {
                gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &blue);
            }    
            else if(process_itr->Status() == "waiting")
            {
                gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &gray);
            }    
            else if(process_itr->Status() == "paused")
            {
                gtk_widget_modify_fg (label, GTK_STATE_NORMAL, &li_blue);
            }        
            list_item = gtk_list_item_new();
            gtk_container_add(GTK_CONTAINER(list_item), label);
            gtk_container_add(GTK_CONTAINER(scheduled_list), list_item);        
        }
        process_itr++;
    }
}
        
/*
 * schedule(string) - schedule an idle process
 *
 * button clicked : "Schedule"
 */          
void Process_Queue::schedule(std::string process_data)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->match_process(process_data, false))
        {
            if(process_itr->Status() != "blocked")
            {
                process_itr->Status("waiting");
            }
            else
            {
                // not happening!
            }
            break;
        }
        process_itr++;
    }
}
        
/*
 * deschedule(string) - deschedule a scheduled process
 *
 * button clicked : "Deschedule"
 */           
void Process_Queue::deschedule(std::string process_data)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->match_process(process_data, false))
        {
            if(process_itr->Status() != "running")
            {
                process_itr->Status("idle");
            }
        }
        process_itr++;
    }
}
        
/*
 * allow(string) - allow an idle process to be scheduled
 *
 * button clicked : "Allow"
 */         
void Process_Queue::allow(std::string process_data)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->match_process(process_data, false))
        {
                process_itr->Status("idle");
        }
        process_itr++;
    }
}
        
/*
 * block(string) - block an idle process from being scheduled
 *
 * button clicked : "Block"
 */           
void Process_Queue::block(std::string process_data)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->match_process(process_data, false))
        {
            process_itr->Status("blocked");
        }
        process_itr++;
    }
}
        
/*
 * pause_process(string) - pause/continue a running process,
 *                         calls SIGTSTP/SIGCONT respectively
 *
 * button clicked : "Pause"
 */            
void Process_Queue::pause_process(bool paused)
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
       if(process_itr->Status() == "running" && !paused)
       {
            process_itr->Status("paused");
            kill(process_itr->Pid(), SIGUSR2);
            break;
       }
       else if(process_itr->Status() == "paused" && paused)
       {
            process_itr->Status("running");
            kill(process_itr->Pid(), SIGUSR2);
            break;
       }
       process_itr++;
    }
}
        
/*
 * stop_process(string) - terminate a running or paused process
 *
 * button clicked : "Stop"
 */          
void Process_Queue::stop_process()
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
       if(process_itr->Status() == "running" || process_itr->Status() == "paused")
       {
            process_itr->Status("idle");
            kill(process_itr->Pid(), SIGUSR1);
            break;
       }
       process_itr++;
    }
}
        
/*
 * no_running_process() - checks for a running process
 */         
bool Process_Queue::no_running_process()
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {

       if(process_itr->Status() == "running" || process_itr->Status() == "paused")
       {
            return false;
       }
       process_itr++;
    }
    
    return true;
}
        
/*
 * next_up() - finds the next waiting process with highest priority
 */          
std::string Process_Queue::next_up()
{
    this->processes.sort();

    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Status() == "waiting" )
        {
            return process_itr->Process_Path();
        }
        process_itr++;
    }
    return "";
}
        
/*
 * done() - change the status of the current running process to idle
 */        
void Process_Queue::done()
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {

       if(process_itr->Status() == "running")
       {
            process_itr->Status("idle");
            break;
       }
       process_itr++;
    }
}
        
/*
 * Running_Process_Pid() - returns the Pid of the instance of 
 *                         process_tracker that is running the 
 *                         process 
 */        
pid_t Process_Queue::Running_Process_Pid()
{
    std::list<Process>::iterator process_itr = this->processes.begin();
    
    while(process_itr != this->processes.end())
    {
        if(process_itr->Status() == "running")
        {
            process_itr->Pid();
            break;
        }
        process_itr++;
    }
}
        
/*
 * load_processes_from_file() - allow user to load many processes at 
 *                              one time by specifying path, nice and args
 *                              in a text file, one line per process
 */        
void Process_Queue::load_processes_from_file(std::string File_Path)
{
    //TODO
}


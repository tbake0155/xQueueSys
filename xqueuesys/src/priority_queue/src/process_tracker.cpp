/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <X11/Xlib.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;
bool paused = false;

static void xqueuesys_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        kill(child_pid, SIGTERM);
    }
}

static void pause_handler(int signum)
{
    if (signum == SIGUSR2)
    {
        if(paused == false)
        {
            paused = true;
            kill(child_pid, SIGTSTP);
        }
        else
        {
            paused = false;
            kill(child_pid, SIGCONT);
        }
    }
}

int main(int argc, char** argv)
{
    XInitThreads(); // prevents errors due to multithreading with windows

    std::string Process_Path;
    std::string args;
    key_t key;
    pid_t parent_pid;

    if(argc < 4)
    {
        // exit with error status if an incorrect 
        // number of arguments is passed
        return 1;
    }   

    key = atoi(argv[1]);
    Process_Path = argv[2];
    parent_pid = atoi(argv[3]);
    Process_Path = Process_Path;
    
    int child_args = argc -4;  
    char **child_args[child_args];  
    
    for(int i=0; i<child_args; i++)
    {
        child_args[i] = argv[i + child_args];
    }

    // listen for xqueuesys to request clean termination
    signal(SIGUSR1, xqueuesys_handler);
    signal(SIGUSR2, pause_handler);

   // create another child process inside this child process
   child_pid = fork();
   
   int status;
        
   // child block
   if(child_pid == 0)
   {
       // execute process and allow this child to become the new process
       // "fly away little bird"
       if(argc == 4)
       {
            execlp(Process_Path.c_str(),Process_Path.c_str(), NULL);
       }
       else
       {
            execlp(Process_Path.c_str(),Process_Path.c_str(), child_args);
       }
       exit(0);
   }
   else
   {
       waitpid(child_pid, &status, 0);
       kill(parent_pid, SIGUSR1);
   }

    return 0;
}

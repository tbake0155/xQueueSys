
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <X11/Xlib.h>
#include <signal.h>
#include <sys/wait.h>

bool paused = false;
pid_t child_pid;

static void stop_handler(int signum)
{
    if(signum == SIGUSR1)
    {
        kill(child_pid, SIGTERM);
        kill(getpid(), SIGTERM);
    }
}

static void pause_handler(int signum)
{
    if (signum == SIGUSR2)
    {
        if(paused == false)
        {
            paused = true;
            kill(child_pid, SIGSTOP);
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
    key_t key;
    pid_t parent_pid;

    if(argc != 4)
    {
        // exit with error status if an incorrect 
        // number of arguments is passed
        return 1;
    }   

    key = atoi(argv[1]);
    Process_Path = argv[2];
    parent_pid = atoi(argv[3]);
    Process_Path = Process_Path;    
    
    signal(SIGUSR1, stop_handler);
    signal(SIGUSR2, pause_handler);

   // create another child process inside this child process
   child_pid = fork();
   
   int status;
        
   // child block
   if(child_pid == 0)
   {
       // execute process and allow this child to become the new process
       // "fly away little bird"
       execlp(Process_Path.c_str(),Process_Path.c_str(), NULL);
       exit(0);
   }
   else
   {
       waitpid(child_pid, &status, 0);
       kill(parent_pid, SIGUSR1);
   }

    return 0;
}

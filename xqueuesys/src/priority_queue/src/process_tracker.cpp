/*
 * process tracker - program to launch and track child processes for xqueuesys
 */

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>  
#include <sys/wait.h>  

pid_t child_pid; // the pid of the process to be exec()'d
pid_t parent_pid; // the pid of the xqueuesys process that called
bool paused = false; // keep track of the state of the child

static void xqueuesys_handler(int signum); // SIGUSR1 handler
static void pause_handler(int signum) //SIGUSR2 handler

/*
 * process_tracker main
 */
int main(int argc, char** argv)
{
    // xqueuesys will always pass at least 4 arguments
    if(argc < 4)
    {
        // exit with error status if an incorrect 
        // number of arguments is passed
        return 1;
    }   

    /* if more than 4 arguments was passed, assume a valid call */

    int status; // needed for waitpid(), not used
    key_t key = atoi(argv[1]);  // not used, for unimplemented shared memory
    std::string Process_Path = argv[2]; // path to the child process
    parent_pid = atoi(argv[3]); // xqueuesys's pid
    
    // get the user args
    int child_args = argc -4;  // number of args passed
    char **child_args[child_args]; // C string array to hold args
    
    // store args into the array
    for(int i=0; i<child_args; i++)
    {
        child_args[i] = argv[i + child_args];
    }

    // listen for xqueuesys to request clean termination
    signal(SIGUSR1, xqueuesys_handler);
    signal(SIGUSR2, pause_handler);

    // create child process
    child_pid = fork();
        
    // child block
    if(child_pid == 0)
    {
        // execute process and allow the child to become the new process
        // "fly away little bird"

        if(argc == 4) // no user args passed
        {
            execlp(Process_Path.c_str(),Process_Path.c_str(), NULL);
        }

        else // user args passed
        {
            execlp(Process_Path.c_str(),Process_Path.c_str(), child_args);
        }

        exit(0); // if we got here there was an error, destroy the thread
    }

    // parent block
    else
    {
        waitpid(child_pid, &status, 0); // wait for the child to terminate
        kill(parent_pid, SIGUSR1); // alert xqueuesys
    }

    return 0; // exit cleanly
}


/*
 * xqueuesys_handler - signal handler for SIGUSR1 signals
 *                     sent from xqueuesys to terminate the
 *                     child process. sends a SIGUSR1 back
 *                     to xqueuesys to alert terminatination
 *                     was successful.
 */
static void xqueuesys_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        kill(child_pid, SIGTERM); // terminate child
        kill(parent_pid, SIGUSR1); // alert xqueuesys
    }
}


/*
 * pause_handler - signal handler for SIGUSR2 signals sent
 *                 from xqueuesys.  if the child is paused,
 *                 the child is sent a SIGCONT signal to
 *                 continue processing.  if the child is
 *                 running, the child is sent a SIGTSTP 
 *                 signal.
 */
static void pause_handler(int signum)
{ 
    if (signum == SIGUSR2)
    {
        if(paused == false)
        {
            paused = true;
            kill(child_pid, SIGTSTP); // pause
        }
        else
        {
            paused = false;
            kill(child_pid, SIGCONT); // continue
        }
    }
}

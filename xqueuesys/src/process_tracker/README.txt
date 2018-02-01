Process_tracker is a helper program launched by xqueuesys to handle the launching of children processes.  Process_tracker is forked as a grand child
process of xqueuesys, and as such xqueuesys must be passed the pid of process_tracker by piping.  Process_tracker can only be killed by xqueuesys 
using signals.  This allows process_tracker to be controlled by xqueuesys without being a direct child (and therefore a completely separate process).

Process_tracker launches the specified process passed in by xqueuesys.  Process_tracker launches it's children as children, not as grandchildren, and as
such keeps direct control over the child process. It does use a fork() -> execlp() combination, so that the child process that is launched is not launched
inside a copy of process_tracker but as it's own process (execlp() will erase the instance of the process_tracker that calls it and rewrites the memory with
the data from the launched program).

Process_tracker and xqueuesys communicate by triggering SIGUSR1 and SIGUSR2 signals to each other.  The main reason for moving the process handling to a separate 
but reachable program was to allow the GTK window to remain interactive during the running of the process.  GTK runs best when it has an uninterrupted thread 
(the main program thread) to itself so that it can respond to callbacks effectively.  Process_tracker allows xqueuesys to remain in control of the scheduled
processes while also responding to callbacks during the running of the scheduled processes.

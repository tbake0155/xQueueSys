priority_qeueu folder contains the  source for the xqueuesys main program. xqueuesys is a gtk windowed application that primarily handles callbacks
due to button presses on the user interface. xqueuesys has a priority_queue (wrapper for std::list<Process>) of processes that it can launch by
passing the process information to the sister program process_tracker.

xqueuesys provides a priority queue dispatcher interface to the user.  The user can queue processes, which can be assigned a priority value (1-20,
1 being highest priority) or given the default priority value of 10. The processes will then run one at a time based on their priority.  The running
process can be paused and continued, or stopped altogether.  New idle processes can be added to the xqueuesys program during run time.  A process
must exist as an idle process in the xqueuesys program before xqueuesys can schedule the program for launching. 

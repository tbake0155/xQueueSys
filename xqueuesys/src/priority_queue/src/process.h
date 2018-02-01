/*
 * process.h - class declaration for Process object
 */

#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <iostream>

class Process
{

    private:

        int status_num;            // enumerate status for sorting

        int nice;                  // process priority

        pid_t pid;                 // process pid, only valid for a running process

        std::string process_path;  // path to executable

        std::string status;        // idle, waiting, running, blocked, failed

        std::string args;          // args to be passed when executing

	/*
	 * default contructor - not available
	 */
        Process(){} // can't touch this
      

    public:

	/*
	 * contructor - create process with path, nice and args
	 */
        Process(std::string Process_Path, int How_Nice, std::string args);

	/*
	 * contructor - create process with path and nice
	 */
        Process(std::string Process_Path, int How_Nice);

	/*
	 * contructor - create process with path only
	 */
        Process(std::string Process_Path);

	/*
	 * destructor 
	 */
        ~Process(){}

	/*
	 * Nice() - get value of nice
	 */
        int Nice(){return this->nice;}

	/*
	 * Nice(int) - set value of nice
	 */
        void Nice(int Nice){this->nice=Nice;}

	/*
	 * set_status_num() - set value of status num based on 
	 *                    current status
	 */
        void set_status_num();

	/*
	 * Pid() - get value of pid
	 */
        pid_t Pid(){return this->pid;}

	/*
	 * Pid(pid_t) - set value of pid
	 */
        void Pid(pid_t Pid){this->pid=Pid;}

	/*
	 * Process_Path() - get value of process_path
	 */
        std::string Process_Path(){return this->process_path;}

	/*
	 * Status() - get value of status
	 */
        std::string Status(){return this->status;}

	/*
	 * Status(string) - set value of status and status number
	 */
        void Status(std::string Child_Status){this->status=Child_Status; this->set_status_num();}

	/*
	 * Args() - get value of args
	 */
        std::string Args(){return this->args;}

	/*
	 * Args(string) - set value of args
	 */
        void Args(std::string Args){this->args=Args;}

	/*
	 * operator - equality operator
	 */
        bool operator==(Process const& other)const;

	/*
	 * operator - inequality operator
	 */
        bool operator!=(Process const& other)const;

	/*
	 * operator - less than operator
	 */
        bool operator<(Process const& other)const;

	/*
	 * path_to_name(string) - return process name from path
         *                        passed
	 */
        std::string path_to_name(std::string path); 

	/*
	 * path_to_name() - return process name from this processes's
         *                  path
	 */
        std::string path_to_name();

	/*
	 * Scrollable_List_Data(bool) - return formatted output for 
         *                              gtk_list_item's label. bool
	 *                              flag to include PID. 
	 */
        std::string Scrollable_List_Data(bool include_pid);

	/*
	 * match_process(string, bool) - match selected list_data
	 *                               against our list data. bool
         *                               flag indicates if PID is included.
	 */
        bool match_process(std::string process_data, bool include_pid);

};
#endif // PROCESS_H

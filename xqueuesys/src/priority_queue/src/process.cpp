#include "process.h"
#include <sstream> 
#include <string> 
#include <iostream>
#include <iomanip>

#define FAILED -1
#define BLOCKED 0
#define IDLE 1
#define WAITING 2
#define RUNNING 3

Process::Process(std::string Process_Path, int how_nice, std::string Args)
{
   this->process_path = Process_Path;
   this->status = "idle";
   this->status_num = IDLE;
   this->nice = how_nice;
   this->args = Args;
}

Process::Process(std::string Process_Path, int how_nice)
{
   this->process_path = Process_Path;
   this->status = "idle";
   this->status_num = IDLE;
   this->nice = how_nice;
}

Process::Process(std::string Process_Path)
{
   this->process_path = Process_Path;
   this->status = "idle";
   this->status_num = IDLE;
   this->nice = 10;
}

void Process::set_status_num()
{
    if(this->status == "idle")
    {
        this->status_num = IDLE;
    }
    else if(this->status == "blocked")
    {
        this->status_num = BLOCKED;
    }
    else if(this->status == "failed")
    {
        this->status_num = FAILED;
    }
    else if(this->status == "waiting")
    {
        this->status_num = WAITING;
    }
    else if(this->status == "running")
    {
        this->status_num = RUNNING;
    }
}

bool Process::operator<(Process const& other)const
{    
    if(this->status == other.status)
    {
        return this->nice < other.nice;
    }
    else
    {
        return this->status_num > other.status_num;
    }
}

bool Process::operator==(Process const& other)const
{
    if(this->status == other.status)
    {
        if(this->nice == other.nice)
        {
            if(this->process_path == other.process_path)
            {
                return true;
            }
        }
    }
    return false;
}

bool Process::operator!=(Process const& other)const
{
    return!(*this==other);
}

std::string Process::path_to_name(std::string path)
{   
    std::string name = path.substr(path.find_last_of("/") + 1);
    return name;
}

std::string Process::path_to_name()
{   
    std::string name = this->process_path.substr(this->process_path.find_last_of("/") + 1);
    return name;
}

std::string Process::Scrollable_List_Data(bool include_pid)
{
    std::stringstream formatted_label;
    formatted_label << "  " <<  std::setfill(' ') << std::setw(20) << std::left << this->path_to_name(this->process_path) << std::setw(9) << std::left << std::to_string(this->nice) << std::setw(8) << std::left << this->status;
    return formatted_label.str();
}

bool Process::match_process(std::string process_data, bool include_pid)
{
        std::stringstream formatted_label;
    formatted_label << "  " <<  std::setfill(' ') << std::setw(20) << std::left << this->path_to_name(this->process_path) << std::setw(9) << std::left << std::to_string(this->nice) << std::setw(8) << std::left << this->status;
    
        std::string match_data = formatted_label.str();
        
        if(match_data == process_data)
        {
            return true;
        }
        else
        {
            return false;
        }
}

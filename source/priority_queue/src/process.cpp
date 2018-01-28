#include "process.h"

Process::Process(std::string Process_Path, int how_nice)
{
   this->process_path = Process_Path;
   this->status = "idle";
   this->nice = how_nice;
}

Process::Process(std::string Process_Path)
{
   this->process_path = Process_Path;
   this->status = "idle";
   this->nice = 10;
}

std::string Process::path_to_name(std::string path)
{   
    std::string name = path; // TODO
    return name;
}

std::string Process::Scrollable_List_Data(bool include_pid)
{
    if(include_pid)
    {
        return this->path_to_name(this->process_path) + "\t" + std::to_string(this->pid) + "\t" + std::to_string(this->nice) + "\t" + this->status;
    }
    else
    {
        return this->path_to_name(this->process_path) + "\t" + std::to_string(this->nice) + "\t" + this->status;
    }
}

#include "process.h"

Process::Process(std::string Process_Path, int how_nice)
{
   this->process_path = Process_Path;
   this->nice = how_nice;
}

Process::Process(std::string Process_Path)
{
   this->process_path = Process_Path;
   this->nice = 10;
}

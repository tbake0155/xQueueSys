#include "xqueue.h"

void Xqueue::new_process(std::string process_name)
{
    this->pq.new_process(process_name);
}

void Xqueue::new_process(std::string process_name, int how_nice)
{
    this->pq.new_process(process_name, how_nice);
}

void Xqueue::kill_process(std::string process_name)
{
    this->pq.kill_process(process_name);
}

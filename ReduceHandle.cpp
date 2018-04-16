#include "ReduceHandle.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>

ReduceHandle::ReduceHandle()
{
}

void ReduceHandle::operator()(std::string line)
{
    stringsVector.emplace_back(std::move(line));
}

void ReduceHandle::save()
{
    std::ofstream file;
    std::stringstream ss;
    ss << std::this_thread::get_id();
    file.open(std::string("reduce_") + ss.str() + ".txt");
    ss.str() = "";
    std::for_each(stringsVector.begin(), stringsVector.end(), [&ss](std::string& line)
    {
        ss << line << "\n";
    });
    file << ss.str();
    file.close();
}

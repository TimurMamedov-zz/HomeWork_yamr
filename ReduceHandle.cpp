#include "ReduceHandle.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <atomic>

static std::atomic_size_t count{0};

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
    ss << count;
    count++;
    file.open(std::string("reduce_") + ss.str() + ".txt");
    ss.str(std::string());

    if(!stringsVector.empty())
    {
        auto last = stringsVector.end();
        last--;
        for(auto it = stringsVector.begin(); it != last; it++)
        {
            ss << *it << "\n";
        }
        ss << *last;
    }

    file << ss.str();
    file.close();
}

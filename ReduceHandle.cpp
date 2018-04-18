#include "ReduceHandle.h"
#include <fstream>
#include <algorithm>
#include <thread>
#include <atomic>

static std::atomic_size_t count{0};

ReduceHandle::ReduceHandle()
{
}

void ReduceHandle::operator()(std::string line)
{
    auto iterator = prefixHash.find(line.substr(0, minPrefix));
    if(iterator != prefixHash.end())
    {
        if(line.size() > minPrefix)
        {
            while(iterator != prefixHash.end())
            {
                minPrefix++;
                auto tempHash = prefixHash;
                prefixHash.clear();

                for(auto& pair : tempHash)
                {
                    prefixHash.emplace(pair.second.substr(0, minPrefix),
                                       pair.second);
                }
                iterator = prefixHash.find(line.substr(0, minPrefix));

                if(line.size() < minPrefix)
                    break;
            }
        }
    }
    prefixHash.emplace(line.substr(0, minPrefix), line);

    ss << line << "\n";
}

std::size_t ReduceHandle::save()
{
    std::ofstream file;
    file.open(std::string("reduce_") + std::to_string(count++) + ".txt");

    file << ss.str();
    file.close();
    ss.str(std::string());
    return minPrefix;
}

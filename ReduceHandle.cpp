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
    auto iterator = prefixHash.find(line.substr(0, minPrefix));
    if(iterator != prefixHash.end())
    {
        if(line.size() < minPrefix)
        {
            while(iterator != prefixHash.end())
            {
                minPrefix++;

                for(auto& pair : prefixHash)
                {
                    if(pair.first.size() < minPrefix)
                    {
                        auto tempLine = pair.second;
                        prefixHash.erase(pair.first);
                        prefixHash.emplace(tempLine.substr(0, minPrefix), tempLine);
                    }
                }
                iterator = prefixHash.find(line.substr(0, minPrefix));

                if(line.size() < minPrefix)
                    break;
            }
        }
    }
    else
        prefixHash.emplace(line.substr(0, minPrefix), line);


    stringsMultiset.emplace(std::move(line));
}

void ReduceHandle::save()
{
    std::ofstream file;
    std::stringstream ss;
    ss << count;
    count++;
    file.open(std::string("reduce_") + ss.str() + ".txt");
    ss.str(std::string());

    if(!stringsMultiset.empty())
    {
        auto last = stringsMultiset.end();
        last--;
        for(auto it = stringsMultiset.begin(); it != last; it++)
        {
            ss << *it << "\n";
        }
        ss << *last;
    }

    file << ss.str();
    file.close();
}

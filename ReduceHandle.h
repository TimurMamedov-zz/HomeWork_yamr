/*!
\file
\brief
*/
#pragma once
#include <tuple>
#include <string>
#include <vector>

class ReduceHandle
{
public:
    ReduceHandle() = default;
    ReduceHandle(const ReduceHandle&){}
    ReduceHandle(ReduceHandle&& ) = default;
    std::size_t operator()(const std::string& line)
    {
        thread_local static std::string prevStr;
        thread_local static std::size_t minPrefix = 1;

        if(first)
        {
            if(prevStr == line)
            {
                auto currMinPrefix = line.size() + 1;
                if(currMinPrefix > minPrefix)
                    minPrefix = currMinPrefix;
            }
            prevStr = line;
        }
        else
            first = true;
        prevStr = line;

        return minPrefix;
    }

private:
    bool first = false;
};


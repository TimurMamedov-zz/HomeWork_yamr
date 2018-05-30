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
    std::tuple<bool, std::string> operator()(const std::string& line)
    {
        thread_local static std::string prevStr;
        if(first)
        {
            if(prevStr == line)
            {
                return std::make_tuple(true, prevStr);
            }
            prevStr = line;
            return std::make_tuple(false, prevStr);
        }
        else
            first = true;
        prevStr = line;
        return std::make_tuple(false, prevStr);
    }

private:
    bool first = false;
};


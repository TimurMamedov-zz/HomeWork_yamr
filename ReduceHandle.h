/*!
\file
\brief
*/
#pragma once
#include <set>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

class ReduceHandle
{
public:
    ReduceHandle() = default;
    ReduceHandle(const ReduceHandle&){}
    ReduceHandle(ReduceHandle&& ) = default;
    std::string operator()(std::vector<std::string> MapResult)
    {

    }

//    std::size_t save();

private:
    std::stringstream ss;
    std::unordered_map<std::string, std::string> prefixHash;
    std::size_t minPrefix = 1;
};


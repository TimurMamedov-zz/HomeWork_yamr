/*!
\file
\brief
*/
#pragma once
#include <set>
#include <string>
#include <unordered_map>
#include <sstream>

class ReduceHandle
{
public:
    ReduceHandle() = default;
    ReduceHandle(const ReduceHandle&reduceHandle);
    ReduceHandle(ReduceHandle&& ) = default;
    std::string operator()(std::string line);
//    std::size_t save();

private:
    std::stringstream ss;
    std::unordered_map<std::string, std::string> prefixHash;
    std::size_t minPrefix = 1;
};


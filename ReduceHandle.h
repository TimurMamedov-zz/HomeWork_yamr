/*!
\file
\brief
*/
#pragma once
#include <set>
#include <string>
#include <unordered_map>

class ReduceHandle
{
public:
    ReduceHandle();
    void operator()(std::string line);
    void save();
private:
    std::multiset<std::string> stringsMultiset;
    std::unordered_map<std::string, std::string> prefixHash;
    std::size_t minPrefix = 1;
};


/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <string>

class ReduceHandle
{
public:
    ReduceHandle();
    void operator()(std::string line);
    void save();
private:
    std::vector<std::string> stringsVector;
};


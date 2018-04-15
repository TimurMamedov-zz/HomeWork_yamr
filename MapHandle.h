/*!
\file
\brief
*/
#pragma once
#include <set>
#include <string>

class MapHandle
{
public:
    MapHandle();
    void operator()(std::string line);
    std::multiset<std::string> getSortedContainer() const;
private:
    std::multiset<std::string> multisetStrings;
};


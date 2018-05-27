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
    MapHandle() = default;
    MapHandle(const MapHandle&) = default;
    MapHandle(MapHandle&&) = default;
    std::string operator()(std::string line);
//    std::multiset<std::string> getSortedContainer() const;

//private:
//    std::multiset<std::string> multisetStrings;
};


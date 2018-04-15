#include "MapHandle.h"

MapHandle::MapHandle()
{
}

void MapHandle::operator()(std::string line)
{
    multisetStrings.emplace(std::move(line));
}

std::multiset<std::string> MapHandle::getSortedContainer() const
{
    return multisetStrings;
}

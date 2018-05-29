/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <string>

class MapHandle
{
public:
    MapHandle() = default;
    MapHandle(const MapHandle&) = default;
    MapHandle(MapHandle&&) = default;

    std::vector<std::string> operator()(const std::string& line)
    {
        std::vector<std::string> MapHandleResult;
        for(auto i = std::size_t{0}; i < line.size(); i++)
        {
            MapHandleResult.emplace_back(line.substr(0, i+1));
        }
        std::sort(MapHandleResult.begin(), MapHandleResult.end());
        return MapHandleResult;
    }
};


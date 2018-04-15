/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <fstream>
#include <functional>
#include <set>

class Mapping
{
public:
    Mapping(std::string path_,
            std::vector<std::size_t> pos_vec_);
    std::vector<std::multiset<std::string> > getSortedContainers() const;
    void Map();
    void deleteContainers();

private:
    const std::string path;
    const std::vector<std::size_t> pos_vec;

    std::vector<std::multiset<std::string> > multisetVector;
};


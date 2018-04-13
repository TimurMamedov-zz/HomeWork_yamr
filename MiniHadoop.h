/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <fstream>
#include "MapReduce.h"

class MiniHadoop
{
public:
    MiniHadoop(std::ifstream& in,
               std::vector<std::size_t> pos_vec);

private:
    MapReduce mapReduce;
};


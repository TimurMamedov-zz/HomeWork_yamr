/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <fstream>
#include <functional>
#include "Mapping.h"
#include "Reduce.h"

class MiniHadoop
{
public:
    MiniHadoop(std::string path,
               std::vector<std::size_t> pos_vec,
               int rnum);

    void MapReduce();

private:
    Mapping mapping;
    Reduce reduce;
    std::vector<std::multiset<std::string> > MapFunc();
    void ReduceFunc(std::vector<std::multiset<std::string> > sortedContainers);
};


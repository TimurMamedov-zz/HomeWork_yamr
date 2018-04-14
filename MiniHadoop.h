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
               int nnum_,
               std::function<void()> mapHandle,
               std::function<void()> reduceHandle);

private:
    const int nnum;
    Mapping mapping;
    Reduce reduce;
};


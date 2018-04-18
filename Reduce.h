/*!
\file
\brief
*/
#pragma once
#include <vector>
#include "threadsafe_multiset.h"
#include <string>

class Reduce
{
public:
    Reduce(int rnum_);
    void addString(std::string line);

    std::size_t reduce();

private:
    const int rnum;
    std::vector<ThreadSave_MultiSet<std::string> > multisetVector;
    std::hash<std::string> hash_fn;

    std::mutex coutMutex;//delete!
};


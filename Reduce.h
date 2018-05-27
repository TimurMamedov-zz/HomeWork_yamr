/*!
\file
\brief
*/
#pragma once
#include <vector>
#include "threadsafe_multiset.h"
#include <string>

template<typename ReduceRes>
class Reduce
{
public:
    Reduce(const int rnum_, std::function<ReduceRes(std::string)> ReduceHandle_)
        :rnum(rnum_), ReduceHandle(std::move(ReduceHandle_))
    {
    }
    void addString(std::string line)
    {

    }

    void reduce()
    {

    }

private:
    std::function<ReduceRes(std::string)> ReduceHandle;
    const int rnum;
//    std::vector<ThreadSave_MultiSet<std::string> > multisetVector;
    std::hash<std::string> hash_fn;

//    std::mutex coutMutex;//delete!
};


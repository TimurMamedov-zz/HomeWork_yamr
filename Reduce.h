/*!
\file
\brief
*/
#pragma once
#include <vector>
#include "threadsafe_multiset.h"
#include <string>
#include <future>
#include <algorithm>

template<typename ReduceRes, typename MapRes>
class Reduce
{
public:
    Reduce(const int rnum_, std::function<ReduceRes(MapRes)> ReduceHandle_)
        :rnum(rnum_), ReduceHandle(std::move(ReduceHandle_))
    {
        ShuffleResult.reserve(rnum);
    }

    void shuffle( std::vector<std::vector<MapRes>>&& MapResult )
    {
        for(auto i = std::size_t{0}; i < MapResult.size(); ++i)
        {
//            ShuffleResult[]
        }

        std::for_each(MapResult.begin(), MapResult.end(),
                      [this, &futuresVector](std::vector<MapRes>& Container)
        {
            futuresVector.emplace_back(std::async(std::launch::async,
                                                  [this, &Container]()
            {
                for(auto&& mapRes : Container)
                {
                    reduce.addString(line);
                }
                Container.clear();
            }));
        });
    }

    void reduce()
    {

    }

private:
    std::function<ReduceRes(MapRes)> ReduceHandle;
    const int rnum;
    std::vector<std::vector<MapRes>> ShuffleResult;
//    std::vector<ThreadSave_MultiSet<std::string> > multisetVector;
    std::hash<std::string> hash_fn;

//    std::mutex coutMutex;//delete!
};


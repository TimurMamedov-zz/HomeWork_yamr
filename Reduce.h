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

static std::size_t count = 0;

template<typename ReduceRes>
class Reduce
{
public:
    Reduce(const int rnum_,
           std::function<ReduceRes(const std::string&)>&& ReduceHandle_,
           std::function<void(std::ofstream &, const ReduceRes&)>&& ReduceSaveFunc_)
        :rnum(rnum_),
          ReduceHandle(std::move(ReduceHandle_)),
          ReduceSaveFunc(std::move(ReduceSaveFunc_))
    {
    }

    void shuffle(std::vector<std::vector<std::string>>&& MapResult)
    {
        std::vector<std::future<void>> futuresVector;
        multisetVector.resize(rnum);

        std::for_each(MapResult.begin(), MapResult.end(),
                      [this, &futuresVector](std::vector<std::string>& strings)
        {
            futuresVector.emplace_back(std::async(std::launch::async,
                                                  [this, &strings]()
            {
                for(auto&& line : strings)
                {
                    multisetVector[hash_fn(line)%rnum].push(line);
                }
                strings.clear();
            }));
        });

        for(auto&& future : futuresVector)
        {
            future.get();
        }
    }

    void reduce()
    {
        std::vector<std::future<void> > futuresVector;
        futuresVector.resize(rnum);
        for(auto i = std::size_t{0}; i < rnum; i++)
        {
            auto& multiset = multisetVector[i].getNonThreadSave_MultiSet();

            futuresVector[i] = std::async(std::launch::async,
                                                  [this,  &multiset]()
            {
                if(!multiset.empty())
                {
                    auto last = --multiset.end();
                    for(auto it = multiset.begin(); it != last; ++it)
                    {
                        ReduceHandle(*it);
                    }
                    auto&& temp = ReduceHandle(*last);
                    std::ofstream file;
                    file.open(std::string("reduce_") + std::to_string(count++) + ".txt");
                    ReduceSaveFunc(file, temp);
                    file.close();
                }
            });
        }

        for(auto&& future : futuresVector)
        {
            future.get();
        }
    }

private:
    std::function<ReduceRes(const std::string&)> ReduceHandle;
    std::function<void(std::ofstream &, const ReduceRes&)> ReduceSaveFunc;
    const int rnum;
    std::vector<ThreadSave_MultiSet<std::string> > multisetVector;
    std::hash<std::string> hash_fn;

    std::mutex coutMutex;
};


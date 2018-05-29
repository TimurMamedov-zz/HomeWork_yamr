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
           std::function<void(std::vector<std::string>&, const ReduceRes&, std::size_t&)>&& ReduceGetFunc_)
        :rnum(rnum_),
          ReduceHandle(std::move(ReduceHandle_)),
          ReduceGetFunc(std::move(ReduceGetFunc_)),
          multisetVector(rnum)
    {
    }

    void shuffle(std::vector<std::vector<std::string>>&& MapResult)
    {
        std::vector<std::future<void>> futuresVector;

        std::for_each(MapResult.begin(), MapResult.end(),
                      [this, &futuresVector](std::vector<std::string>& strings)
        {
            futuresVector.emplace_back(std::async(std::launch::async,
                                                  [this, &strings]()
            {
                for(auto& line : strings)
                {
                    multisetVector[hash_fn(line)%rnum].push(line);
                }
                strings.clear();
            }));
        });

        for(auto& future : futuresVector)
        {
            future.get();
        }
    }

    void reduce()
    {
        std::vector<std::future<void> > futuresVector;
        futuresVector.reserve(rnum);
        for(auto i = std::size_t{0}; i < rnum; i++)
        {
            auto& multiset = multisetVector[i].getNonThreadSave_MultiSet();

            futuresVector.emplace_back(std::async(std::launch::async,
                                                  [this,  multiset]()
            {
                std::vector<std::string> temp;
                std::size_t minPrefix = 1;
                for(auto& line : multiset)
                {
                    ReduceGetFunc(temp, ReduceHandle(line), minPrefix);
                }
                std::ofstream file;
                file.open(std::string("reduce_") + std::to_string(count++) + ".txt");
                for(auto&& line : temp)
                    file << line << "\n";
                file.close();

                std::lock_guard<std::mutex> lk(coutMutex);
                std::cout << minPrefix << " ";
            }));
        }
    }

private:
    std::function<ReduceRes(const std::string&)> ReduceHandle;
    std::function<void(std::vector<std::string>&, const ReduceRes&, std::size_t&)> ReduceGetFunc;
    const int rnum;
    std::vector<ThreadSave_MultiSet<std::string> > multisetVector;
    std::hash<std::string> hash_fn;

    std::mutex coutMutex;
};


#include "Reduce.h"
#include <iostream>
#include <future>
#include <algorithm>
#include "ReduceHandle.h"

Reduce::Reduce(int rnum_)
    :rnum(rnum_), multisetVector(rnum_)
{
}

void Reduce::addString(std::string line)
{
    multisetVector[hash_fn(line)%rnum].push(line);
}

void Reduce::reduce()
{
    std::vector<std::future<void>> futuresVector;
    futuresVector.reserve(rnum);
    for(auto i = std::size_t{0}; i < rnum; i++)
    {
        auto& multiset = multisetVector[i].getNonThreadSave_MultiSet();
//        using item_type = std::multiset<std::string>::value_type;
//        std::for_each(multiset.begin(), multiset.end(), [this](const item_type& item)
//        {
//            std::cout << item << std::endl;
//        });
//        std::cout << std::endl << std::endl;
        futuresVector.emplace_back(std::async([this,  multiset]()
        {
//            using item_type = std::multiset<std::string>::value_type;
//            std::for_each(multiset.begin(), multiset.end(), [this](const item_type& item)
//            {
//                std::cout << item << std::endl;
//            });
            if(!multiset.empty())
            {
                ReduceHandle reduceHandle;
                for(auto& line : multiset)
                {
                    reduceHandle(line);
                }
//                using item_type = std::multiset<std::string>::value_type;
//                std::for_each(multiset.begin(), multiset.end(), [this, &reduceHandle](const item_type& item)
//                {
//                    reduceHandle(item);
//                });
                reduceHandle.save();
            }
        }));
    }

    for(auto& future : futuresVector)
        future.get();
}



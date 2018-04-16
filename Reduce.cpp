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
/*    std::vector<std::future<void>> futuresVector;
    futuresVector.reserve(rnum);
    for(auto i = std::size_t{0}; i < rnum; i++)
    {
        auto& multiset = multisetVector[i].getNonThreadSave_MultiSet();
        futuresVector.emplace_back(std::async([this,  &multiset]()
        {
            if(!multiset.empty())
            {
                ReduceHandle reduceHandle;
                using item_type = std::multiset<std::string>::value_type;
                std::for_each(multiset.begin(), multiset.end(), [this, &reduceHandle](const item_type& item)
                {
//                    reduceHandle(item);
                });
//                reduceHandle.save();
            }
//            std::ifstream in(path, std::ios::binary | std::ios::ate);
//            in.seekg(pos_vec[begin], std::ios_base::beg);
//            MapHandle mapHandle;
//            while(in.tellg() < pos_vec[end])
//            {
//                std::string line;
//                std::getline(in, line);
//                mapHandle(std::move(line));
//            }
//            in.close();
//            return mapHandle.getSortedContainer();
        }));
    }

    for(auto& future : futuresVector)
        future.get();
    std::cout << "after future\n";*/
}



//#include "Reduce.h"
//#include <iostream>
//#include <future>
//#include <algorithm>
//#include <queue>

//template<typename ReduceRes>
//Reduce<ReduceRes>::Reduce(const int rnum_,
//               std::function<ReduceRes(std::string)> ReduceHandle_)

//{
//}

//template<typename ReduceRes>
//void Reduce<ReduceRes>::addString(std::string line)
//{
//    multisetVector[hash_fn(line.substr(0, 1))%rnum].push(line);
//}

//template<typename ReduceRes>
//void Reduce<ReduceRes>::reduce()
//{
//    std::vector<std::future<std::size_t> > futuresVector;
//    futuresVector.reserve(rnum);
//    for(auto i = std::size_t{0}; i < rnum; i++)
//    {
//        auto& multiset = multisetVector[i].getNonThreadSave_MultiSet();

//        futuresVector.emplace_back(std::async(std::launch::async,
//                                              [this,  multiset]()
//        {
//            ReduceHandle reduceHandle;
//            for(auto& line : multiset)
//            {
//                reduceHandle(line);
//            }
//            return reduceHandle.save();
//        }));
//    }

//    std::priority_queue<std::size_t> prefixesQueue;
//    for(auto& future : futuresVector)
//        prefixesQueue.emplace(future.get());

//    return prefixesQueue.top();
//}



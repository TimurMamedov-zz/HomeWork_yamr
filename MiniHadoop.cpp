//#include "MiniHadoop.h"
//#include <iostream>
//#include <algorithm>
//#include <future>

//template<typename MapRes, typename ReduceRes>
//MiniHadoop<MapRes, ReduceRes>::MiniHadoop(std::string&& path,
//                       std::vector<std::size_t>&& pos_vec,
//                       const int rnum,
//                       std::function<MapRes(std::string)> MapHandle_,
//                       std::function<ReduceRes(std::string)> ReduceHandle_)

//{
//}

//template<typename MapRes, typename ReduceRes>
//std::vector<MapRes> MiniHadoop<MapRes, ReduceRes>::MapFunc()
//{
//    std::vector<MapRes> result;
//    mapping.Map();
//    auto sortedContainers = mapping.getSortedContainers();
//    mapping.deleteContainers();

//    return result;
//}

//template<typename MapRes, typename ReduceRes>
//void MiniHadoop<MapRes, ReduceRes>::ReduceFunc(std::vector<MapRes> &&MapResult)
//{
//    using Container_type = decltype(sortedContainers.front());
//    std::vector<std::future<void>> futuresVector;
//    futuresVector.reserve(sortedContainers.size());

//    std::for_each(sortedContainers.begin(), sortedContainers.end(),
//                  [this, &futuresVector](Container_type& Container)
//    {
//        futuresVector.emplace_back(std::async(std::launch::async,
//                                              [this, &Container]()
//        {
//            for(auto& line : Container)
//            {
//                reduce.addString(line);
//            }
//            Container.clear();
//        }));
//    });

//    for(auto& future : futuresVector)
//    {
//        future.get();
//    }

//    std::cout << "Min prefix = " << reduce.reduce() << std::endl;
//}

//template<typename MapRes, typename ReduceRes>
//void MiniHadoop<MapRes, ReduceRes>::MapReduce()
//{

//}

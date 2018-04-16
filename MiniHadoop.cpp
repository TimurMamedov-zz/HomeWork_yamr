#include "MiniHadoop.h"
#include <iostream>
#include <algorithm>
#include <future>

MiniHadoop::MiniHadoop(std::string path,
                       std::vector<std::size_t> pos_vec,
                       int rnum)
    :mapping(std::move(path), std::move(pos_vec)),
      reduce(rnum)
{
}

void MiniHadoop::MapReduce()
{
    mapping.Map();
    auto sortedContainers = mapping.getSortedContainers();
    mapping.deleteContainers();


    using Container_type = decltype(sortedContainers.front());
    std::vector<std::future<void>> futuresVector;
    futuresVector.reserve(sortedContainers.size());
    std::for_each(sortedContainers.begin(), sortedContainers.end(),[this, &futuresVector](Container_type& Container)
    {
        futuresVector.emplace_back(std::async([this, &Container]()
        {
            for(auto& line : Container)
            {
                reduce.addString(line);
            }
            Container.clear();
        }));
    });

    for(auto& future : futuresVector)
    {
        future.get();
    }

    reduce.reduce();
}

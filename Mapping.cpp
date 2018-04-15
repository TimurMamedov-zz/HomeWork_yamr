#include "Mapping.h"
#include <iostream>
#include <future>
#include <algorithm>
#include "MapHandle.h"

Mapping::Mapping(std::string path_,
                 std::vector<std::size_t> pos_vec_)
    :path(std::move(path_)), pos_vec(pos_vec_)
{
    if(!pos_vec.empty())
    {
        multisetVector.reserve(pos_vec.size() - 1);
//        std::ifstream in(path, std::ios::binary | std::ios::ate);

//        if(in.is_open())
//        {
//            in.clear();
//            in.seekg(0, std::ios_base::beg);
//            for(auto i = std::size_t{0}; i < pos_vec.size(); i++)
//            {
//                if(i + 1 < pos_vec.size())
//                {
//                    std::string str;
//                    auto size = pos_vec[i+1] - pos_vec[i];
//                    str.resize(size);
//                    in.read(&str[0], size);
//                    std::cout << str << std::endl << std::endl;
//                }
//            }
//        }
    }
}


std::vector<std::multiset<std::string> > Mapping::getSortedContainers() const
{
    return multisetVector;
}

void Mapping::deleteContainers()
{
    multisetVector.clear();
}

void Mapping::Map()
{
    if(!pos_vec.empty())
    {
        std::vector<std::future<std::multiset<std::string>>> futuresVector;
        futuresVector.reserve(pos_vec.size() - 1);
        for(auto i = std::size_t{0}; i < pos_vec.size(); i++)
        {
            if(i + 1 < pos_vec.size())
            {
                auto begin = i;
                auto end = i + 1;
                futuresVector.emplace_back(std::async([this, begin, end]()
                {
                    std::ifstream in(path, std::ios::binary | std::ios::ate);
                    in.seekg(pos_vec[begin], std::ios_base::beg);
                    MapHandle mapHandle;
                    while(in.tellg() < pos_vec[end])
                    {
                        std::string line;
                        std::getline(in, line);
                        mapHandle(std::move(line));
                    }
                    in.close();
                    return mapHandle.getSortedContainer();
                }));
            }
        }

        using item_type = decltype(futuresVector.front());
        std::for_each(futuresVector.begin(), futuresVector.end(), [this](item_type& item)
        {
            multisetVector.emplace_back(item.get());
        });
    }
}

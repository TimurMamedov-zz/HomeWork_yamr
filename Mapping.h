/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <fstream>
#include <functional>
#include <future>
#include <algorithm>

#include <mutex>

template<typename MapRes>
class Mapping
{
public:
    Mapping(std::string path_,
            std::vector<std::size_t> pos_vec_,
            std::function<MapRes(std::string)>&& MapHandle_)
        :path(std::move(path_)), pos_vec(pos_vec_), MapHandle(MapHandle_)
    {

    }

    std::vector<std::vector<MapRes>> Map()
    {
        std::vector<std::vector<MapRes>> mapResult;

        if(!pos_vec.empty())
        {
            std::vector<std::future<std::vector<MapRes>>> futuresVector;

            for(auto i = std::size_t{0}; i < pos_vec.size(); i++)
            {
                if(i + 1 < pos_vec.size())
                {
                    auto begin = i;
                    auto end = i + 1;
                    futuresVector.emplace_back(std::async(std::launch::async,
                                                          [this, begin, end]()
                    {
                        std::ifstream in(path, std::ios::binary | std::ios::ate);
                        in.seekg(pos_vec[begin], std::ios_base::beg);
                        std::vector<MapRes> temp;
                        while(in.tellg() < pos_vec[end])
                        {
                            std::string line;
                            std::getline(in, line);
                            temp.emplace_back(MapHandle(std::move(line)));
                        }
                        in.close();
                        return temp;
                    }));
                }
            }

            for(auto& future : futuresVector)
            {
                mapResult.emplace_back(future.get());
            }
        }

        return mapResult;
    }

private:
    std::function<MapRes(std::string)> MapHandle;
    const std::string path;
    const std::vector<std::size_t> pos_vec;

//    std::mutex coutMutex;

//    std::vector<std::multiset<std::string> > multisetVector;
};


/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <fstream>
#include <functional>
#include "Mapping.h"
#include "Reduce.h"

template<typename MapRes, typename ReduceRes>
class MiniHadoop
{
public:
    MiniHadoop(std::string&& path,
               std::vector<std::size_t>&& pos_vec,
               const int rnum,
               std::function<MapRes(const std::string&)>&& MapHandle_,
               std::function<ReduceRes(const std::string&)>&& ReduceHandle_,
               std::function<void(std::vector<std::string>&, const MapRes&)>&& MapGetFunc_,
               std::function<void(std::ofstream &, const ReduceRes&)>&& ReduceSaveFunc_)
        :mapping(std::move(path), std::move(pos_vec), std::move(MapHandle_), std::move(MapGetFunc_)),
          reduce(rnum, std::move(ReduceHandle_), std::move(ReduceSaveFunc_))
    {
    }

    void MapReduce()
    {
        reduce.shuffle(mapping.Map());
        reduce.reduce();
    }

private:
    Mapping<MapRes> mapping;
    Reduce<ReduceRes> reduce;
};


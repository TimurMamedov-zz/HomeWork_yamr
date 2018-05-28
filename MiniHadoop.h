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
               std::function<MapRes(std::string)>&& MapHandle_,
               std::function<ReduceRes(MapRes)>&& ReduceHandle_,
               std::function<bool(const MapRes&, const MapRes&)>&& MapSortFunc_)
        :mapping(std::move(path), std::move(pos_vec), std::move(MapHandle_), std::move(MapSortFunc_)),
          reduce(rnum, std::move(ReduceHandle_))
    {
    }

    void MapReduce()
    {
        reduce.shuffle(mapping.Map());
        reduce.reduce();
//        ReduceFunc(std::move(MapFunc()));
    }

private:
    Mapping<MapRes> mapping;
    Reduce<ReduceRes, MapRes> reduce;

//    std::vector<MapRes> MapFunc()
//    {
//        std::vector<MapRes> mapResult = mapping.Map();
//        return mapResult;
//    }

//    void ReduceFunc(std::vector<MapRes>&& MapResult)
//    {
//        reduce.reduce(std::move(MapResult));
//    }
};


#include "MiniHadoop.h"
#include <iostream>

MiniHadoop::MiniHadoop(std::string path,
                       std::vector<std::size_t> pos_vec,
                       int nnum_,
                       std::function<void()> mapHandle,
                       std::function<void()> reduceHandle)
    :nnum(nnum_), mapping(mapHandle), reduce(reduceHandle)
{
    std::ifstream in(path, std::ios::binary | std::ios::ate);

    if(in.is_open())
    {
        in.clear();
        in.seekg(0, std::ios_base::beg);
        for(auto i = std::size_t{0}; i < pos_vec.size(); i++)
        {
            if(i + 1 < pos_vec.size())
            {
                std::string str;
                auto size = pos_vec[i+1] - pos_vec[i];
                str.resize(size);
                in.read(&str[0], size);
                std::cout << str << std::endl << std::endl;
            }
        }
    }
}

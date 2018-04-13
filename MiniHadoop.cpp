#include "MiniHadoop.h"
#include <iostream>

MiniHadoop::MiniHadoop(std::ifstream& in,
                       std::vector<std::size_t> pos_vec)
{
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
    in.close();
}

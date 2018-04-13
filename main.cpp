#include <iostream>
#include <fstream>
#include <vector>
#include "MiniHadoop.h"

int main(int argc, char *argv[])
{
    try
    {
//        if (argc != 4)
//        {
//            std::cerr << "Usage:  yamr <src> <mnum> <rnum>\n";
//            return 1;
//        }
//        std::ifstream in(argv[1], std::ios::binary | std::ios::ate);
        std::string src = "emails.txt";
        std::ifstream in(src, std::ios::binary | std::ios::ate);
//        auto mnum = std::atoi(argv[2]);
//        if(mnum > 0 && rnum > 0)
//        {

//        }
        auto mnum = std::size_t{7};
        auto endPos = in.tellg();

        in.clear();
        in.seekg(0, std::ios_base::beg);

        auto part = endPos/mnum;
        std::vector<std::size_t> pos_vec;
        pos_vec.emplace_back(0);

        auto newPos = part;

        for(auto i = std::size_t{0}; i < mnum; i++)
        {
            in.seekg(part, std::ios_base::cur);
            if(in.tellg() < endPos)
            {
                char c = in.peek();
                while(c != '\n' && in.tellg() != -1)
                {
                    c = in.get();
                }
                newPos = in.tellg();
            }
            else
                newPos = endPos;

            if(pos_vec[pos_vec.size() - 1] == endPos)
                break;

            if(newPos != -1)
                pos_vec.emplace_back(newPos);
            else
                pos_vec.emplace_back(endPos);

            newPos += part;
        }
//


//        for(auto i = std::size_t{0}; i < pos_vec.size(); i++)
//        {
//            if(i + 1 < pos_vec.size())
//            {
//                std::string str;
//                auto size = pos_vec[i+1] - pos_vec[i];
//                str.resize(size);
//                in.read(&str[0], size);
//                std::cout << str << std::endl << std::endl;
//            }
//        }

//        for(auto& item : pos_vec)
//            std::cout << "item: " << item << std::endl;
//        std::cout << "size: " << pos_vec.size() << std::endl;
        in.clear();
        in.seekg(0, std::ios_base::beg);

        MiniHadoop hadoop(in, std::move(pos_vec));
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

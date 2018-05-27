#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <type_traits>
#include "MiniHadoop.h"
#include "MapHandle.h"
#include "ReduceHandle.h"

void moveBack(std::vector<std::size_t>& pos_vec,
              std::ifstream& in)
{
    while(in.peek() != '\n' &&
          in.tellg() > pos_vec[pos_vec.size() - 1])
    {
        in.unget();
    }
    if(in.peek() == '\n')
        in.get();
}

void moveForward(std::ifstream& in)
{
    while(in.peek() != '\n' && in.tellg() != -1)
    {
        in.get();
    }
    in.get();
}

void moveBeforeNewLine(std::ifstream& in,
                       std::vector<std::size_t>& pos_vec)
{
    moveBack(pos_vec, in);
    if(pos_vec[pos_vec.size() - 1] >= in.tellg())
    {
        moveForward(in);
    }
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 4)
        {
            std::cerr << "Usage:  yamr <src> <mnum> <rnum>\n";
            return 1;
        }

        std::string src(argv[1]);
        std::ifstream in(src, std::ios::binary | std::ios::ate);
        if(in.is_open())
        {
            auto mnum = std::atoi(argv[2]);
            auto rnum = std::atoi(argv[3]);

            if(mnum > 0 && rnum > 0)
            {
                int endPos = in.tellg();
                in.clear();
                in.seekg(0, std::ios_base::beg);

                int part = endPos/mnum;

                std::vector<std::size_t> pos_vec;
                pos_vec.emplace_back(0);

                auto newPos = part;

                for(auto i = int{0}; i < mnum; i++)
                {
                    part = (endPos - pos_vec[pos_vec.size() - 1])/ (mnum - i);

                    in.seekg(part, std::ios_base::cur);

                    if(in.tellg() < endPos)
                    {
                        moveBeforeNewLine(in, pos_vec);
                        newPos = in.tellg();
                    }
                    else
                        break;

                    if(pos_vec[pos_vec.size() - 1] == endPos)
                        break;

                    if(newPos != -1)
                        pos_vec.emplace_back(newPos);
                    else
                        break;

                    newPos += part;
                }

                if(pos_vec[pos_vec.size() - 1] != endPos)
                {
                    pos_vec.emplace_back(endPos);
                }
                in.close();

//                auto mapHandle = [](std::string str){return std::string{"3r32"};};
//                auto reduceHandle = [](std::string str){return std::string{"3r32"};};

                MiniHadoop<std::result_of<MapHandle(std::string)>::type,
                        std::result_of<ReduceHandle(std::result_of<MapHandle(std::string)>::type)>::type>
                        hadoop(std::move(src), std::move(pos_vec), rnum, MapHandle(), ReduceHandle());
                hadoop.MapReduce();
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

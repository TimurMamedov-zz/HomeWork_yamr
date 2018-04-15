#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
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
        if(in.is_open())
        {
            //        auto mnum = std::atoi(argv[2]);
            //        if(mnum > 0 && rnum > 0)
            //        {

            //        }
                    auto mnum = int{7};
                    auto rnum = int{5};
                    int endPos = in.tellg();
//                    std::cout << "endPos " << endPos << std::endl;
                    in.clear();
                    in.seekg(0, std::ios_base::beg);

                    int part = endPos/mnum;
//                    std::cout << "part " << part << std::endl;
                    std::vector<std::size_t> pos_vec;
                    pos_vec.emplace_back(0);

                    auto newPos = part;

                    for(auto i = int{0}; i < mnum; i++)
                    {
                        part = (endPos - pos_vec[pos_vec.size() - 1])/ (mnum - i);
                        in.seekg(part, std::ios_base::cur);
                        if(in.tellg() < endPos)
                        {
                            while(in.peek() != '\n' &&
                                  in.tellg() > pos_vec[pos_vec.size() - 1])
                            {
                                in.unget();
                            }
                            if(in.peek() == '\n')
                                in.get();
                            if(pos_vec[pos_vec.size() - 1] >= in.tellg())
                            {

                                while(in.peek() != '\n' && in.tellg() != -1)
                                {
                                    in.get();
                                }
                                in.get();
                            }
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


//                    for(auto& item : pos_vec)
//                        std::cout << "item: " << item << std::endl;
//                    std::cout << "size: " << pos_vec.size() << std::endl;

                    MiniHadoop hadoop1(std::move(src), std::move(pos_vec), rnum);
                    hadoop1.MapReduce();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

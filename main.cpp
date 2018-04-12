#include <iostream>
#include <fstream>
#include <map>

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
        std::ifstream in("emails.txt", std::ios::binary | std::ios::ate);
//        auto mnum = std::atoi(argv[2]);
        auto mnum = 7;
        auto endPos = in.tellg();
        in.clear();
        in.seekg(0, std::ios_base::beg);
        auto part = endPos/mnum;
        std::cout << "part " << part << std::endl;
        std::map<int, int> pos_map;
        auto newPos = part;
        pos_map[0] = -1;

        for(auto i = 1; i <= mnum; i++)
        {
            in.seekg(part, std::ios_base::cur);
            if(in.tellg() < endPos)
            {
                char c = in.peek();
                while(c != '\n' && in.tellg() != -1)
                {
    //                std::cout << "peek " << c << std::endl;
                    c = in.get();
                }
                newPos = in.tellg();
            }
            else
            {
                newPos = endPos;
            }

            for(auto& pair : pos_map)
                if(pair.second == -1)
                {
                    pos_map[pair.first] = newPos;
                    if(newPos != endPos)
                        pos_map[newPos] = -1;
                    break;
                }

            std::cout << "newPos " << newPos << std::endl;
            std::cout << "in.tellg() " << in.tellg() << std::endl;

            newPos += part;
        }

        for(auto& pair : pos_map)
            std::cout << "begin: " << pair.first << ", end: " << pair.second << std::endl;

        in.close();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

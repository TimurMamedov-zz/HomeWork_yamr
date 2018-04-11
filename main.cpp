#include <iostream>
#include <fstream>
#include <map>

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 4)
        {
            std::cerr << "Usage:  yamr <src> <mnum> <rnum>\n";
            return 1;
        }
        std::ifstream in(argv[1], std::ios::binary | std::ios::ate);
        auto mnum = std::atoi(argv[2]);
        auto endPos = in.tellg();
        in.seekg(0, std::ios_base::beg);
        std::size_t part = endPos/mnum;
        if(!part)
            part = 1;


        std::map<std::ifstream::pos_type, std::ifstream::pos_type> pos_map;
        auto start = in.tellg();
        auto end = start + static_cast<std::ifstream::pos_type>(part);

        for(auto i = 0; i < mnum; i++)
        {
            std::cout << in.tellg() << std::endl;
            std::string str;
            str.resize(part);

            in.read(&str[0], part);
            if(!str.empty())
                while(str.at(str.size() - 1) != '\n')
                {
    //                in.unget();
    //                auto prevPos = in.tellg() - 1;
                    in.seekg(part - 1);
                    str.pop_back();
                    if(str.empty())
                        break;
                }
            in.seekg(part + 1);
            std::cout << str << std::endl << std::endl;
//            start = in.tellg();
        }

        in.close();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

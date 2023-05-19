#include "./meter.hpp"

#include <iostream>

int* meter::get_sizes(std::string from,
                std::set<std::string> to,
                std::string body)
{
    int* arr = new int(4);
    
    arr[2] = 5*1 + 8;
    arr[1] = 5 + from.size() + 1;
    arr[2] = [&]()->int{
        int temp = 0;
        for(auto& str : to){
            temp += to.size();
        }
        return (temp += to.size()-1 + 1);
    }();
    arr[3] = body.size() + 7;
    return arr;
}

int* meter::get_sizes(std::string from,
                std::string to,
                std::string body)
{
    std::cout <<"get_sizes\n";
    int* arr = new int(4);
    
    arr[0] = 7 + from.size();;
    arr[1] = to.size() + 5;
    arr[2] = 8;
    arr[3] = body.size() + 7;

    std::cout <<"~get_sizes\n";
    return arr;
}


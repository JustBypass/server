#include "./meter.hpp"


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


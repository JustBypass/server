#ifndef _PARTY_HPP_
#define _PARTY_HPP_

#include <set>
#include <string>

class iparser{
public:
     //int parse(std::string message);
     int parseFlag(std::string);
     std::string parseBody(std::string);
     std::set<std::string> parseTo(std::string);
     std::string parseFrom(std::string);
};

#endif
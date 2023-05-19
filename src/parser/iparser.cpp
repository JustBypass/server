#include "./iparser.hpp"
#include <regex>
#include <set>

std::string iparser::parseFrom(std::string message){
     std::regex rgx("from:'(.*?)'");
    
    std::smatch match;
    std::string result;
    if (std::regex_search(message, match, rgx) ){
        result = std::string(match[1]);
    }
    return result;
}

std::set<std::string> iparser::parseTo(std::string message){
    std::regex rgx("to:'(.*?)'");
    
    std::smatch match;
    std::set<std::string> strings;

    if (std::regex_search(message, match, rgx) )
    {
        std::stringstream ss(match[1]); // создаем поток из строки
        std::string subs;

        while (std::getline(ss, subs, ',')) { // разбиваем строку на подстроки по разделителю ","
            strings.insert(subs);
        }
    }    
    return strings;
 }

std::string iparser::parseBody(std::string message){
   std::regex rgx("data:'(.*?)'");
    
    std::smatch match;
    std::string result;
    if (std::regex_search(message, match, rgx) ){
        result = std::string(match[1]);
    }
    return result;
}

int iparser::parseFlag(std::string message){
    std::regex rgx("flag:'(.*?)'");
    std::smatch match;
    if(std::regex_search(message,match,rgx)){
        return std::stoi(match[1]);
    }
    return 0;
}
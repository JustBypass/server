#include <string>
#include "./imessage.hpp"
#include "../builders/meter.hpp"



// 
// from:user1,usern\n
// to:user2\n
// flag:1\n
// data: "hello"
//
//

#include "../parser/iparser.hpp"
/// What pattert
class chat_message : public imessage
{

public:
    std::string flags();

public:
    enum _flag_type
    {
        _FILE,
        _MSG,
        _REQ_ONLINE,
        _REQ_ALL,
        _CONNECT,
        _EXIT,
        _SET_NICKNAME
    };
    enum responce_flag_type{
        ERROR,
        ONLINE,
        MSG_TYPE_EXCEPTION,
        OK
    };

public:
    std::string from();
    std::string to();
    _flag_type get_flag();

private:
    std::string _message;
    iparser* parser;
    meter* meter;
public:
    void add_flag(_flag_type);
    void set_to(std::set<std::string>);
    void set_from(std::string);
public:
    bool check_data_length();
public:
    chat_message():imessage(){}

private:
    std::string distributor(std::string from,std::string to_person,responce_flag_type type,std::string _data_){
         return *meter->get_sizes(from,to,_data_) + "from:" + from + 
                                                '\n'+"to:" + 
                                                     to_person + 
                                                '\n' + 
                                                "flag:" +  
                                                                std::string((char*)&type,sizeof(int)) +
                                                                    "data:'" + 
                                                                          _data_ + "'";
    }
public:
    chat_message(std::string msg):imessage(msg){}
    chat_message(std::string from,std::string to,responce_flag_type type,std::string data):imessage(distributor(from,to,type,data)){}
    chat_message(std::string from,responce_flag_type type,std::string data):imessage(distributor(from,from,type,data)){}
};
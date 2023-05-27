#ifndef _CHATMESSAGE_HPP_
#define _CHATMESSAGE_HPP_

#include <string>
#include <boost/enable_shared_from_this.hpp>

// 
// from:user1,usern\n
// to:user2\n
// flag:1\n
// data: "hello"
//
//

/// What pattert
class chat_message :public boost::enable_shared_from_this<chat_message>{
public:
    chat_message(const chat_message& msg);
    chat_message& operator=(const chat_message& rhs) ;
public:
    enum _flag_type
    {
        _FILE,
        _MSG,
        _REQ_ONLINE,
        _REQ_ALL,
        _CONNECT,
        _EXIT,
        _SET_NICKNAME,
        _MSG_ALL
    };
    enum responce_flag_type{
        ERROR,
        ONLINE,
        MSG_TYPE_EXCEPTION,
        OK
    };
public:
    std::string& data(){
        return data_;
    }
    int size(){
        return data_.size();
    }
private:
    std::string data_;  
public:
    bool check_data_length();
private:
    std::string distributor(std::string from,std::string to,size_t flag,std::string _data_);
public:
    chat_message();
    chat_message(std::string _msg);
    chat_message(std::string from,std::string to,size_t type,std::string data);
    chat_message(std::string from,int type,std::string data);
};

#endif
#include "./chat_room.hpp"
#include "../chat_message/chat_message.hpp"
#include "../party/party.hpp"
#include "../chat_message/chat_message.hpp"
#include "../parser/iparser.hpp"
#include "../connection/srv_connection.hpp"
#include "../builders/director.hpp"

#include <string>

shared_connection chat_room::get_connection_by_nickname(std::string nick){
    for(auto& user:attendees ){
        if(user->get_nickname() == nick){
            return user;
        }
    }
    return nullptr;
}

void chat_room::send(chat_message& _message){
    messages.push_back(_message);// ? 

    auto to = parser.parse(headers[2]);

    auto flag = _message.get_flag();

    chat_message* _msg_;       

    int _sizes_[3]; 
    auto from = *parser.parse(headers[1]).begin();// to
    auto _connection = get_connection_by_nickname(from);
    auto body = *parser.parse(headers[4]).begin();

    //TODO: clear stack from old messages

    switch(flag){
        case(chat_message::_EXIT):{
            disconnect(from);
        }
        case(chat_message::_CONNECT):{

        }
        case(chat_message::_REQ_ONLINE):{
            auto online = users_online_count();
            size_t type = chat_message::ONLINE;
                                            
            chat_message _msg(from,type,online);
            _connection->send(_msg);
        }
        case(chat_message::_MSG||chat_message::_FILE):{
            chat_message _msg;
            for(auto& connection: attendees){
                if(to.count(connection) == 1){
                    chat_message _msg(from,connection->get_nickname(),flag,body);
                    connection->send(_msg);
                }
            }
        }
        case(chat_message::_SET_NICKNAME):{
            std::string last_name = _connection->get_nickname() ;
            _connection->set_nickname(body);

            for(auto& connection: attendees){
                chat_message _msg(from,connection->get_nickname(), chat_message::OK,"user " + last_name " changed his nickname to "+ body);
                connection->send(_msg);
            }
        }   
    }
}

void chat_room::disconnect(shared_party connection){
    chat_message mesg_;
    attendees.erase(connection);
    connection->exit();
}


size_t chat_room::users_online_count(){
    return attendees.size();
}

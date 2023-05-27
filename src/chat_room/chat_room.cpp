#include "./chat_room.hpp"
#include "../chat_message/chat_message.hpp"
#include "../parser/iparser.hpp"
#include "../connection/srv_connection.hpp"
#include <string>
#include <iostream>

shared_connection chat_room::get_connection_by_nickname(std::string nick){
     for(auto& atend :_attendees){
        if(atend->getName() == nick){
            return atend;
        }
    }
    return nullptr;
}

void chat_room::send(boost::shared_ptr<chat_message> _message,shared_connection cn){
   // messages.push_back(_message);
  // std::cout << "room.send()\n";
   std::cout << _message->data() <<std::endl;
   std::string data = _message->data();

    boost::shared_ptr<iparser> parser(new iparser());

    auto to = parser->parseTo(data);

    auto flag = parser->parseFlag(data);

    auto _from = parser->parseFrom(data);

    auto _connection = cn;//get_connection_by_nickname(_from);
    auto body = parser->parseBody(data);

  //  std::cout <<"After proessing in room.send()\n";
    switch(flag){
        case(chat_message::_EXIT):{
            disconnect(_from);
            break;
        }
        case(chat_message::_CONNECT):{
            connect(cn,body);
           // attendees.insert(std::make_pair(body,cn));
           cn->setName(body);
           _attendees.push_back(_connection);
            std::cout <<"Now is " <<_attendees.size() <<"  online\n";
            break;
        }
        case(chat_message::_REQ_ONLINE):{

            auto online = users_online_count();
            int type = chat_message::ONLINE;
                                            
            chat_message _msg(_from,type,std::to_string(online));
            // std::cout <<"Message is " <<_msg.data() <<std::endl;
           // std::cout <<"before    _connection->send(_msg.shared_from_this())" <<std::endl;

            _connection->send(_msg);
            break;
        }
        case(chat_message::_MSG||chat_message::_FILE):{
            for(auto connection: _attendees){
                if(to.count(connection->getName()) == 1){

                    chat_message _msg(_from,connection->getName(),flag,body);
                    connection->send(_msg);
                }
            }
            break;
        }
        case(chat_message::_SET_NICKNAME):{
            std::string last_name = _from ;
            
            for(auto& atend :_attendees){
                if(atend == cn){
                    atend->setName(body);
                    chat_message _msg(_from,body, chat_message::OK,"user " + last_name +" changed his nickname to "+ body);
                    atend->send(_msg);
                }
            }
            break;
        }   
        case(chat_message::_MSG_ALL):{
            for(auto connection: _attendees){
                if(connection != cn){
                    chat_message _msg(_from,connection->getName(),flag,body);
                    connection->send(_msg);
                }
            }
            break;
        }   
    }
   // std::cout << "~room.send()\n";
}

void chat_room::connect(shared_connection connection,std::string name){
    for(auto atend :_attendees){
        if(atend == connection){
            atend->setName(name);
        }
    }
}

void chat_room::connect(shared_connection connection){
    //attendees.insert(std::make_pair("",connection));
    _attendees.push_back(connection);
}

void chat_room::disconnect(std::string from){
    chat_message mesg_;
    auto connection = get_connection_by_nickname(from);
    if(connection != nullptr){
      //  _attendees.pop_back(connection);

    }
}
void chat_room::disconnect(shared_connection connection){
    chat_message mesg_;
    for(auto& atend :_attendees){
        if(atend == connection){
           // _attendees.pop_back(atend);
        }
    }
}


size_t chat_room::users_online_count(){
    return _attendees.size();
}

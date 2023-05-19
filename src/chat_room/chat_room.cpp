#include "./chat_room.hpp"
#include "../chat_message/chat_message.hpp"
#include "../parser/iparser.hpp"
#include "../connection/srv_connection.hpp"
#include <string>
#include <iostream>

shared_connection chat_room::get_connection_by_nickname(std::string nick){
    return attendees[nick];
}

void chat_room::send(boost::shared_ptr<chat_message> _message,shared_connection cn){
   // messages.push_back(_message);
   std::cout << "room.send()\n";
   std::cout << _message->data() <<std::endl;
   std::string data = _message->data();

    boost::shared_ptr<iparser> parser(new iparser());

    auto to = parser->parseTo(data);

    auto flag = parser->parseFlag(data);

    auto _from = parser->parseFrom(data);

    auto _connection = cn;//get_connection_by_nickname(_from);
    auto body = parser->parseBody(data);

    std::cout <<"After proessing in room.send()\n";
    switch(flag){
        case(chat_message::_EXIT):{

            disconnect(_from);
            break;
        }
        case(chat_message::_CONNECT):{
            connect(cn,body);
            attendees.insert(std::make_pair(body,cn));
            std::cout <<"Now is " <<attendees.size() <<"  online\n";
            break;

        }
        case(chat_message::_REQ_ONLINE):{

            auto online = users_online_count();
            int type = chat_message::ONLINE;
                                            
            chat_message _msg(_from,type,std::to_string(online));
            std::cout <<"Message is " <<_msg.data() <<std::endl;
            //  attendees[_from]->send(_msg.shared_from_this())
            //auto f = _msg.shared_from_this();
            std::cout <<"before    _connection->send(_msg.shared_from_this())" <<std::endl;

           // attendees[_from]->send(_msg);
            _connection->send(_msg);
            break;

        }
        case(chat_message::_MSG||chat_message::_FILE):{
            chat_message _msg;
            for(auto& connection: attendees){
                if(to.count(connection.first) == 1){
                    chat_message _msg(_from,connection.first,flag,body);
                    connection.second->send(_msg);
                }
            }
            break;
        }
        case(chat_message::_SET_NICKNAME):{

            std::string last_name = _from ;
            
            attendees.erase(_from);
            attendees.insert(std::make_pair(body,_connection));

            for(auto& connection: attendees){
                chat_message _msg(_from,body, chat_message::OK,"user " + last_name +" changed his nickname to "+ body);
                connection.second->send(_msg);
            }
            break;
        }   
    }
    std::cout << "~room.send()\n";
}

void chat_room::connect(shared_connection connection,std::string name){
    for(auto& atend :attendees){
        if(atend.second == connection){
            attendees.erase(atend.first);
            attendees.insert(std::make_pair(name,connection));
        }
    }
}

void chat_room::connect(shared_connection connection){
    attendees.insert(std::make_pair("",connection));
}

void chat_room::disconnect(std::string from){
    chat_message mesg_;
    auto connection = attendees[from];
    attendees.erase(from);
  //  connection->exit();
}
void chat_room::disconnect(shared_connection connection){
    chat_message mesg_;
    for(auto& atend :attendees){
        if(atend.second == connection){
            //connection->close();
            attendees.erase(atend.first);
        }
    }
}


size_t chat_room::users_online_count(){
    return attendees.size();
}

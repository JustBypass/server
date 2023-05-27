#ifndef _CHATROOM_HPP_
#define _CHATROOM_HPP_


#include <deque>

//#include <list>
#include <set>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <map>


class srv_connection;
class chat_message;
class party;

typedef boost::shared_ptr<party> shared_party;
typedef boost::shared_ptr<srv_connection> shared_connection;

class chat_room{
public:
    void connect(shared_connection);
    void disconnect(std::string);
    size_t users_online_count();
    void connect(shared_connection ,std::string );

private:
    std::map<std::string,shared_connection> attendees;
    std::deque<boost::shared_ptr<chat_message>> messages;
    std::vector<shared_connection> _attendees;
public:
    void send(boost::shared_ptr<chat_message>,shared_connection);
    void disconnect(shared_connection connection);

private: // upcomming changes
    bool block_nickname(std::string);
private:
    shared_connection get_connection_by_nickname(std::string);
};


#endif
#include <deque>
#include <set>
#include <vector>
#include <boost/shared_ptr.hpp>

class srv_connection;
class chat_message;
class iparser;
class party;
class director;

typedef boost::shared_ptr<party> shared_party;
typedef boost::shared_ptr<srv_connection> shared_connection;

class chat_room{
public:
    void connect(shared_connection);
    void disconnect(shared_party);
    size_t users_online_count();

private:
    std::set<shared_party> attendees;
    std::deque<chat_message> messages;

private:
    iparser& parser;
    //std::vector<chat_message> _all_messages;
    director& _director;
public:
    void send(chat_message&);

public:
    void pull_out_of_size_error(chat_message&);

private: // upcomming changes
    bool block_nickname(std::string);

    /// 2bytes2bytes2bytes2bytes
     std::vector<std::string> headers = {
        "FROM",
        "TO",
        "FLAGS",
        "BODY",
        "LENGTHS"
     };
private:
    shared_connection get_connection_by_nickname(std::string);
};

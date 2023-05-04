#include "../party/party.hpp"
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "../parser/simple_parser.hpp"
#include <deque>

class chat_room;
class iparser;
class chat_message;
typedef  boost::asio::ip::tcp::socket _socket_;

class srv_connection : public party ,public boost::enable_shared_from_this<srv_connection>{
private:
    void async_read_header();
    void write(std::string msg);
    
    void start_reading();

private:
    chat_room& room;
    std::string nickname;

public:
    inline std::string get_nickname()const override{return nickname;}
    inline void set_nickname(std::string new_nickname)override{nickname = new_nickname;}

private:
   // const iparser& parser;
    chat_message& cur_message;
    _socket_ sock;
    std::deque<boost::shared_ptr<chat_message>> to_write_messages;
    size_t sizes[4] ;//= {18,136,8,819200};
    int now = 0;
    
public:
    void send(chat_message msg)override;
public:
    srv_connection(_socket_ _socket,chat_room _room);
public:
    void open();
};


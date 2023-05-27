#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <deque>
#include "../party/party.hpp"
#include <boost/shared_ptr.hpp>
class chat_room;
class chat_message;

class srv_connection : public boost::enable_shared_from_this<srv_connection>{
private:
    void async_read_header(size_t ,int*);
    void write(std::string);
    
    void start_reading();
private:
    boost::shared_ptr<chat_room> room;
    std::string name;
private:
    boost::shared_ptr<chat_message> cur_message;
    boost::shared_ptr<boost::asio::ip::tcp::socket> sock;
    int _sizes[4];
public:
    boost::shared_ptr<boost::asio::ip::tcp::socket> socket();
    void send(chat_message msg);
    std::string getName();
    void setName(std::string name_);

public:
    srv_connection(boost::asio::io_context& ioservice,boost::shared_ptr<chat_room> _room);
    ~srv_connection();
public:
    void read_body(const boost::system::error_code& );
    void open();
    void header(const boost::system::error_code& ec );

};


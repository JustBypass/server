#include <boost/asio.hpp>
#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/bind/bind.hpp>
class srv_connection;
class chat_room;

class async_server:public boost::enable_shared_from_this<async_server>{
public:  
    async_server(boost::asio::io_context& service, boost::asio::ip::tcp::endpoint& ep);
public:
    async_server(const async_server&);
    async_server& operator=(const async_server&);
    void accept_handle(boost::shared_ptr<srv_connection>  ,const boost::system::error_code& );

private:
    boost::asio::io_context& serv;
    boost::asio::ip::tcp::acceptor acceptor;
    std::vector<boost::shared_ptr<srv_connection>> connections;
    boost::shared_ptr<chat_room> room;
private:
    void accept();
};

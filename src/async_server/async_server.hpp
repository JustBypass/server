#include <boost/asio.hpp>
#include <boost/asio.hpp>

using namespace boost::asio::ip;
using namespace boost::asio;
using boost::asio::ip::tcp;


class async_server{
public:  
     async_server(boost::asio::io_service& service,boost::asio::ip::tcp::endpoint& ep);

public:
    void accept_connections();

private:
    tcp::endpoint endpoint;
    io_service& serv;
    boost::asio::ip::tcp::acceptor acceptor;

private:
    void accept();

};

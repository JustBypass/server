#include "./async_server.hpp"
#include "../connection/srv_connection.hpp"

async_server::async_server(boost::asio::io_service& service,boost::asio::ip::tcp::endpoint& ep):endpoint(ep),
                                                                                serv(service),acceptor(service,ep)
{
    accept();
}

void async_server::accept(){
    acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket){
        if (!ec)
        {
           boost::shared_ptr<srv_connection> _connection;
           _connection->open();
        }
        accept();
    });
}

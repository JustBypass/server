#include "./async_server.hpp"
#include "../connection/srv_connection.hpp"
#include "../chat_room/chat_room.hpp"
#include "../chat_message/chat_message.hpp"
#include <cstring>
async_server::async_server(boost::asio::io_context& service, boost::asio::ip::tcp::endpoint& ep)
    :  acceptor(service, ep),serv(service),room(new chat_room())
{
    std::cout << "Started accepting requests on ip '" + ep.address().to_string() + std::string("' and port; '") +std::to_string( ep.port()) + "'\n";
    accept();
}

void async_server::accept_handle(boost::shared_ptr<srv_connection>  session,const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "attempt of connection";
        session->open();
    }
    else{
        std::cout << error.message() <<std::endl;
        std::cout << "Some error while async_accept()\n";
    }
    accept();
}

void async_server::accept(){
    
    boost::shared_ptr<srv_connection> _connection(new srv_connection(serv,room));
    acceptor.async_accept(*_connection->socket(),
        boost::bind(&async_server::accept_handle,this,_connection,boost::asio::placeholders::error));
}

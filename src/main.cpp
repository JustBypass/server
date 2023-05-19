#include <string>
#include <boost/shared_ptr.hpp>
#include <list>
#include <boost/asio.hpp>
#include <vector>
#include "./async_server/async_server.hpp"

#include <boost/log/trivial.hpp>

// argc rooms for connections
int main(int argc,char** argv){
    
    boost::asio::io_context service;
    std::vector<boost::shared_ptr<async_server>> servers;
    for(int i = 1;i<argc;++i){
        boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"),atoi(argv[i]));
        boost::shared_ptr<async_server> serv(new async_server(service,ep));
        servers.push_back(serv);
    }
     // async_server server(service,ep);
    std::cout << servers.size() <<std::endl;
    service.run();
}
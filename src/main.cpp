
#include <string>
#include <boost/shared_ptr.hpp>
#include <list>
#include <boost/asio.hpp>

#include "./async_server/async_server.hpp"
#include <boost/log/trivial.hpp>

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

// argc rooms for connections
int main(int argc,char** argv){

    BOOST_LOG_TRIVIAL(debug) << "Debug logging started...";

    boost::asio::io_service service;
    std::list<async_server> servers;

    for(int i = 0;i<argc;++i){
        servers.emplace_back((service,new tcp::endpoint(boost::asio::ip::tcp::v4(),atoi(argv[i]))));
    }
    service.run();
}
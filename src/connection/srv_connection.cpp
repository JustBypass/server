#include "./srv_connection.hpp"
#include <boost/asio.hpp>
#include "../chat_message/chat_message.hpp"
#include "../chat_room/chat_room.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>              
void open();


void srv_connection::write(std::string msg){
  //  auto self(shared_from_this());
  //std::cout <<"write()";
  std::cout <<msg.data() <<std::endl;
  boost::asio::async_write(*sock,
                boost::asio::buffer(msg, msg.size()),
                [this](const boost::system::error_code& ec, std::size_t /*length*/)
                {
                  if (!ec) // check the length of header
                  {
                   // std::cout <<"bytes sent\n"; // change here something
                     boost::asio::async_read(*sock,boost::asio::buffer(_sizes,16),
                       boost::bind(&srv_connection::header,shared_from_this(),boost::asio::placeholders::error));
                  }
                });
}

srv_connection::srv_connection(boost::asio::io_context& ioservice,boost::shared_ptr<chat_room> _room):room(_room),sock(new boost::asio::ip::tcp::socket(ioservice)),cur_message(new chat_message()){
//  std::cout << "srv_connection()" <<std::endl;

};
  srv_connection::~srv_connection(){
    //  std::cout <<"~srv_connection()\n";
  }
boost::shared_ptr<boost::asio::ip::tcp::socket> srv_connection::socket(){
  return sock;
}


void srv_connection::read_body(const boost::system::error_code& ec){
  //  std::cout << "read body()\n";

     if (!ec) // check the length of header
      {
        std::cout <<cur_message->data() <<std::endl;
        room->send(cur_message,shared_from_this());
        boost::asio::async_read(*sock,boost::asio::buffer(_sizes,16),
          boost::bind(&srv_connection::header,shared_from_this(),boost::asio::placeholders::error));
      }
      else{
        room->disconnect(shared_from_this());
      }
}

void srv_connection::open(){
 // std::cout << "open()" <<std::endl;

  room->connect(shared_from_this());
    boost::asio::async_read(*sock,boost::asio::buffer(_sizes,16),
      boost::bind(&srv_connection::header,shared_from_this(),boost::asio::placeholders::error));

 // std::cout <<"~open()\n";
}

void srv_connection::header(const boost::system::error_code& ec ){
 if(! ec){
  //  std::cout << "header()" <<std::endl;

    int size = _sizes[0] + _sizes[1] + _sizes[2] + _sizes[3];
    std::cout <<size <<std::endl;
    cur_message->data().resize(size);

    boost::asio::async_read(*sock,boost::asio::buffer(cur_message->data(),size),
        boost::bind(&srv_connection::read_body,shared_from_this(),boost::asio::placeholders::error
    ));
 }
 else{
   // room->disconnect(shared_from_this());
 }
  std::cout <<"~header()\n";
}

void srv_connection::send(chat_message msg){
 // bool is_writing; //= !to_write_messages.empty();
  //to_write_messages.push_back(msg);
  //if(!is_writing){
    std::cout <<" srv_connection send to " <<name <<'\n';
      write(msg.data());
 // }
}


std::string srv_connection::getName(){
  return name;
}
void srv_connection::setName(std::string name_){
  name = name_;
}

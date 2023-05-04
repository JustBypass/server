#include "./srv_connection.hpp"
#include <boost/asio.hpp>
#include "../chat_message/chat_message.hpp"
#include "../chat_room/chat_room.hpp"

void srv_connection::start_reading();


void srv_connection::write(std::string msg){
    auto self(shared_from_this());
  boost::asio::async_read(sock,
                boost::asio::buffer(msg, msg.size()),
                [this, self](boost::system::error_code ec, std::size_t /*length*/)
                {
                  if (!ec) // check the length of header
                  {
                     start_reading()
                  }
                });

}

srv_connection::srv_connection(_socket_ _socket,chat_room _room){
  sock = std::move(_socket);
  room = std::move(_room);
}



void srv_connection::async_read_header()
{
  auto self(shared_from_this());
  boost::asio::async_read(sock,
                          boost::asio::buffer(cur_message.data(), sizes[this->now]),
                          [this, self](boost::system::error_code ec, std::size_t /*length*/)
                          {
                            if (!ec) // check the length of header
                            {
                              if (this->now == 4)
                              {
                                this->now = 0;
                                room.send(cur_message);
                              }
                              else
                              {
                                ++this->now;
                              }
                              async_read_header();
                            }
                            else
                            {
                               room.disconnect(shared_from_this());
                            }
                          });
}

void srv_connection::start_reading()
{
  auto self(shared_from_this());
  boost::asio::async_read(sock,
                          boost::asio::buffer(sizes, 4 * 8),
                          [this, self](boost::system::error_code ec, std::size_t /*length*/)
                          {
                            if (!ec) // check the length of header
                            {
                              async_read_header();
                            }
                            else
                            {
                               room.disconnect(shared_from_this());
                            }
                          });
}

void srv_connection::open(){
  start_reading();
}

void srv_connection::send(chat_message msg){
  bool is_writing = !to_write_messages.empty();
  to_write_messages.push_back(msg);
  if(!is_writing){
      write(msg.data());
  }
}

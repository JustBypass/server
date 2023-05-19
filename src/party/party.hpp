//#ifndef _PARTY_HPP_
//#define _PARTY_HPP_

#include <string>
class chat_message;

class party{
public:
    virtual ~party(){}
public:
    virtual void send(chat_message& msg) = 0;
  //  virtual void exit() = 0;
};

//#endif
#include <string>

class party{
public:
    virtual ~party(){}
public:
    virtual void send(chat_message message) = 0;
    virtual inline std::string get_nickname()const = 0;
    virtual inline void set_nickname(std::string new_nickname) = 0;
    virtual void exit() = 0;
};

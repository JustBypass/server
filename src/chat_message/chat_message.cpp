#include "./chat_message.hpp"
#include <cstring>
#include "../builders/meter.hpp"
#include <iostream>

std::string chat_message::distributor(std::string from,std::string to,size_t flag,std::string body){

   std::cout << "convert()\n";
    meter _meter;
    int* arr = _meter.get_sizes(from,to,body);

    unsigned char* bytes = reinterpret_cast<unsigned char*>(arr);
    for (int i = 0; i < 4 * sizeof(int); i++) {
        std::cout << static_cast<int>(bytes[i]) << " ";
    }
    std::string str(reinterpret_cast<char*>(bytes), 4 * sizeof(int));

    int new_arr[4];
    for (int i = 0; i < 4; i++) {
        new_arr[i] = *reinterpret_cast<int*>(&str[i * sizeof(int)]);
    }

    delete(arr);

    std::cout <<"~convert()\n";
    return str + std::string("from:'") + from + 
                                        "'"
                                        +std::string("to:'") + 
                                                to + 
                                        "'" + 
                                        std::string("flag:'") +  
                                                        std::to_string(flag) + "'" +
                                                            std::string("data:'") + 
                                                                    body + "'";
}
chat_message::chat_message(){};


chat_message::chat_message(const chat_message& msg){
        this->data_ = msg.data_;
};

// Оператор копирования
chat_message& chat_message::operator=(const chat_message& rhs) {
    if (this != &rhs) {
        this->data_ = rhs.data_;
    }
    return *this;
}

chat_message::chat_message(std::string _msg):data_(_msg){};
chat_message::chat_message(std::string from,std::string to,size_t type,std::string data):data_(distributor(from,to,type,data)){};
chat_message::chat_message(std::string from,int type,std::string data):data_(distributor(from,from,type,data)){};
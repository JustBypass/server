#include <string>

class imessage{
public:
    imessage(std::string _data):data_(_data){}
public:
    std::string& data(){
        return data_;
    }
    int size(){
        return data_.size();
    }
private:
    std::string data_;  
};
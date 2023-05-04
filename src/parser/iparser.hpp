#include <set>
#include <string>

class iparser{
public:
    virtual std::set<std::string> parse(std::string) = 0;
};
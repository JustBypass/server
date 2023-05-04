#include "./iparser.hpp"
#include <map>
class simple_parser: public iparser{
public:
      std::set<std::string> parse(std::string) override;
};
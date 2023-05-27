#ifndef SCROLL_H_
#define SCROLL_H_

#include <vector>

#include "Option.h"

class Scroll
{
private:
    int current_option;
    // std::vector<Option> options; //TODO : Make it vector of options instead of clear text
    std::vector<std::string> options {"1","1","1","1","1","1"};

public:
    Scroll();
    ~Scroll() = default;

public:
    int getCurrentOption();
    std::vector<std::string> getOptions();
    
    void scrollDown();
    void scrollUp();
    void choseOption();
};

#endif

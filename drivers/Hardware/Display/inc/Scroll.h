#ifndef SCROLL_H_
#define SCROLL_H_

#include <vector>

#include "Option.h"

class Scroll
{
public:
    int current_option;
    // std::vector<Option> options; //TODO : Make it vector of options instead of clear text
    std::vector<std::string> options {"1","2","3","4","5","6","7","8","99"};
                                    // 0   1   2   3   4   5   6   7   8
public:
    Scroll() = default;
    ~Scroll() = default;

public:
    int getCurrentOption() const;
    int get_option_count() const;
    std::vector<std::string> getOptions();
    
    void scrollDown();
    void scrollUp();
    void choseOption();
};

#endif

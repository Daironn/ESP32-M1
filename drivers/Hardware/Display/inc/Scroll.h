#ifndef SCROLL_H_
#define SCROLL_H_

#include <vector>

#include "Option.h"
class Scroll
{
private:
    int current_option;
    std::vector<Option> options;
    
public:
    Scroll();
    ~Scroll() = default;
};

#endif

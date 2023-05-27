#ifndef OPTION_H_
#define OPTION_H_

#include <iostream>

class Option
{
private:
    std::string text;

public:
    virtual int doAThing() = 0;

public:
    Option(std::string a_text): text(a_text){};
    virtual ~Option();
};

#endif

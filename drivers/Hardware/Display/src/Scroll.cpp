#ifndef SCROLL_C_
#define SCROLL_C_

#include "Scroll.h"

#define FIRST_INDEX 0

int Scroll::getCurrentOption() const
{
    return this->current_option;
}

int Scroll::get_option_count() const
{
    return this->options.size();
}

std::vector<std::string> Scroll::getOptions()
{
    return this->options;
}

void Scroll::scrollDown()
{
    // if(current_option < options.size())
        this->current_option++;
}

void Scroll::scrollUp()
{
    // if(current_option >= FIRST_INDEX)
        this->current_option--;
}
#endif

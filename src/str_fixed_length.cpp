//
//  str_fixed_length.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/17/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "str_fixed_length.hpp"
#include <string>
#include <algorithm>

std::string str_fixed_length(int value, int digits)
{
    unsigned int uvalue = value;
    if (value < 0) {
        uvalue = -uvalue;
    }
    std::string result;
    while (digits-- > 0) {
        result += ('0' + uvalue % 10);
        uvalue /= 10;
    }
    if (value < 0) {
        result += '-';
    }
    std::reverse(result.begin(), result.end());
    return result;
}
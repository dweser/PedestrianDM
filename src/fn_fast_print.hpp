//
//  fn_fast_print.hpp
//  diffusion
//
//  Created by Daniel Weser on 9/19/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef fn_fast_print_hpp
#define fn_fast_print_hpp

#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

void fn_fast_print_xy(double xy[][2], string path, int n, string iter_string);
void fn_fast_print_state(bool state[], string path, int n, string iter_string);

#endif /* fn_fast_print_hpp */

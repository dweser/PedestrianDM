//
//  fn_file_print.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/16/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef fn_file_print_hpp
#define fn_file_print_hpp

#include <string>

void fn_file_print_xy(double xy[][2], std::string path, int n, std::string iter_string, int seed_num);
void fn_file_print_state(bool state[], std::string path, int n, std::string iter_string, int seed_num);

#endif /* fn_file_print_hpp */

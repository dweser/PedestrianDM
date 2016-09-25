//
//  game_threshold_vm.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef game_threshold_vm_hpp
#define game_threshold_vm_hpp

#include "parameters_xml.hpp"

void game_threshold_vm(double xy[][2], bool state[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

#endif /* game_threshold_vm_hpp */

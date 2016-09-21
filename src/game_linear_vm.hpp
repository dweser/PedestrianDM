//
//  game_linear_vm.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef game_linear_vm_hpp
#define game_linear_vm_hpp

#include "parameters.hpp"
#include "fn_neighbors.hpp"

#include <omp.h>
#include <vector>
#include <math.h>
#include <cstdlib>
using namespace std;

void game_linear_vm(double xy[][2], bool state[], int neighbors[][100], parameters &parameters);

#endif /* game_linear_vm_hpp */

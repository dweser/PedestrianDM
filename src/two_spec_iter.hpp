//
//  two_spec_iter.hpp
//  diffusion
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef two_spec_iter_hpp
#define two_spec_iter_hpp

#include "game_linear_vm.hpp"
#include "fn_phi.hpp"
#include "fn_distance.hpp"
#include "parameters.hpp"
#include "fn_neighbors.hpp"

#include <omp.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

void two_spec_iter(double xy[][2], bool state[], int neighbors[][100], PARAMETERS &parameters);

#endif /* two_spec_iter_hpp */

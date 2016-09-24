//
//  fn_neighbors.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef fn_neighbors_hpp
#define fn_neighbors_hpp

#include "fn_distance.hpp"

void fn_neighbors(double xy[][2], bool state[], int neighbors[][100], int n, float r_coop, float r_def, const int NUM_THREADS);
int fn_count_states(int neighbors[100], bool state[], int target);
int fn_count_neighbors(int neighbors[100]);

#endif /* fn_neighbors_hpp */

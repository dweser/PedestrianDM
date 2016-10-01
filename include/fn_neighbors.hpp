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
#include "nanoflann.hpp"
#include "xy_struct.hpp"

void fn_neighbors(XY &xy, bool state[], int neighbors[][100], int n, float r_coop, float r_def,
                  nanoflann::KDTreeSingleIndexAdaptor<nanoflann::L2_Simple_Adaptor<double, XY>, XY, 2 /* dim */> &tree);
int fn_count_states(int neighbors[100], bool state[], int target);
int fn_count_neighbors(int neighbors[100]);

#endif /* fn_neighbors_hpp */

//
//  two_spec_iter.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef two_spec_iter_hpp
#define two_spec_iter_hpp

#include "parameters_xml.hpp"
#include "xy_struct.hpp"

void two_spec_iter(XY &xy, bool state[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

#endif /* two_spec_iter_hpp */

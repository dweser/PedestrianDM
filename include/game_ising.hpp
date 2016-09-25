//
//  game_ising.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/24/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef game_ising_hpp
#define game_ising_hpp

#include "parameters_xml.hpp"

void game_ising(double xy[][2], bool state[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

#endif /* game_ising_hpp */

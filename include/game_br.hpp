//
//  game_br.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/24/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef game_br_hpp
#define game_br_hpp

#include "parameters_xml.hpp"

void game_br(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

#endif /* game_br_hpp */

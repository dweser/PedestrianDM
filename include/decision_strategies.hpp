//
//  decision_strategies.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/24/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef decision_strategies
#define decision_strategies

#include "parameters_xml.hpp"


void dec_linear_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

void dec_nonlinear_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

void dec_threshold_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

void dec_norm_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

void dec_ising(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);

void dec_br(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS);


#endif /* decision_strategies */
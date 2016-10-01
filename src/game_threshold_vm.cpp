//
//  game_threshold_vm.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/24/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "game_threshold_vm.hpp"
#include "parameters_xml.hpp"
#include "fn_neighbors.hpp"

#include <cstdlib>
#include <omp.h>
#include <math.h>
using namespace std;

void game_threshold_vm(bool state[], bool state_temp[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    int   N_i0 = 0;
    int   N_i1 = 0;
    
    // parameters for convenience
    float markov_rate = parameters.MARKOV_RATE;
    float dt = parameters.DT;
    int threshold = parameters.THRESHOLD;

    // loop
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for
        for (int i=0; i<parameters.N; i++)
        {
            // number of neighbors
            N_i0 = fn_count_states(neighbors[i], state, 0);
            N_i1 = fn_count_states(neighbors[i], state, 1);
            
            // state change
            if (state[i]==0)
            {
                // if N1>=threshold, they jump with rate 1 scaled by the "markov rate" and "dt"
                // otherwise, they don't jump
                if (N_i1 >= threshold)
                {
                    state_temp[i] = (rand()/RAND_MAX < (1 - exp(-markov_rate*dt))) == 1;
                } else
                {
                    state_temp[i] = state[i];
                }
            } else
            {
                if (N_i0 >= threshold)
                {
                    state_temp[i] = (rand()/RAND_MAX < (1 - exp(-markov_rate*dt))) == 0;
                } else
                {
                    state_temp[i] = state[i];
                }
            }
        }
        // commit changes
        #pragma omp for
        for (int i=0; i<parameters.N; i++)
        {
            state[i] = state_temp[i];
        }
    }
}
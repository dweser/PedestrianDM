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

void game_threshold_vm(double xy[][2], bool state[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    long   N_i0 = 0;
    long   N_i1 = 0;
    
    // parameters for /convenience
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
                    state[i] = (bool) (rand()/RAND_MAX < (1 - exp(-markov_rate*dt)))==1;
                }
            } else
            {
                if (N_i0 >= threshold)
                {
                    state[i] = (bool) (rand()/RAND_MAX < (1 - exp(-markov_rate*dt)))==0;
                }
            }
        }
    }
}
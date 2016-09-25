//
//  game_ising.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/24/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "game_ising.hpp"
#include "parameters_xml.hpp"
#include "fn_neighbors.hpp"

#include <cstdlib>
#include <omp.h>
#include <math.h>
using namespace std;

void game_ising(double xy[][2], bool state[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    long   N_m1 = 0;
    long   N_p1 = 0;
    double summation = 0;
    double rate = 0;
    
    // parameters for convenience
    float ising_beta = parameters.ISING_BETA;
    float ising_h = parameters.ISING_H;
    float dt = parameters.DT;

    // loop
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for
        for (int i=0; i<parameters.N; i++)
        {
            // number of neighbors
            N_m1 = fn_count_states(neighbors[i], state, 0);
            N_p1 = fn_count_states(neighbors[i], state, 1);

            summation = (-1)*N_m1 + (1)*N_p1 + (N_m1+N_p1)*ising_h;
            rate = exp(-ising_beta*state[i]*summation);

            // state change
            if (state[i]==0)
            {
                state[i] = (bool) (rand()/RAND_MAX < (1 - exp(-rate*dt)))==1;
            } else
            {
                state[i] = (bool) (rand()/RAND_MAX < (1 - exp(-rate*dt)))==0;
            }
        }
    }
}
//
//  game_linear_vm.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "game_linear_vm.hpp"
#include "parameters_xml.hpp"
#include "fn_neighbors.hpp"

#include <iostream>

#include <cstdlib>
#include <omp.h>
#include <cmath>
using namespace std;

void game_linear_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    int    N_i0 = 0;
    int    N_i1 = 0;
    double B_i0 = 0;
    double B_i1 = 0;
    
    // parameters for convenience
    float markov_rate = parameters.MARKOV_RATE;
    float a_00 = parameters.a_00;
    float a_01 = parameters.a_01;
    float a_10 = parameters.a_10;
    float a_11 = parameters.a_11;
    float coop_const = parameters.COOP_CONST;
    float guilt_const = parameters.GUILT_CONST;
    float dt = parameters.DT;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for
        for (int i=0; i<parameters.N; i++)
        {
            // number of neighbors
            N_i0 = fn_count_states(neighbors[i], state_old, 0);
            N_i1 = fn_count_states(neighbors[i], state_old, 1);

            // payoffs
            B_i0 = markov_rate * (a_00*N_i0 + a_01*N_i1 + coop_const);
            B_i1 = markov_rate * (a_10*N_i0 + a_11*N_i1 - guilt_const);

            // state change
            if (state_old[i]==0)
            {
                state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-B_i1*dt))) == 1;
            } else
            {
                state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-B_i0*dt))) == 0;
            }
        }
    }
}
//
//  game_br.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/24/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "game_br.hpp"
#include "parameters_xml.hpp"
#include "fn_neighbors.hpp"

#include <cstdlib>
#include <omp.h>
#include <math.h>
using namespace std;

void game_br(double xy[][2], bool state[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    long   N_i0 = 0;
    long   N_i1 = 0;
    double B_i0 = 0;
    double B_i1 = 0;
    
    // parameters for /convenience
    float markov_rate = parameters.MARKOV_RATE;
    float a_00 = parameters.a_00;
    float a_01 = parameters.a_01;
    float a_10 = parameters.a_10;
    float a_11 = parameters.a_11;
    float coop_const = parameters.COOP_CONST;
    float guilt_const = parameters.GUILT_CONST;
    float dt = parameters.DT;

    // loop
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for
        for (int i=0; i<parameters.N; i++)
        {
            // number of neighbors
            N_i0 = fn_count_states(neighbors[i], state, 0);
            N_i1 = fn_count_states(neighbors[i], state, 1);

            // payoffs
            B_i0 = a_00*N_i0 + a_01*N_i1 + coop_const;
            B_i1 = a_10*N_i0 + a_11*N_i1 + guilt_const;
            
            // state change
            if (state[i]==0)
            {
                // if B1>B0, they jump with rate 1 scaled by the "markov rate" and "dt"
                // otherwise, they don't jump
                if (B_i1 > B_i0)
                {
                    state[i] = (bool) (rand()/RAND_MAX < (1 - exp(-markov_rate*dt)))==1;
                }
            } else
            {
                if (B_i0 > B_i1)
                {
                    state[i] = (bool) (rand()/RAND_MAX < (1 - exp(-markov_rate*dt)))==0;
                }
            }
        }
    }
}
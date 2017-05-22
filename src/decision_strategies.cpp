//
//  decision_strategies.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 05/15/17.
//  Copyright © 2017 Daniel Weser. All rights reserved.
//

#include "decision_strategies.hpp"
#include "parameters_xml.hpp"
#include "fn_neighbors.hpp"

#include <iostream>

#include <cstdlib>
#include <omp.h>
#include <cmath>
#include <math.h>
using namespace std;



void dec_linear_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
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



void dec_nonlinear_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    double p_A  = 0;
    double p_B  = 0;
    double l_AB = 0;
    double l_BA = 0;
    
    // parameters for convenience
    float alpha = parameters.MARKOV_RATE;
    float gamma = parameters.GAMMA;
    float dt = parameters.DT;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for
        for (int i=0; i<parameters.N; i++)
        {
            // densities
            p_A = fn_count_states(neighbors[i], state_old, 0) / (M_PI*pow(parameters.L,2));
            p_B = fn_count_states(neighbors[i], state_old, 1) / (M_PI*pow(parameters.L,2));

            // payoffs
            l_AB = gamma + alpha * max(p_B-p_A, 0.0);
            l_BA = gamma + alpha * max(p_A-p_B, 0.0);

            // state change
            if (state_old[i]==0)
            {
                state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-l_AB*dt))) == 1;
            } else
            {
                state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-l_BA*dt))) == 0;
            }
        }
    }
}



void dec_norm_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    int   N_i0 = 0;
    int   N_i1 = 0;
    float B_i0 = 0;
    float B_i1 = 0;
    float temp_B0 = 0;
    float temp_B1 = 0;
    
    // parameters for convenience
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
            N_i0 = fn_count_states(neighbors[i], state_old, 0);
            N_i1 = fn_count_states(neighbors[i], state_old, 1);

            // payoffs
            temp_B0 = a_00*N_i0 + a_01*N_i1 + coop_const;
            temp_B1 = a_10*N_i0 + a_11*N_i1 - guilt_const;
            B_i0 = markov_rate * temp_B0 / (temp_B0 + temp_B1);
            B_i1 = markov_rate * temp_B1 / (temp_B0 + temp_B1);
            
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



void dec_ising(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
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
            N_m1 = fn_count_states(neighbors[i], state_old, 0);
            N_p1 = fn_count_states(neighbors[i], state_old, 1);

            summation = (-1)*N_m1 + (1)*N_p1 + (N_m1+N_p1)*ising_h;
            rate = exp(-ising_beta*state[i]*summation);

            // state change
            if (state_old[i]==0)
            {
                state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-rate*dt))) == 1;
            } else
            {
                state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-rate*dt))) == 0;
            }
        }
    }
}



void dec_br(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    long   N_i0 = 0;
    long   N_i1 = 0;
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

    // loop
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for
        for (int i=0; i<parameters.N; i++)
        {
            // number of neighbors
            N_i0 = fn_count_states(neighbors[i], state_old, 0);
            N_i1 = fn_count_states(neighbors[i], state_old, 1);

            // payoffs
            B_i0 = a_00*N_i0 + a_01*N_i1 + coop_const;
            B_i1 = a_10*N_i0 + a_11*N_i1 + guilt_const;
            
            // state change
            if (state_old[i]==0)
            {
                // if B1>B0, they jump with rate 1 scaled by the "markov rate" and "dt"
                // otherwise, they don't jump
                if (B_i1 > B_i0)
                {
                    state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-markov_rate*dt))) == 1;
                }
            } else
            {
                if (B_i0 > B_i1)
                {
                    state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-markov_rate*dt))) == 0;
                }
            }
        }
    }
}



void dec_threshold_vm(bool state[], bool state_old[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
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
            N_i0 = fn_count_states(neighbors[i], state_old, 0);
            N_i1 = fn_count_states(neighbors[i], state_old, 1);
            
            // state change
            if (state_old[i]==0)
            {
                // if N1>=threshold, they jump with rate 1 scaled by the "markov rate" and "dt"
                // otherwise, they don't jump
                if (N_i1 >= threshold)
                {
                    state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-markov_rate*dt))) == 1;
                } else
                {
                    state[i] = state[i];
                }
            } else
            {
                if (N_i0 >= threshold)
                {
                    state[i] = (double(rand())/double(RAND_MAX) < (1 - exp(-markov_rate*dt))) == 0;
                } else
                {
                    state[i] = state[i];
                }
            }
        }
    }
}
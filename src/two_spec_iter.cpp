//
//  two_spec_iter.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "two_spec_iter.hpp"
#include "game_linear_vm.hpp"
#include "fn_phi.hpp"
#include "fn_distance.hpp"
#include "parameters.hpp"
#include "fn_neighbors.hpp"

#include <omp.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

void two_spec_iter(double xy[][2], bool state[], int neighbors[][100], PARAMETERS &parameters)
{
    // new coordinates
    if (parameters.get_SPATIAL())
    {
        double desired[2] = {0,0};
        int nb_j = 0;
        double dxdy[parameters.get_N()][2];
        double distance = 0;
        int num_neighbs = 0;
        
        // loop
        #pragma omp parallel num_threads(4)
        {
            #pragma omp for
            for (int i=0; i<parameters.get_N(); i++)
            {
                // summation for defective with phi_1
                if (state[i])
                {
                    dxdy[i][0] = desired[0];
                    dxdy[i][1] = desired[1];
                    
                    // count neighbors for ease of loop
                    num_neighbs = fn_count_neighbors(neighbors[i]);
                    
                    // loop through neighbors
                    for (int j=0; j<num_neighbs; j++)
                    {
                        nb_j = neighbors[i][j];
                        distance = (double) fn_distance(xy[i][0], xy[i][1], xy[nb_j][0], xy[nb_j][1]);
                        
                        // desired + phi_1(d(x_j,x_i))*(x_j-x_i)/d(x_j,x_i)
                        dxdy[i][0] += (double) fn_phi1(distance, parameters.get_R_DEF()) * (xy[i][0] - xy[nb_j][0])/distance;
                        dxdy[i][1] += (double) fn_phi1(distance, parameters.get_R_DEF()) * (xy[i][1] - xy[nb_j][1])/distance;
                    }
                } else
                // summation for cooperative with phi_0
                {
                    dxdy[i][0] = desired[0];
                    dxdy[i][1] = desired[1];

                    // count neighbors for ease of loop
                    num_neighbs = fn_count_neighbors(neighbors[i]);
                    
                    
                    // loop through neighbors
                    for (int j=0; j<num_neighbs; j++)
                    {
                        nb_j = neighbors[i][j];
                        distance = (double) fn_distance(xy[i][0], xy[i][1], xy[nb_j][0], xy[nb_j][1]);
                        
                        // desired + phi_0(d(x_j,x_i))*(x_j-x_i)/d(x_j,x_i)
                        dxdy[i][0] += (double) fn_phi0(distance, parameters.get_R_COOP()) * (xy[i][0] - xy[nb_j][0])/distance;
                        dxdy[i][1] += (double) fn_phi0(distance, parameters.get_R_COOP()) * (xy[i][1] - xy[nb_j][1])/distance;
                    }
                }
            }
        }
        // commit changes
        #pragma omp for
        for (int i=0; i<parameters.get_N(); i++)
        {
            xy[i][0] += dxdy[i][0]*parameters.get_DT();
            xy[i][1] += dxdy[i][1]*parameters.get_DT();
        }

    }
}
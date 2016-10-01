//
//  two_spec_iter.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "two_spec_iter.hpp"
#include "fn_neighbors.hpp"
#include "fn_phi.hpp"
#include "fn_distance.hpp"
#include "parameters_xml.hpp"
#include "xy_struct.hpp"

#include <omp.h>
using namespace std;

void two_spec_iter(XY &xy, bool state[], int neighbors[][100], parameters &parameters, const int NUM_THREADS)
{
    // new coordinates
    if (parameters.SPATIAL)
    {
        double  desired[2] = {0,0};
        double  distance = 0;
        double  dt = (double) parameters.DT;
        int     nb_j = 0;
        long    num_neighbs = 0;

        // loop
        #pragma omp parallel num_threads(NUM_THREADS)
        {
            #pragma omp for
            for (int i=0; i<parameters.N; i++)
            {
                xy.pts[i].x += dt * desired[0];
                xy.pts[i].y += dt * desired[1];
                
                // summation for defective with phi_1
                if (state[i])
                {
                    // count neighbors
                    num_neighbs = fn_count_neighbors(neighbors[i]);
                    
                    // loop through neighbors
                    for (int j=0; j<num_neighbs; j++)
                    {
                        nb_j = neighbors[i][j];
                        distance = fn_distance(xy.pts[i].x, xy.pts[i].y, xy.pts[nb_j].x, xy.pts[nb_j].y);
                        
                        // desired + phi_1(d(x_j,x_i))*(x_j-x_i)/d(x_j,x_i)
                        xy.pts[i].x += dt * fn_phi1(distance, parameters.R_DEF) * (xy.pts[i].x - xy.pts[nb_j].x)/distance;
                        xy.pts[i].y += dt * fn_phi1(distance, parameters.R_DEF) * (xy.pts[i].y - xy.pts[nb_j].y)/distance;
                    }
                } else
                // summation for cooperative with phi_0
                {
                    
                    // count neighbors
                    num_neighbs = fn_count_neighbors(neighbors[i]);
                    
                    // loop through neighbors
                    for (int j=0; j<num_neighbs; j++)
                    {
                        nb_j = neighbors[i][j];
                        distance = fn_distance(xy.pts[i].x, xy.pts[i].y, xy.pts[nb_j].x, xy.pts[nb_j].y);
                        
                        // desired + phi_0(d(x_j,x_i))*(x_j-x_i)/d(x_j,x_i)
                        xy.pts[i].x += dt * fn_phi0(distance, parameters.R_DEF) * (xy.pts[i].x - xy.pts[nb_j].x)/distance;
                        xy.pts[i].y += dt * fn_phi0(distance, parameters.R_DEF) * (xy.pts[i].y - xy.pts[nb_j].y)/distance;
                    }
                }
            }
        }
    }
}
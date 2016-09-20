//
//  diffusion.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/13/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "parameters.hpp"
#include "init_functions.hpp"
#include "two_spec_iter.hpp"
#include "fn_neighbors.hpp"
#include "game_linear_vm.hpp"
#include "fn_file_print.hpp"
#include "str_fixed_length.hpp"


#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


int main(int argc, char *argv[])
{
    // parameters construction
    PARAMETERS parameters ("../parameters/parameters.txt");
    int N = parameters.get_N();
    
    // values calculated based on parameters
    const int     NUM_DEFECT_INIT = round(N/2);
    const int     NTIME = floor(parameters.get_TIME()/parameters.get_DT()+.5);
    
    // main structures
    double  xy[N][2];
    bool    state[N];
    int     neighbors[N][100];
    
    // file name and number string for data writing
    string file_path = "../data/";
    string num_str = "";
    
    // seed random number generator
    srand(1);
    
    // clock for elapsed time output
    clock_t time;
    double elapsed = 0;
    
    
    // generate initial condition
    if (parameters.get_IC() == "lattice" || parameters.get_IC() == "block")
    {
        // initialize structure of lattice
        int lattice_height = round(sqrt(N));
        vector<int> lattice_x = generateRange(1, 1, lattice_height);
        vector<int> lattice_y = generateRange(1, 1, lattice_height);
        vector< vector<int> > mesh_x(lattice_height, vector<int>(lattice_height));
        vector< vector<int> > mesh_y(lattice_height, vector<int>(lattice_height));
        
        // build lattice coordinates
        meshGrid(mesh_x, mesh_y, lattice_x, lattice_y);
        
        for (int col=0; col<lattice_height; col++)
        {
            for (int row=0; row<lattice_height; row++)
            {
                xy[col*lattice_height + row][0] = mesh_x[row][col];
                xy[col*lattice_height + row][1] = mesh_y[row][col];
            }
        }
    } else
    {
        uniformXY(xy, N, parameters.get_SPREAD());
    }
    
    // generate states
    initState(state, N, NUM_DEFECT_INIT, parameters.get_DECISION_MODEL(), parameters.get_IC());
    
    
    time = clock();

    // iteration
    for (int t=0; t<NTIME; t++)
    {
        
        // write data
        num_str = str_fixed_length(t);
        fn_file_print_xy(xy, file_path, N, num_str);
        fn_file_print_state(state, file_path, N, num_str);
        
        
        // set neighbors to all -1's
        memset(neighbors, -1, sizeof(int)*N*2);
        fn_neighbors(xy, state, neighbors, N, parameters.get_R_COOP(), parameters.get_R_DEF());
        
        // new states
        if (parameters.get_DECISION_MODEL() == "linear vm")
        {
            game_linear_vm(xy, state, neighbors, parameters);
        }
        
        // find neighbors again
        memset(neighbors, -1, sizeof(int)*N*2);
        fn_neighbors(xy, state, neighbors, N, parameters.get_R_COOP(), parameters.get_R_DEF());
        
        // new xy-coordinates
        two_spec_iter(xy, state, neighbors, parameters);
    }
    

    elapsed = clock() - time;
    printf ("Run time: %f seconds\n",((float)elapsed)/CLOCKS_PER_SEC);
    
    return 0;
}

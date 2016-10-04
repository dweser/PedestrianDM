//
//  main_pedestrianDM.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/13/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "parameters_xml.hpp"
#include "xy_struct.hpp"
#include "init_functions.hpp"
#include "two_spec_iter.hpp"
#include "fn_neighbors.hpp"
#include "fn_file_print.hpp"
#include "str_fixed_length.hpp"
#include "game_threshold_vm.hpp"
#include "game_linear_vm.hpp"
#include "game_norm_vm.hpp"
#include "game_br.hpp"
#include "game_ising.hpp"
#include "nanoflann.hpp"

#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <chrono>
#include <ctime>
#include <vector>
#include <string>
#include <cstring>
#include <utility>

using namespace std;
using namespace nanoflann;


int main(int argc, char *argv[])
{
    // parameters construction
    parameters parameters("../parameters/parameters.xml");
    int N = parameters.N;

    // file name and number string for data writing
    string data_path = "../data/";
    string num_str = "";
    // clear existing data
    string shell_command = "for f in " + data_path + '*' + "; do rm $f; done";
    system(shell_command.c_str());

    // values calculated based on parameters
    const int     NUM_DEFECT_INIT = round(N/2);
    const int     NTIME = floor(parameters.TIME/parameters.DT+.5);
    const int     NUM_THREADS = ceil((double) N/2000);

    // main structures
    XY      xy; 
    xy.pts.resize(N);
    bool    state[N];
    int     neighbors[N][100];

    // arrays to hold old states and changes in xy-coordinates
    bool    state_old[N];
    double  dxdy[N][2];

    // pointers to states to swap
    bool    *state_ptr = state;
    bool    *state_old_ptr = state_old;
    
    // construct a k-d tree index for neighbors searches
    typedef KDTreeSingleIndexAdaptor<L2_Simple_Adaptor<double, XY>, XY, 2 /* dim */> tree;

    // seed random number generator
    srand(parameters.SEED_NUMBER);
    
    // clock for elapsed time output
    chrono::time_point<chrono::system_clock> start, end;
    
    // generate initial condition
    if (parameters.IC == "lattice" || parameters.IC == "block")
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
                xy.pts[col*lattice_height + row].x = (double) mesh_x[row][col];
                xy.pts[col*lattice_height + row].y = (double) mesh_y[row][col];
            }
        }
    } else
    {
        uniformXY(xy, N, parameters.SPREAD, parameters.LENGTH, parameters.WIDTH);
    }

    // initiate xy
    for (int i=0; i<N; i++)
    {
        xy.pts[i].x = xy_old.pts[i].x;
        xy.pts[i].y = xy_old.pts[i].y;
    }

    // generate states
    initState(state_old, N, NUM_DEFECT_INIT, parameters.DECISION_MODEL, parameters.IC);

    // iteration
    start = chrono::system_clock::now();
    for (int t=0; t<NTIME; t++)
    {
        // write data
        num_str = str_fixed_length(t);
        fn_file_print_xy(xy, data_path, N, num_str, parameters.SEED_NUMBER);
        fn_file_print_state(state_old, data_path, N, num_str, parameters.SEED_NUMBER);

        // build tree for finding neighbors
        tree   index(2 /*dim*/, xy, KDTreeSingleIndexAdaptorParams(200 /* max leaf */) );
        index.buildIndex();

        // find neighbors
        fn_neighbors(xy, state_old, neighbors, N, parameters.R_COOP, parameters.R_DEF, index);

        // new states
        if (parameters.DECISION_MODEL == "linear vm")
        {
            game_linear_vm(state, state_old, neighbors, parameters, NUM_THREADS);
        } else if (parameters.DECISION_MODEL == "norm vm")
        {
            game_norm_vm(state, state_old, neighbors, parameters, NUM_THREADS);
        } else if (parameters.DECISION_MODEL == "threshold vm")
        {
            game_threshold_vm(state, state_old, neighbors, parameters, NUM_THREADS);
        } else if (parameters.DECISION_MODEL == "br")
        {
            game_br(state, state_old, neighbors, parameters, NUM_THREADS);
        } else
        {
            game_ising(state, state_old, neighbors, parameters, NUM_THREADS);
        }

        // new xy-coordinates
        two_spec_iter(xy, dxdy, state, neighbors, parameters, NUM_THREADS);

        // swap states
        swap(state_ptr, state_old_ptr);
    }
    
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    printf ("Elapsed time: %f seconds\n",(float) elapsed_seconds.count());
    
    return 0;
}

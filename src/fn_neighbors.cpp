//
//  fn_neighbors.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "fn_neighbors.hpp"
#include "fn_distance.hpp"
#include "nanoflann.hpp"
#include "xy_struct.hpp"

#include <vector>
#include <cmath>
using namespace std;
using namespace nanoflann;

void fn_neighbors(XY &xy, bool state[], int neighbors[][100], int n, float r_coop, float r_def,
                  KDTreeSingleIndexAdaptor<L2_Simple_Adaptor<double, XY>, XY, 2 /* dim */> &tree)
{
    long num_matches;
    double query_pt[2];
    // vector to hold neighbors
    std::vector<std::pair<size_t, double> > matches;

    // default parameters for range search
    nanoflann::SearchParams params;

    for (int i=0; i<n; i++)
    {
        query_pt[0] = xy.pts[i].x;
        query_pt[1] = xy.pts[i].y;

        if (state[i]==1)
            num_matches = tree.radiusSearch(&query_pt[0], sqrt(r_def), matches, params);
        else
            num_matches = tree.radiusSearch(&query_pt[0], sqrt(r_coop), matches, params);

        // exclude herself
        for (int j=1; j<num_matches; j++)
        {
            neighbors[i][j-1] = matches[j].first;
        }
        for (int j=(num_matches-1); j<100; j++)
        {
            neighbors[i][j] = -1;
        }
    }
    
}

// only pass one row of neighbors at a time
int fn_count_states(int neighbors[100], bool state[], int target)
{
    int count = 0;
    
    for (int i=0; i<100; i++)
    {
        if (neighbors[i] != -1)
        {
            if (state[neighbors[i]] == target)
            {
                count++;
            }
        }
    }
    return count;
}


// only pass one row of neighbors at a time
int fn_count_neighbors(int neighbors[100])
{
    int count = 0;
    
    for (int i=0; i<100; i++)
    {
        if (neighbors[i] != -1)
        {
            count++;
        }
    }
    return count;
}

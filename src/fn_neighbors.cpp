//
//  fn_neighbors.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "fn_neighbors.hpp"
#include "fn_distance.hpp"

#include <omp.h>
#include <vector>
using namespace std;

void fn_neighbors(double xy[][2], bool state[], int neighbors[][100], int n, float r_coop, float r_def, const int NUM_THREADS)
{
    // vector of counters for keeping track of the number of neighbors each player has
    vector<int> count_neighbors(n);
    int count_init = 0;

    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp for
        // loop through players and check all players above them to see if they're within distance r
        for (int init=0; init<n; init++)
        {
            if (state[init]==0)
            {
                for (int search=(init+1); search<n; search++)
                {
                    // since cooperative players do not always have reciprocal neighbors,
                    // we need to check separately if players i and j are both neighbors
                    // of each other
                    
                    // if within distance r_coop, then add index to temp indices
                    if (fn_distance_lt(xy[init][0], xy[init][1], xy[search][0], xy[search][1], r_coop))
                    {
                        // add upper player to lower player's neighbors
                        neighbors[init][count_init] = search;
                        count_init++;
                        
                        // check search player to see if init player is also their neighbor
                        // if they're defective, we need to check radius
                        if (state[search]==1)
                        {
                            if (fn_distance_lt(xy[init][0], xy[init][1], xy[search][0], xy[search][1], r_def))
                            {
                                // add lower player to upper player's neighbors
                                neighbors[search][count_neighbors[search]] = init;
                                count_neighbors[search]++;
                            }
                        // if they're also cooperative, we know they're neighbors
                        } else
                        {
                            // add lower player to upper player's neighbors
                            neighbors[search][count_neighbors[search]] = init;
                            count_neighbors[search]++;
                        }
                    }
                }
            } else
            {
                for (int search=(init+1); search<n; search++)
                {
                    // since they're defective, we know that all defective player's neighbors
                    // are reciprocal, so we can avoid the above checks
                    if (fn_distance_lt(xy[init][0], xy[init][1], xy[search][0], xy[search][1], r_def))
                    {
                        // add upper player to lower player's neighbors
                        neighbors[init][count_init] = search;
                        count_init++;
                        
                        // add lower player to upper player's neighbors
                        neighbors[search][count_neighbors[search]] = init;
                        count_neighbors[search]++;
                    }
                }
            }
            // update neighbors counter and clear counter
            count_neighbors[init] = count_init;
            count_init = 0;
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

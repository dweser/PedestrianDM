//
//  init_functions.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "init_functions.hpp"
#include "xy_struct.hpp"
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// equivalent to "linspace" function in MATLAB
vector<int> generateRange(int a, int b, int c)
{
    vector<int> array;
    while(a <= c) {
        array.push_back(a);
        a += b;
    }
    return array;
}

// equivalent to "meshgrid" function in MATLAB
void meshGrid(vector< vector<int> >& array1, vector< vector<int> >& array2, vector<int> linspace1, vector<int> linspace2)
{
    for (unsigned int col=0; col<linspace1.size(); col++)
    {
        for (unsigned int row=0; row<linspace2.size(); row++)
        {
            array1[row][col] = linspace1[col];
            array2[row][col] = linspace2[row];
        }
    }
}

// uniform random x
void uniformXY(XY &xy, int N, float spread, int length, int width)
{    
    for (int i=0; i<N; i++)
    {
        xy.pts[i].x = spread * length * rand()/RAND_MAX;
        xy.pts[i].y = spread * width  * rand()/RAND_MAX;
    }
}

// initialize array of states
void initState(bool array[], int N, int num_def, string dec_model, string ic)
{
    // set first n=num_def as defective, rest as cooperative
    for (int i=0; i<num_def; i++)
    {
        array[i] = false;
    }
    for (int i=num_def; i<N; i++)
    {
        array[i] = true;
    }
    
    // if IC is not block, then randomly shuffle the states
    if (ic != "block")
    {
        random_shuffle(array, array+N-1);
    }
}


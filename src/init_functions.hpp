//
//  init_functions.hpp
//  diffusion
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef init_functions_hpp
#define init_functions_hpp

#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> generateRange(int a, int b, int c);
void meshGrid(vector< vector<int> >& array1, vector< vector<int> >& array2, vector<int> linspace1, vector<int> linspace2);
void randomArray(double array[][2], int N);
void uniformXY(double xy[][2], int N, float spread);
void initState(bool array[], int N, int num_def, string dec_model, string ic);
void splitNeighbors(int neighbors[][100], int split_neighbors[][100], int start, int end);

#endif /* init_functions_hpp */

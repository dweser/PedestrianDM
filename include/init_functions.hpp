//
//  init_functions.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef init_functions_hpp
#define init_functions_hpp

#include <vector>
#include <string>

std::vector<int> generateRange(int a, int b, int c);
void meshGrid(std::vector< std::vector<int> >& array1, std::vector< std::vector<int> >& array2, std::vector<int> linspace1, std::vector<int> linspace2);
void randomArray(double array[][2], int N);
void uniformXY(double xy[][2], int N, float spread, int length, int width);
void initState(bool array[], int N, int num_def, std::string dec_model, std::string ic);
void splitNeighbors(int neighbors[][100], int split_neighbors[][100], int start, int end);

#endif /* init_functions_hpp */

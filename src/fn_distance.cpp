//
//  fn_distance.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "fn_distance.hpp"

#include <stdio.h>
#include <cmath>

double fn_distance(double x1, double y1, double x2, double y2)
{
    return (double) std::sqrt( (double) std::pow(x1-x2, 2) + (double) std::pow(y1-y2, 2) );
}

bool fn_distance_lt(double x1, double y1, double x2, double y2, double radius)
{
    return fn_distance(x1,y1,x2,y2) < radius;
}
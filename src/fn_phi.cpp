//
//  fn_phi.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/14/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "fn_phi.hpp"

double fn_phi0(double distance, float r_coop)
{
    double out = 0;
    
    if (distance < r_coop)
    {
        out = ( (double) 1/distance - (double) 1/r_coop);
    }
    
    return out;
}

double fn_phi1(double distance, float r_def)
{
    double out = 0;
    
    if (distance < r_def)
    {
        out = ( (double) 1/distance - (double) 1/r_def);
    }
    
    return out;
}
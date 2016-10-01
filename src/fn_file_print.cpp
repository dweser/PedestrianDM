//
//  fn_file_print.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/16/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "fn_file_print.hpp"
#include "xy_struct.hpp"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void fn_file_print_xy(XY &xy, string path, int n, string iter_string, int seed_num)
{
    // to write data
    ofstream outFile_x,outFile_y;
    stringstream name_x_nb, name_y_nb;
    
    name_x_nb << path << "particleX_" << "Seed" << seed_num << "_" << iter_string << ".dat";
    name_y_nb << path << "particleY_" << "Seed" << seed_num << "_" << iter_string << ".dat";
    outFile_x.open(name_x_nb.str().c_str(),  ios::out|ios::binary);
    outFile_y.open(name_y_nb.str().c_str(),  ios::out|ios::binary);
    
    for (int i=0; i<n; i++)
    {
        outFile_x.write( (char*)&xy.pts[i].x, sizeof(double) );
        outFile_y.write( (char*)&xy.pts[i].y, sizeof(double) );
    }
    outFile_x.close();
    outFile_y.close();
}

void fn_file_print_state(bool state[], string path, int n, string iter_string, int seed_num)
{
    // to write data
    ofstream outFile;
    stringstream name_nb;
    
    name_nb << path << "particleS_" << "Seed" << seed_num << "_" << iter_string << ".dat";
    outFile.open(name_nb.str().c_str(), ios::out|ios::binary);
    
    for (int i=0; i<n; i++)
    {
        outFile.write( (char*)&state[i], sizeof(bool) );
    }
    outFile.close();
}
//
//  fn_file_print.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/16/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "fn_file_print.hpp"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void fn_file_print_xy(double xy[][2], string path, int n, string iter_string)
{
    // to write data
    ofstream outFile_x,outFile_y;
    std::stringstream name_x_nb, name_y_nb;
    
    name_x_nb << path << "particleX_" << iter_string;
    name_y_nb << path << "particleY_" << iter_string;
    outFile_x.open(name_x_nb.str().c_str());
    outFile_y.open(name_y_nb.str().c_str());
    
    for (int i=0; i<n; i++)
    {
        outFile_x << xy[i][0] << endl;
        outFile_y << xy[i][1] << endl;
    }
    outFile_x.close();
    outFile_y.close();
}

void fn_file_print_state(bool state[], string path, int n, string iter_string)
{
    // to write data
    //kop if (present(Nbre_iter)) Then
    ofstream outFile;
    std::stringstream name_nb;
    
    name_nb << path << "particleS_" << iter_string;
    outFile.open(name_nb.str().c_str());
    
    for (int i=0; i<n; i++)
    {
        outFile << state[i] << endl;
    }
    outFile.close();
}
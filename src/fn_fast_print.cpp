//
//  fn_fast_print.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/19/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "fn_fast_print.hpp"
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

void fn_fast_print_xy(double xy[][2], string path, int n, string iter_string)
{
	FILE* xFile, yFile;
	char x_name[sizeof(path)+10+9];
	char y_name[sizeof(path)+10+9];

	stringstream name_x_nb, name_y_nb;
    name_x_nb << path << "particleX_" << iter_string;
    name_y_nb << path << "particleY_" << iter_string;

    x_name = name_x_nb.str().c_str();
    y_name = name_y_nb.str().c_str();

    xFile = fopen (x_name, "wb");
    yFile = fopen (y_name, "wb");

    for (int i=0; i<n; i++)
    {
		fwrite (xy[i][0], sizeof(double), 1, xFile);
		fwrite (xy[i][1], sizeof(double), 1, yFile);
	}

	fclose (xFile);
	fclose (yFile);
}

void fn_fast_print_state(bool state[], string path, int n, string iter_string)
{
	FILE* sFile;

	stringstream name_s_nb, name_y_nb;
    name_s_nb << path << "particleS_" << iter_string;

    sFile = fopen (name_s_nb.str().c_str(), "wb");

	fwrite (state, sizeof(bool), n, sFile);

	fclose (sFile);
}
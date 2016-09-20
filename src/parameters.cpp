//
//  parameters.cpp
//  diffusion
//
//  Created by Daniel Weser on 9/15/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "parameters.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <cstdlib>
using namespace std;


// constructor
PARAMETERS::PARAMETERS(string file_path)
{
    string line;
    
    ifstream parameters_file (file_path.c_str());
    if (parameters_file.is_open())
    {
        // N
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_N(line);
        
        // DT
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_DT(line);
        
        // TIME
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_TIME(line);
        
        
        // SPATIAL
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_SPATIAL(line);
        
        // LENGTH
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_LENGTH(line);
        
        // WIDTH
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_WIDTH(line);
        
        // IC
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_IC(line);
        
        // SPREAD
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_SPREAD(line);
        
        // R_COOP
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_R_COOP(line);
        
        // R_DEF
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_R_DEF(line);
        
        // DECISION MODEL
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_DECISION_MODEL(line);
        
        // a_00
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_a_00(line);
        
        // a_01
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_a_01(line);
        
        // a_10
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_a_10(line);
        
        // a_11
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_a_11(line);
        
        // MARKOV RATE
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_MARKOV_RATE(line);
        
        // THRESHOLD
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_THRESHOLD(line);
        
        // COOP CONST
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_COOP_CONST(line);
        
        // GUILT CONST
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_GUILT_CONST(line);
        
        // ISING BETA
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_ISING_BETA(line);
        
        // ISING H
        getline(parameters_file,line);
        getline(parameters_file,line);
        set_ISING_H(line);
    } else
    {
        cout << "Error: Could not open file." << endl;
        exit(1);
    }
}

// member functions
void PARAMETERS::set_N(string line)
{
    if ( ! (istringstream(line) >> N) ) exit(-2);
}

void PARAMETERS::set_DT(string line)
{
    if ( ! (istringstream(line) >> DT) ) exit(-2);
}

void PARAMETERS::set_TIME(string line)
{
    if ( ! (istringstream(line) >> TIME) ) exit(-2);
}

void PARAMETERS::set_SPATIAL(string line)
{
    if ( ! (istringstream(line) >> SPATIAL) ) exit(-2);
}

void PARAMETERS::set_LENGTH(string line)
{
    if ( ! (istringstream(line) >> LENGTH) ) exit(-2);
}

void PARAMETERS::set_WIDTH(string line)
{
    if ( ! (istringstream(line) >> WIDTH) ) exit(-2);
}

void PARAMETERS::set_IC(string line)
{
    IC = line;
}

void PARAMETERS::set_SPREAD(string line)
{
    if ( ! (istringstream(line) >> SPREAD) ) exit(-2);
}

void PARAMETERS::set_R_COOP(string line)
{
    if ( ! (istringstream(line) >> R_COOP) ) exit(-2);
}

void PARAMETERS::set_R_DEF(string line)
{
    if ( ! (istringstream(line) >> R_DEF) ) exit(-2);
}

void PARAMETERS::set_DECISION_MODEL(string line)
{
    DECISION_MODEL = line;
}

void PARAMETERS::set_a_00(string line)
{
    if ( ! (istringstream(line) >> a_00) ) exit(-2);
}

void PARAMETERS::set_a_01(string line)
{
    if ( ! (istringstream(line) >> a_01) ) exit(-2);
}

void PARAMETERS::set_a_10(string line)
{
    if ( ! (istringstream(line) >> a_10) ) exit(-2);
}

void PARAMETERS::set_a_11(string line)
{
    if ( ! (istringstream(line) >> a_11) ) exit(-2);
}

void PARAMETERS::set_MARKOV_RATE(string line)
{
    if ( ! (istringstream(line) >> MARKOV_RATE) ) exit(-2);
}

void PARAMETERS::set_THRESHOLD(string line)
{
    if ( ! (istringstream(line) >> THRESHOLD) ) exit(-2);
}

void PARAMETERS::set_COOP_CONST(string line)
{
    if ( ! (istringstream(line) >> COOP_CONST) ) exit(-2);
}

void PARAMETERS::set_GUILT_CONST(string line)
{
    if ( ! (istringstream(line) >> GUILT_CONST) ) exit(-2);
}

void PARAMETERS::set_ISING_BETA(string line)
{
    if ( ! (istringstream(line) >> ISING_BETA) ) exit(-2);
}

void PARAMETERS::set_ISING_H(string line)
{
    if ( ! (istringstream(line) >> ISING_H) ) exit(-2);
}

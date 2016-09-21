//
//  parameters.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/15/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "parameters.hpp"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

parameters::parameters(string file_path)
{
    string line;
    
    ifstream parameters_file (file_path.c_str());
    if (parameters_file.is_open())
    {
        // N
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> N) ) exit(-2);

        // DT
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> DT) ) exit(-2);
        
        // TIME
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> TIME) ) exit(-2);
        
        
        // SPATIAL
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> SPATIAL) ) exit(-2);
        
        // LENGTH
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> LENGTH) ) exit(-2);
        
        // WIDTH
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> WIDTH) ) exit(-2);
        
        // IC
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> IC) ) exit(-2);
        
        // SPREAD
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> SPREAD) ) exit(-2);
        
        // R_COOP
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> R_COOP) ) exit(-2);
        
        // R_DEF
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> R_DEF) ) exit(-2);
        
        // DECISION MODEL
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> DECISION_MODEL) ) exit(-2);
        
        // a_00
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> a_00) ) exit(-2);
        
        // a_01
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> a_01) ) exit(-2);
        
        // a_10
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> a_10) ) exit(-2);
        
        // a_11
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> a_11) ) exit(-2);
        
        // MARKOV RATE
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> MARKOV_RATE) ) exit(-2);
        
        // THRESHOLD
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> THRESHOLD) ) exit(-2);
        
        // COOP CONST
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> COOP_CONST) ) exit(-2);
        
        // GUILT CONST
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> GUILT_CONST) ) exit(-2);
        
        // ISING BETA
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> ISING_BETA) ) exit(-2);
        
        // ISING H
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> ISING_H) ) exit(-2);

        // SEED NUMBER
        getline(parameters_file,line);
        getline(parameters_file,line);
        if ( ! (istringstream(line) >> SEED_NUMBER) ) exit(-2);
    }
}







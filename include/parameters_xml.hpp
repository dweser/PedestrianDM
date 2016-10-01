//
//  parameters_xml.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/15/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef parameters_xml_hpp
#define parameters_xml_hpp

#include <string>

struct parameters
{
	int         N;
    float       DT;
    float       TIME;
    bool        SPATIAL;
    int         LENGTH;
    int         WIDTH;
    std::string IC;
    float       SPREAD;
    float       R_COOP;
    float       R_DEF;
    std::string DECISION_MODEL;
    float       a_00;
    float       a_01;
    float       a_10;
    float       a_11;
    float       MARKOV_RATE;
    int         THRESHOLD;
    float       COOP_CONST;
    float       GUILT_CONST;
    float       ISING_BETA;
    float       ISING_H;
    int         SEED_NUMBER;

    parameters(std::string file_path);
};

#endif /* parameters_xml_hpp */
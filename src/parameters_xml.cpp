//
//  parameters_xml.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/15/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "parameters_xml.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
using namespace std;

parameters::parameters(string file_path)
{
    string line;

    // Create an empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    // Load the XML file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
    read_xml(file_path, pt);
    
    // N
    N = pt.get<int>("parameters.N");

    // DT
    DT = pt.get<float>("parameters.DT");
    
    // TIME
    TIME = pt.get<int>("parameters.TIME");
    
    // SPATIAL
    SPATIAL = pt.get<bool>("parameters.SPATIAL");
    
    // LENGTH
    LENGTH = pt.get<int>("parameters.LENGTH");
    
    // WIDTH
    WIDTH = pt.get<int>("parameters.WIDTH");
    
    // IC
    IC = pt.get<string>("parameters.IC");
    
    // SPREAD
    SPREAD = pt.get<float>("parameters.SPREAD");
    
    // R_COOP
    R_COOP = pt.get<float>("parameters.R_COOP");
    
    // R_DEF
    R_DEF = pt.get<float>("parameters.R_DEF");

    // DECISION MODEL
    DECISION_MODEL = pt.get<string>("parameters.DECISION_MODEL");
  
    // a_00
    a_00 = pt.get<float>("parameters.a_00");

    // a_01
    a_01 = pt.get<float>("parameters.a_01");
   
    // a_10
    a_10 = pt.get<float>("parameters.a_10");
    
    // a_11
    a_11 = pt.get<float>("parameters.a_11");
   
    // MARKOV RATE
    MARKOV_RATE = pt.get<float>("parameters.MARKOV_RATE");

    // THRESHOLD
    THRESHOLD = pt.get<int>("parameters.THRESHOLD");
  
    // COOP CONST
    COOP_CONST = pt.get<float>("parameters.COOP_CONST");
 
    // GUILT CONST
    GUILT_CONST = pt.get<float>("parameters.GUILT_CONST");

    // ISING BETA
    ISING_BETA = pt.get<float>("parameters.ISING_BETA");

    // ISING H
    ISING_H = pt.get<float>("parameters.ISING_H");

    // SEED NUMBER
    SEED_NUMBER = pt.get<int>("parameters.SEED_NUMBER");
}
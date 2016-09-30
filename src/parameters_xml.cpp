//
//  parameters_xml.cpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/15/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#include "parameters_xml.hpp"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <string>
using namespace std;
using namespace rapidxml;

parameters::parameters(string file_path)
{
    // Create an empty xml document object
    xml_document<> doc;

    // Load the XML file into the xml object and parse it
    file<> xmlFile(file_path.c_str());
    doc.parse<0>(xmlFile.data());

    // find the root node
    xml_node<>* root = doc.first_node("parameters");
    
    // N
    N = atoi(root->first_node("N")->value());

    // DT
    DT = atof(root->first_node("DT")->value());
    
    // TIME
    TIME = atoi(root->first_node("TIME")->value());
    
    // SPATIAL
    SPATIAL = (bool) atoi(root->first_node("SPATIAL")->value());
    
    // LENGTH
    LENGTH = atoi(root->first_node("LENGTH")->value());
    
    // WIDTH
    WIDTH = atoi(root->first_node("WIDTH")->value());
    
    // IC
    WIDTH = atoi(root->first_node("WIDTH")->value());
    
    // SPREAD
    SPREAD = atof(root->first_node("SPREAD")->value());
    
    // R_COOP
    R_COOP = atof(root->first_node("R_COOP")->value());
    
    // R_DEF
    R_DEF = atof(root->first_node("R_DEF")->value());

    // DECISION MODEL
    DECISION_MODEL = (string) (root->first_node("DECISION_MODEL")->value());
  
    // a_00
    a_00 = atof(root->first_node("a_00")->value());

    // a_01
    a_01 = atof(root->first_node("a_01")->value());
   
    // a_10
    a_10 = atof(root->first_node("a_10")->value());
    
    // a_11
    a_11 = atof(root->first_node("a_11")->value());
   
    // MARKOV RATE
    MARKOV_RATE = atof(root->first_node("MARKOV_RATE")->value());

    // THRESHOLD
    THRESHOLD = atoi(root->first_node("THRESHOLD")->value());
  
    // COOP CONST
    COOP_CONST = atof(root->first_node("COOP_CONST")->value());
 
    // GUILT CONST
    GUILT_CONST = atof(root->first_node("GUILT_CONST")->value());

    // ISING BETA
    ISING_BETA = atof(root->first_node("ISING_BETA")->value());

    // ISING H
    ISING_H = atof(root->first_node("ISING_H")->value());

    // SEED NUMBER
    SEED_NUMBER = atoi(root->first_node("SEED_NUMBER")->value());
}
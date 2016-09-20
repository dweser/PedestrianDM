//
//  parameters.hpp
//  diffusion
//
//  Created by Daniel Weser on 9/15/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef parameters_hpp
#define parameters_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

class PARAMETERS
{
private:
    int     N;
    float   DT;
    int     TIME;
    bool    SPATIAL;
    int     LENGTH;
    int     WIDTH;
    string  IC;
    float   SPREAD;
    float   R_COOP;
    float   R_DEF;
    string  DECISION_MODEL;
    float   a_00;
    float   a_01;
    float   a_10;
    float   a_11;
    float   MARKOV_RATE;
    int     THRESHOLD;
    float   COOP_CONST;
    float   GUILT_CONST;
    float   ISING_BETA;
    float   ISING_H;
    
public:
    PARAMETERS(string file_path);
    
    void set_N(string line);
    void set_DT(string line);
    void set_TIME(string line);
    void set_SPATIAL(string line);
    void set_LENGTH(string line);
    void set_WIDTH(string line);
    void set_IC(string line);
    void set_SPREAD(string line);
    void set_R_COOP(string line);
    void set_R_DEF(string line);
    void set_DECISION_MODEL(string line);
    void set_a_00(string line);
    void set_a_01(string line);
    void set_a_10(string line);
    void set_a_11(string line);
    void set_MARKOV_RATE(string line);
    void set_THRESHOLD(string line);
    void set_COOP_CONST(string line);
    void set_GUILT_CONST(string line);
    void set_ISING_BETA(string line);
    void set_ISING_H(string line);
    
    int     get_N()                 { return N; }
    float   get_DT()                { return DT; }
    int     get_TIME()              { return TIME; }
    bool    get_SPATIAL()           { return SPATIAL; }
    int     get_LENGTH()            { return LENGTH; }
    int     get_WIDTH()             { return WIDTH; }
    string  get_IC()                { return IC; }
    float   get_SPREAD()            { return SPREAD; }
    float   get_R_COOP()            { return R_COOP; }
    float   get_R_DEF()             { return R_DEF; }
    string  get_DECISION_MODEL()    { return DECISION_MODEL; }
    float   get_a_00()              { return a_00; }
    float   get_a_01()              { return a_01; }
    float   get_a_10()              { return a_10; }
    float   get_a_11()              { return a_11; }
    float   get_MARKOV_RATE()       { return MARKOV_RATE; }
    int     get_THRESHOLD()         { return THRESHOLD; }
    float   get_COOP_CONST()        { return COOP_CONST; }
    float   get_GUILT_CONST()       { return GUILT_CONST; }
    float   get_ISING_BETA()        { return ISING_BETA; }
    float   get_ISING_H()           { return ISING_H; }
};

#endif /* parameters_hpp */

//
//  parameters_class.hpp
//  PedestrianDM
//
//  Created by Daniel Weser on 9/15/16.
//  Copyright © 2016 Daniel Weser. All rights reserved.
//

#ifndef parameters_class_hpp
#define parameters_class_hpp

#include <string>

class PARAMETERS
{
private:
    int         N;
    float       DT;
    int         TIME;
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
    
public:
    PARAMETERS(std::string file_path);
    
    void set_N(std::string line);
    void set_DT(std::string line);
    void set_TIME(std::string line);
    void set_SPATIAL(std::string line);
    void set_LENGTH(std::string line);
    void set_WIDTH(std::string line);
    void set_IC(std::string line);
    void set_SPREAD(std::string line);
    void set_R_COOP(std::string line);
    void set_R_DEF(std::string line);
    void set_DECISION_MODEL(std::string line);
    void set_a_00(std::string line);
    void set_a_01(std::string line);
    void set_a_10(std::string line);
    void set_a_11(std::string line);
    void set_MARKOV_RATE(std::string line);
    void set_THRESHOLD(std::string line);
    void set_COOP_CONST(std::string line);
    void set_GUILT_CONST(std::string line);
    void set_ISING_BETA(std::string line);
    void set_ISING_H(std::string line);
    void set_SEED_NUMBER(std::string line);
    
    int         get_N()                 { return N; }
    float       get_DT()                { return DT; }
    int         get_TIME()              { return TIME; }
    bool        get_SPATIAL()           { return SPATIAL; }
    int         get_LENGTH()            { return LENGTH; }
    int         get_WIDTH()             { return WIDTH; }
    std::string get_IC()                { return IC; }
    float       get_SPREAD()            { return SPREAD; }
    float       get_R_COOP()            { return R_COOP; }
    float       get_R_DEF()             { return R_DEF; }
    std::string get_DECISION_MODEL()    { return DECISION_MODEL; }
    float       get_a_00()              { return a_00; }
    float       get_a_01()              { return a_01; }
    float       get_a_10()              { return a_10; }
    float       get_a_11()              { return a_11; }
    float       get_MARKOV_RATE()       { return MARKOV_RATE; }
    int         get_THRESHOLD()         { return THRESHOLD; }
    float       get_COOP_CONST()        { return COOP_CONST; }
    float       get_GUILT_CONST()       { return GUILT_CONST; }
    float       get_ISING_BETA()        { return ISING_BETA; }
    float       get_ISING_H()           { return ISING_H; }
    int         get_SEED_NUMBER()       { return SEED_NUMBER; }
};

#endif /* parameters_class_hpp */

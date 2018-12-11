#include <iostream>
#include <fstream>
#include <unistd.h>

//codeur 1 eQEP2B_in p8.11 EQEP2A_IN p8.12
//codeur 2 eQEP0B_in p9.27 eQEP0A_in p9.42 (92)

//exemples: 
// Codeur codeur1("/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/");
// Codeur codeur2("/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep/");
// long pos = codeur1.read();

#define DEBUG_CODEUR

#ifndef CODEUR_H
#define CODEUR_H

class Codeur{

public:
    Codeur(std::string eqepPath);
    
    long read();
    
    void set(long pos);
    
    ~Codeur();
    
    
private:
    std::string _eqepPath;
    
    std::ifstream _eqep;
    
    long _ofset;
    
    char _posStr[256];
    
    long _pos;
    
};

#endif
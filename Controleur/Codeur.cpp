#include "Codeur.h"
#include <iostream>
#include <fstream>
#include <unistd.h>


Codeur::Codeur(std::string eqepPath){
    // TODO check files
    
    this->_eqepPath = eqepPath;
    
    // open eqep file
    std::string eqep = this->_eqepPath + "position";
    this->_eqep.open(eqep.c_str());
    
    this->_ofset = 0;
    
    #ifdef DEBUG_CODEUR
        if(! _eqep.is_open()){
           std::cout<< "failed to open" <<  eqep<< std::endl;
        }
    #endif
    
    #ifdef DEBUG_CODEUR
        std::cout<< "codeur ctr:  eqep: " << eqep << std::endl;
    #endif
}

Codeur::~Codeur(){
    this->_eqep.close();
}

void Codeur::set(long pos){
    this->_ofset = this->_ofset + pos;
}

long Codeur::read(){
    
    //read pos from file
    this->_eqep >> this->_posStr;
    
    this->_pos = atol(this->_posStr);
    
    this->_pos -= this->_ofset;
    
    #ifdef DEBUG_CODEUR
        std::cout<< "codeur : " <<  this->_posStr << " : "<< this->_pos << std::endl;
    #endif
    
    return this->_pos;
}


#ifdef DEBUG_CODEUR

    int main(void){
        Codeur codeur1("/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/");
        Codeur codeur2("/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep/");
        long pos = codeur1.read();
        pos = codeur2.read();
    
    }
    
#endif
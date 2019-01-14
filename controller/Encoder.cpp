#include "Encoder.h"
#include <iostream>
#include <fstream>
#include <unistd.h>


Encoder::Encoder(std::string eqepPath){
    // TODO check files
    
    this->_eqepPath = eqepPath + "position";
    
    // open eqep file

    this->_eqep.open(this->_eqepPath.c_str());
    
    this->_ofset = 0;
    
    #ifdef DEBUG_ENCODER
        if(! _eqep.is_open()){
           std::cout<< "failed to open" <<  this->_eqepPath<< std::endl;
        }
    #endif
    
    #ifdef DEBUG_ENCODER
        std::cout<< "codeur ctr:  eqep: " << this->_eqepPath << std::endl;
    #endif
}

Encoder::~Encoder(){
    this->_eqep.close();
}


void Encoder::set(long pos){
    this->_ofset =  pos - this->read();
}

long Encoder::read(){
    
     //read pos from file
    
    ///////////////////////////////////////////////////// not good but needed
    this->_eqep.close();
    this->_eqep.open(this->_eqepPath.c_str());
    /////////////////////////////////////////////////////
    
    this->_eqep >> this->_posStr;
    
    this->_pos = atol(this->_posStr);
    
    this->_pos += this->_ofset;
    
    #ifdef DEBUG_ENCODER
        std::cout<< "encoder : " <<  this->_posStr << " : "<< this->_pos << std::endl;
    #endif
    
    return this->_pos;
}


#ifdef DEBUG_ENCODER

    int main(void){
        Encoder encoder1("/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/");
        Encoder encoder2("/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep/");
        long pos = encoder1.read();
        std::cout<< "\t encoder : " <<  pos << std::endl;
        pos = encoder2.read();
        std::cout<< "\t encoder : " <<  pos  << std::endl;
        
        
        for (int i = 0 ; i< 10 ; i++) {
             usleep(1000000);
             encoder1.read();
             std::cout<< "\t";
             encoder2.read();
        }
    
    }
    
#endif
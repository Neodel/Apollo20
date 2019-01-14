#include <iostream>
#include <fstream>
#include <unistd.h>




//encoder 1 eQEP2B_in p8.11 EQEP2A_IN p8.12
//encoder 2 eQEP0B_in p9.27 eQEP0A_in p9.42 (92)

//examples: 
// Codeur codeur1("/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/");
// Codeur codeur2("/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep/");
// long pos = codeur1.read();

//#define DEBUG_CODEUR

#ifndef ENCODER_H
#define ENCODER_H

/**
 * @brief      Class for the encoder
 */
class Encoder{

public:
	/**
	 * @brief      constructor of the class encoder.
	 *
	 * @param[in]  eqepPath  The eqep path of the port
	 */
    Encoder(std::string eqepPath);
    
    /**
     * @brief      read the value of the equep port
     *
     * @return     (long) the value of the data port 
     */
    long read();

    /**
     * @brief     Change the ofset value of the encoder
     *
     * @param[in]  pos   
     */
    void set(long pos);
    
    ~Encoder();
    
    
private:
	/**
	 * path of the eqep port 
	 */
    std::string _eqepPath;
    /**
     * the data coming from the equep is stored in this file stream. 
     */
    std::ifstream _eqep;
    /**
     * ofset of the motor
     */
    long _ofset;
    /**
     * Position of the motor red in the equep port.
     */
    char _posStr[256];
    /**
     * position of the motor
     */
    long _pos;
    
};

#endif
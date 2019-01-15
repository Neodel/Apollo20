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
	 * @brief      Constructor of the class encoder.
	 *
	 * @param[in]  eqepPath  The EQEP path of the port
	 */
    Encoder(std::string eqepPath);
    
    /**
     * @brief      Read the value of the EQEP port
     *
     * @return     (long) The value of the data port
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
	 * Path of the EQEP port
	 */
    std::string _eqepPath;
    /**
     * The data coming from the EQEP is stored in this file stream
     */
    std::ifstream _eqep;
    /**
     * Ofset of the motor
     */
    long _ofset;
    /**
     * Position of the motor red in the EQEP ports
     */
    char _posStr[256];
    /**
     * Position of the motor
     */
    long _pos;
    
};

#endif

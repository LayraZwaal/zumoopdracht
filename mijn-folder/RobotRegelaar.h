/**
 * @file RobotRegelaar.h
 * @brief Header voor het brein van de robot: de hoofdregelaar.
 * @author Groep 2
 */

#ifndef ROBOTREGELAAR_H
#define ROBOTREGELAAR_H

#include "WielAandrijving.h"
#include "OndergrondScanner.h"
#include "SnelheidsMeter.h"
// #include "WipWapRegelaar.h" // Even uitgezet omdat dit compilerfouten gaf

class RobotRegelaar {
private:
    WielAandrijving* motorSturing;       
    OndergrondScanner* bodemScanner;    
    SnelheidsMeter* rotatieTeller;      
    

    // Instellingen voor hoe hard de robot mag rijden
    const int SNELHEID_MAX      = 400;  
    const int SNELHEID_CRUISE   = 300;  
    const int SNELHEID_GROEN    = 180;  

    // Onze PID-waardes voor het strak volgen van de lijn
    const double VERSTERKING_P  = 0.75; 
    const double VERSTERKING_D  = 1.55; 
    const double VERSTERKING_I  = 0.0;  

    int laatsteMeting;                  
    int vorigeAfwijking;                
    long foutSom;                       
    int onderbrekingTeller;             
    bool isAutonoomActief;              
    bool modusWipWapActief;            

    void hanteerHandmatigeInvoer(char commandoKarakter);
    void corrigeerKoersOpBaan();

public:
    RobotRegelaar(WielAandrijving* wa, OndergrondScanner* os, SnelheidsMeter* sm);
    void verwerkLoop();
};

#endif // ROBOTREGELAAR_H
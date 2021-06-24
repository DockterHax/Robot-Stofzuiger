#ifndef MBED_MOTORDRIVER_H
#define MBED_MOTORDRIVER_H

#include "mbed.h"

class motordriver
{
public:
    motordriver(PinName MLpinVooruit, PinName MLpinAchteruit, PinName MRpinVooruit, PinName MRpinAchteruit);
    void Vooruit (void);
    void Achteruit (void);
    void Stop (void);
    void Links (void);
    void Rechts (void);
private:
    DigitalOut _ML_Vooruit;
    DigitalOut _ML_Achteruit;
    DigitalOut _MR_Vooruit;
    DigitalOut _MR_Achteruit;
};
#endif
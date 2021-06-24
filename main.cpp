#include "mbed.h"
#include "ultrasonic.h"     // Subprogramma voor het aansturen van de HC-SR04 ultrasoon sensoren van Jan Kamidra
                            // https://os.mbed.com/users/JohnnyK/code/HC_SR04_Ultrasonic_Library/#6fd0e9c7ead4
#include "MotorDriver.h"    // Subprogramma voor het aansturen van van de motorcontroller geschreven door Mitchel Oosterkamp

// Programma robot stofzuiger project PES
// Mitchel Oosterkamp en Beunhaas Bakker
// EMT1V.G

PwmOut ML_Snelheid (D5);    // Range is beperkt tot 0~1
PwmOut MR_Snelheid (D6);    // Range is beperkt tot 0~1

motordriver md(D2, D3, D4, D7);          // Set pinnen voor vooruit (D1) en achteruit (D2) van de
                                        // linker kant van de motor driver en dus ook de linker set wielen.
                                       // Set pinnen voor vooruit (D4) en achteruit (D5) van de
                                      // rechter kant van de motor driver en dus ook de rechter set wielen.
void ObjectVoor(int distance)
{
    printf("Huidige gemeten afstand %dmm\r\n", distance);
    int r = rand()%2;
    if (distance < 10){
        if (r >= 0.5){
            ML_Snelheid = 0.3;   // Set snelheid linker set motoren (wielen)
            MR_Snelheid = 0.3;   // Set snelheid rechter set motoren (wielen)
            md.Links();          // draai naar links
            thread_sleep_for(500);    // Draai 0.5 seconde
            md.Stop();           // Stop de robot
        } else if (r < 0.5){
            ML_Snelheid = 0.3;   // Set snelheid linker set motoren (wielen)
            MR_Snelheid = 0.3;   // Set snelheid rechter set motoren (wielen)
            md.Rechts();         // draai naar links
            thread_sleep_for(500);    // Draai 0.5 seconde
            md.Stop();           // Stop de robot
        }
    } else{
        md.Vooruit();   // Rijd vooruit
    }
}
ultrasonic SensorVoor(D8, D9, 100ms, 1s, &ObjectVoor);  // Set the trigger pin to D8 and the echo pin to D9
                                                       // have updates every .1 seconds and a timeout after 1
                                                      // second, and call dist when the distance changes.
void Afgrond(int distance)
{
    printf("Huidige gemeten afstand %dmm\r\n", distance);
    if (distance >= 5){
        md.Achteruit();
        thread_sleep_for(1000);    // rijd 1 seconde achteruit
        int r = rand()%2;
        if (r >= 0.5){
            ML_Snelheid = 0.3;   // Set snelheid linker set motoren (wielen)
            MR_Snelheid = 0.3;   // Set snelheid rechter set motoren (wielen)
            md.Links();          // draai naar links
            thread_sleep_for(500);    // Draai 0.5 seconde
            md.Stop();           // Stop de robot
        } else if (r < 0.5){
            ML_Snelheid = 0.3;   // Set snelheid linker set motoren (wielen)
            MR_Snelheid = 0.3;   // Set snelheid rechter set motoren (wielen)
            md.Rechts();         // draai naar links
            thread_sleep_for(500);    // Draai 0.5 seconde
            md.Stop();           // Stop de robot
        }
    } else{
        md.Vooruit();   // Rijd vooruit
    }
}
ultrasonic SensorBeneden(D10, D11, 100ms, 1s, &Afgrond);  // Set the trigger pin to D10 and the echo pin to D11
                                                         // have updates every .1 seconds and a timeout after 1
                                                        // second, and call dist when the distance changes.
int main()
{
    SensorVoor.startUpdates();  // Start afstand meten
    SensorBeneden.startUpdates();  // Start afstand meten
    printf("Succesvolle communicatie \r\n");

    while(true) {
        ML_Snelheid = 0.15;   // Set snelheid linker set motoren (wielen)
        MR_Snelheid = 0.15;   // Set snelheid rechter set motoren (wielen)
        
            md.Vooruit();   // Rijd vooruit
        
        SensorVoor.checkDistance();     // Meet afstand sensor voor
        SensorBeneden.checkDistance();  // Meet afstand sensor beneden
        thread_sleep_for(200);          // Check afstand elke 200ms
    }
}

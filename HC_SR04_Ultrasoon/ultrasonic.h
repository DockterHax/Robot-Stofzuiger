// Credit voor deze library gaat naar Jan Kamidra
// https://os.mbed.com/users/JohnnyK/code/HC_SR04_Ultrasonic_Library/#6fd0e9c7ead4

#ifndef MBED_ULTRASONIC_H
#define MBED_ULTRASONIC_H

/**
   @code

   #include "mbed.h"
   #include "ultrasonic.h"

    void dist(int distance)
   {
       //put code here to happen when the distance is changed
       printf("Distance changed to %dmm\r\n", distance);
   }

   ultrasonic mu(D8, D9, 100ms, 1s, &dist);    //Set the trigger pin to D8 and the echo pin to D9
                                               //have updates every .1 seconds and a timeout after 1
                                               //second, and call dist when the distance changes

   int main()
   {
       mu.startUpdates();//start mesuring the distance
       while(1)
       {
           //Do something else here
           mu.checkDistance();     //call checkDistance() as much as possible, as this is where
                                   //the class checks if dist needs to be called.
       }
   }

   @endcode
*/

#include "mbed.h"

class ultrasonic
{
public:
    /**iniates the class with the specified trigger pin, echo pin, update speed and timeout**/
    ultrasonic(PinName trigPin, PinName echoPin, Kernel::Clock::duration_u32 updateSpeed, Kernel::Clock::duration_u32 timeout);
    /**iniates the class with the specified trigger pin, echo pin, update speed, timeout and method to call when the distance changes**/
    ultrasonic(PinName trigPin, PinName echoPin, Kernel::Clock::duration_u32 updateSpeed, Kernel::Clock::duration_u32 timeout, void onUpdate(int));
    /** returns the last measured distance**/
    int getCurrentDistance(void);
    /**pauses measuring the distance**/
    void pauseUpdates(void);
    /**starts mesuring the distance**/
    void startUpdates(void);
    /**attachs the method to be called when the distances changes**/
    void attachOnUpdate(void method(int));
    /**changes the speed at which updates are made**/
    void changeUpdateSpeed(Kernel::Clock::duration_u32 updateSpeed);
    /**gets whether the distance has been changed since the last call of isUpdated() or checkDistance()**/
    int isUpdated(void);
    /**gets the speed at which updates are made**/
    Kernel::Clock::duration_u32 getUpdateSpeed(void);
    /**call this as often as possible in your code, eg. at the end of a while(1) loop,
    and it will check whether the method you have attached needs to be called**/
    void checkDistance(void);
private:
    DigitalOut _trig;
    InterruptIn _echo;
    Timer _t;
    Timeout _tout;
    Kernel::Clock::duration_u32 _updateSpeed;
    int start;
    int end;
    int _distance;
    volatile int done;
    void (*_onUpdateMethod)(int);
    void _startT(void);
    void _updateDist(void);
    void _startTrig(void);
    Kernel::Clock::duration_u32 _timeout;
    int d;
};
#endif
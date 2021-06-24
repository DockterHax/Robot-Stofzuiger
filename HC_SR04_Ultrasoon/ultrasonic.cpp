// Credit voor deze library gaat naar Jan Kamidra
// https://os.mbed.com/users/JohnnyK/code/HC_SR04_Ultrasonic_Library/#6fd0e9c7ead4

#include "ultrasonic.h"

ultrasonic::ultrasonic(PinName trigPin, PinName echoPin, Kernel::Clock::duration_u32 updateSpeed, Kernel::Clock::duration_u32 timeout):_trig(trigPin), _echo(echoPin)
{
    _updateSpeed = updateSpeed;
    _timeout = timeout;
}

ultrasonic::ultrasonic(PinName trigPin, PinName echoPin, Kernel::Clock::duration_u32 updateSpeed, Kernel::Clock::duration_u32 timeout, void onUpdate(int))
    :_trig(trigPin), _echo(echoPin)
{
    _onUpdateMethod=onUpdate;
    _updateSpeed = updateSpeed;
    _timeout = timeout;
    _t.start ();
}
void ultrasonic::_startT()
{
    if(chrono::duration_cast<chrono::milliseconds>(_t.elapsed_time()).count()>600) {
        _t.reset ();
    }
    start = chrono::duration_cast<chrono::microseconds>(_t.elapsed_time()).count();
}

void ultrasonic::_updateDist()
{
    end = chrono::duration_cast<chrono::microseconds>(_t.elapsed_time()).count();
    done = 1;
    _distance = (end-start);
    _distance = (((_distance)<<2+_distance)/29); // (distance*5)/29 is distance/5.8
    _tout.detach();
    _tout.attach(callback(this,&ultrasonic::_startTrig), _updateSpeed);
}
void ultrasonic::_startTrig(void)
{
    _tout.detach();
    _trig=1;
    wait_us(10);
    done = 0;
    _echo.rise(callback(this,&ultrasonic::_startT));
    _echo.fall(callback(this,&ultrasonic::_updateDist));
    _echo.enable_irq ();
    _tout.attach(callback(this,&ultrasonic::_startTrig),_timeout);
    _trig=0;
}

int ultrasonic::getCurrentDistance(void)
{
    return _distance;
}
void ultrasonic::pauseUpdates(void)
{
    _tout.detach();
    _echo.rise(NULL);
    _echo.fall(NULL);
}
void ultrasonic::startUpdates(void)
{
    _startTrig();
}
void ultrasonic::attachOnUpdate(void method(int))
{
    _onUpdateMethod = method;
}
void ultrasonic::changeUpdateSpeed(Kernel::Clock::duration_u32 updateSpeed)
{
    _updateSpeed = updateSpeed;
}
int ultrasonic::isUpdated(void)
{
    //printf("%d", done);
    d=done;
    done = 0;
    return d;
}
void ultrasonic::checkDistance(void)
{
    if(isUpdated()) {
        (*_onUpdateMethod)(_distance);
    }
}
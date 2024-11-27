#ifndef __PIR_SENSOR__
#define __PIR_SENSOR__

class PirSensor {
public:
    void init(int pin);
    bool isMotionDetected(int pin);

private:
    bool motionDetected;
    int pin;
};


#endif

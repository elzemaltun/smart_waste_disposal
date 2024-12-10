#ifndef __SONAR_SENSOR__
#define __SONAR_SENSOR__

#include "Debug.h"
class SonarSensor {
    public:
        void init(int trigPin, int echoPin);
        float getDistance(int trigPin, int echoPin);
        bool checkWasteLevel(int trigPin, int echoPin);
    private:    
        int trigPin;
        int echoPin;
        bool isFull;
        float temperature;
        float distanceTreshold;
};

#endif
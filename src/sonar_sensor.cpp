#include "SonarSensor.h"
#include "Arduino.h"

void SonarSensor::init(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    isFull = false;
}

float SonarSensor::getDistance(int trigPin, int echoPin) {
    temperature = 20;
    const float vs = 331.45 + 0.62*temperature;

    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    /* Receiving the echo */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float distance = t*vs;
    return distance;
}

bool SonarSensor::checkWasteLevel(int trigPin, int echoPin) {
    const float distanceTreshold = 0.3;
    bool isFull = getDistance(trigPin, echoPin) < distanceTreshold;
    return isFull;
}
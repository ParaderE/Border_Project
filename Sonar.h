#ifndef Sonar_h
#define Sonar_h

#include "Arduino.h"

class Sonar {
    public:
        Sonar();
        Sonar(int trig_pin, int echo_pin);
        void attach(int tr_pin, int eco_pin);
        float getDistance();
    private:
        int _trig_pin;
        int _echo_pin;
};

class SonarArray {
    public:
        SonarArray();
        SonarArray(int n, Sonar *sonars);
        void attach(int n, Sonar *sonars);
        int[] getDistances();
        int getNumber();
    private:
        int _n;
        Sonar *_sonars;
}

class Led {
    public:
        Led();
        Led(int red_pin, int green_pin);
        void attach(int red_pin, int green_pin);
        void turnRed();
        void turnGreen();
    private:
        int _red_pin;
        int _green_pin;
}

class LedArray {
    public:
        LedArray();
        LedArray(int n, Led *leds);
        void attach(Led led);
        void attach(int n, Led *leds);
        void turnRed(int n);
        void turnGreen(int n);
    private:
        int _n = 0;
        Led *_leds;
}

#endif
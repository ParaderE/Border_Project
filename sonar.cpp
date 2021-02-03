#include "Arduino.h"
#include "Sonar.h"

Sonar::Sonar(int trig_pin, int echo_pin) {
    attach(trig_pin, echo_pin);
}

void Sonar::attach(int trig_pin, int echo_pin) {
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);
    _trig_pin = trig_pin;
    _echo_pin = echo_pin;
}

float Sonar::getDistance() {
    digitalWrite(_trig_pin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(_trig_pin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(_trig_pin, LOW); 
    float duration = pulseIn(_sg_pin, HIGH);

    return duration / 58;
}

SonarArray::SonarArray(int n, Sonar *sonars) {
    attach(n, sonars)
}

void SonarArray::attach(int n, Sonar *sonars) {
    _n = n;
    _sonars = sonars;
}

int SonarArray::getNumber() {
    return _n;
}

int[] SonarArray::getDistances() {
    int[] distances;
    for (int i = 0 i < _n; i++) {
        distances[i] = _sonars[i].getDistance();
    }
    return distances;
}

Led::Led(int red_pin, int green_pin) {
    attach(red_pin, green_pin);
}

void Led::attach(int red_pin, int green_pin) {
    pinMode(red_pin, OUTPUT);
    pinMode(green_pin, OUTPUT);
    _red_pin = red_pin;
    _green_pin = green_pin;
}

void Led::turnGreen() {
    digitalWrite(_green_pin, HIGH);
    digitalWrite(_red_pin, LOW);
}

void Led::turnRed() {
    digitalWrite(_green_pin, LOW);
    digitalWrite(_red_pin, HIGH);
}

LedArray::LedArray(int n, Led *leds) {
    attach(n, leds)
}

void LedArray::attach(Led led) {
    _n++;
    _leds[_n] = led;
}

void LedArray::attach(int n, Led *leds) {
    _n = n;
    _leds = leds;
}

void LedArray::turnGreen(int n) {
    if (n < _n) {
        _leds[n].turnGreen()
    }
}

void LedArray::turnRed(int n) {
    if (n < _n) {
        _leds[n].turnRed()
    }
}
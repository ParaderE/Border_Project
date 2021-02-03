#include "Servo.h"
#include "EEPROM.h"
#include "Sonar.h"
#include "Model.h"

Servo servo;
SonarArray array;
LedArray leds;
RandomForest classifier;

struct Pinout {
    int red_pin;
    int green_pin
};

void setupPins() {
    while (not Serial.available()) {}
    data = Serial.parseInt();
    if (data < 100) {
        Pinout pins;
        for (int i = 0; i < data; i++) {
            eeprom_read_block(&pins, i * sizeof(pins), sizeof(pins))
        }
        leds.attach(Led(pins.red_pin, pins.green_pin));
    } else {
        int i = 0
        while (data > 0) {
            int red = data % 100;
            data /= 100;
            int green = data % 100;
            data /= 100;
            leds.attach(Led(red, green));
            Pinout pins;
            pins.red_pin = red;
            pins.green_pin = green;
            eeprom_write_block((void*)&pins, i * sizeof(pins), sizeof(pins));
            i ++;
        }
    }
}

void setup() {
    servo.attach(9);
    array.attach(1, Sonar(11, 10))
    setupPins();
}

void loop() {
    int angle = 165;
    servo.write(angle);
    float ds[array.getNumber()][11] = {};

    for (int i = 0; i < 11; i ++) {
        angle -=15;
        ds[i] = array.getDistance();
        servo.write(angle);
        delay(100);
    }

    for (int i = 0; i < array.getNumber(); i ++) {
        bool is_accident = classifier.predict(ds[i]);
        if (is_accident) {
            leds.turnRed(i);
        } else {
            leds.turnGreen(i);
        }
    }
}
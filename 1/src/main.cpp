/*
Define on which core the main loop runs
using xPortGetCoreID()

By default it should be pinned to core 1 - APP_CPU
See main.cpp on ArduinoEspressif32
*/

#include <Arduino.h>

#define LED 15

void setup(){
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    Serial.print("This task runs on core : ");
    Serial.println(xPortGetCoreID());
    digitalWrite(LED, HIGH);
    Serial.println("LED ON");
    delay(500);
    digitalWrite(LED, LOW);
    Serial.println("LED OFF");
    delay(500);
}





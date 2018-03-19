#include <Arduino.h>
#include <ESPectro.h>

ESPectro board(ESPectro_V3);
unsigned long loops1 = 1000;
unsigned long loops2 = 1000;
float t1;
int t2;
int t3;

unsigned long qq = 0;

void LoadTest () {
    for (long i = 0; i < loops1; i++) {
    for (long j = 1; j < loops2; j++) {
        qq++;   
        ESP.wdtFeed();
        t1 = 1000.125 * i;
        t2 = 150 * 1234 * i;
        t3 = j % 128 ;
    }
}
}

void setup() {
    Serial.begin(115200);
    Serial.println("Start Load Test");
    board.turnOffAllNeopixel();

}

void loop() {
    long end;
    long start = millis();
    LoadTest();
    end=millis();
    Serial.print("Finish Load Test.");
    Serial.print(" Time : ");
    Serial.print(end-start);
    Serial.println(" ms");
    delay(10);
}
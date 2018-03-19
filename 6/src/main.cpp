#include <Arduino.h>
 
#define LED1 15
#define LED2 5


void blink(byte pin, int duration) {

  digitalWrite(pin, LOW);
  delay(duration);
  digitalWrite(pin, HIGH);
  delay(duration);
}

void Task1( void * parameter )
{
  for (;;) {
    Serial.print(millis());
    Serial.println(" Task 1 Init");
    blink(LED1, 750);
    //delay(50);
    Serial.print(millis());
    Serial.println(" Task 1 Done ");
  }
}

void Task2( void * parameter )
{
  for (;;) {
    Serial.print(millis());
    Serial.println("                  Task 2 Init");
    blink(LED2, 1000);
    //delay(50);
    Serial.print(millis());
    Serial.println("                  Task 2 Done");
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  xTaskCreatePinnedToCore(
    Task1,
    "LED1Task1",
    1000,
    NULL,
    1,
    0,
    0);

  xTaskCreatePinnedToCore(
    Task2,
    "LED2Task2",
    1000,
    NULL,
    1,
    0,
    1);

}

void loop() {
  delay(100);
}

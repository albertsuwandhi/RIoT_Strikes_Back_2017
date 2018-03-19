#include <Arduino.h>
 
#define LED1 15
#define LED2 5

//TaskHandle_t Task1, Task2;
SemaphoreHandle_t mutex;
int counter = 0;

void blink(byte pin, int duration) {

  digitalWrite(pin, LOW);
  delay(duration);
  digitalWrite(pin, HIGH);
  delay(duration);
}

void Task1( void * parameter )
{
  for (;;) {
    xSemaphoreTake(mutex, portMAX_DELAY );
    //Serial.print(millis());
    Serial.println(" Task 1 Init");
    blink(LED1, 750);
    //delay(50);
    counter++;
    Serial.print(" Counter in Task 1: ");
    Serial.println(counter);
    //Serial.print(millis());
    Serial.println(" Task 1 Done ");
    xSemaphoreGive(mutex);
    delay(10);

  }
}

void Task2( void * parameter )
{
  for (;;) {
    xSemaphoreTake(mutex, portMAX_DELAY );
    //Serial.print(millis());
    Serial.println("                  Task 2 Init");
    blink(LED2, 750);
    //delay(5000);
    counter++;
    //while(1){} //simulate locking
    Serial.print("                  Counter in Task 2: ");
    Serial.println(counter);
    //Serial.print(millis());
    Serial.println("                  Task 2 Done");
    xSemaphoreGive(mutex);
    delay(10);
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  mutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
    Task1,
    "led1Task",
    1000,
    NULL,
    1,
    0,
    0);

  //delay(500);  // needed to start-up task1

  xTaskCreatePinnedToCore(
    Task2,
    "led2Task",
    1000,
    NULL,
    1,
    0,
    1);

}

void loop() {
  delay(100);
}

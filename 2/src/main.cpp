/*
Create Task pinned to specific core using xTaskCreatePinnedToCore
Main Loop - Core 1 
Blink LED Task - Core 0

*/
#include <Arduino.h>

#define LED 15

void Task1( void * parameter )
{
  for (;;) {
    Serial.print("Task1 runs on Core: ");
    Serial.println(xPortGetCoreID());
    digitalWrite(LED, HIGH);   
    Serial.println("LED ON Task 1");
    //delay(1000);    
    vTaskDelay(1000);           
    digitalWrite(LED, LOW);    
    //delay(1000); 
    vTaskDelay(1000);   
    Serial.println("LED OFF Task 1");              
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  //Create Blink Task pinned to core 0 - PRO_CPU
  xTaskCreatePinnedToCore(
    Task1,                    /* Task function. */
    "BLINK",                 /* name of task. */
    1000,                     /* Stack size of task */
    NULL,                     /* parameter of the task */
    1,                        /* priority of the task */
    0,                        /* Task handle to keep track of created task */
    0);                       /* Core */
}

void loop() {
    Serial.print("            Main Loop runs on Core: ");
    Serial.println(xPortGetCoreID());
    delay(2000); 
    
    while(1){
        delay(10);
    }
    
}

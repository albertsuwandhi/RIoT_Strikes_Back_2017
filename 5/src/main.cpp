/* 
 * This sketch runs a artificial load on both cores to measure maximum compute power of the ESP32 
 */

#include <Arduino.h>

unsigned long loops1 = 1000;
unsigned long loops2 = 1000;


float t1;
int t2;
int t3;



unsigned long qq = 0;

//TaskHandle_t Task1, Task2;


void LoadTest () {
  for ( long i = 0; i < loops1; i++) {
    for (long  j = 1; j < loops2; j++) {
      qq++;
      t1 = 1000.125 * i;
      t2 = 150 * 1234 * i;
      t3 = j % 128 ;
    }
  }
}

void Task1( void * parameter )
{
  unsigned long i, j;
  for (;;) {
    /*
    long start = millis();

    LoadTest();

    Serial.print("Finish Task 1 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time ");
    Serial.println(millis() - start);
    delay(10);
    */
  }
}

void Task2( void * parameter )
{
  for (;;) {
    /*
    long start = millis();

    LoadTest();

    Serial.print("                                                        Finish Task 2 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time ");
    Serial.println(millis() - start);
    delay(10);
    */
  }
}


void setup() {
  Serial.begin(115200);
  
  /*
  xTaskCreatePinnedToCore(
    Task1,
    "Task1",
    1000,
    NULL,
    1,
    0,
    0);
  
  //delay(10);

  xTaskCreatePinnedToCore(
    Task1,
    "Task2",
    1000,
    NULL,
    1,
    0,
    1);
    
*/
}



void loop() {
    
    long start = millis();
    long end;
    LoadTest();
    end=millis();
    Serial.print("Finish Load Test.");
    Serial.print(" Time : ");
    Serial.print(end - start);
    Serial.println(" ms");
    delay(10);
    //delay(1000);
}

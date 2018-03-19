#include <Arduino.h>

long loops1 = 1500;
long loops2 = 1500;
long qq;
float t1;
int t2, t3;

//TaskHandle_t Task1, Task2;
//SemaphoreHandle_t mutex;

void LoadTest () {
  for ( long i = 0; i < loops1; i++) {
    for (long  j = 1; j < loops2; j++) {
      qq++;
      t1 = 18000.25 * i;
      t2 = 150 * 1234 * i;
      t3 = j % 250 ;
    }
  }
}

/*
void LoadTest1(){
   while(1){
      delay(10);
   }

  }
*/


void Task1( void * parameter )
{
  for (;;) {
    Serial.println("Execute Task 1 Load Test");
    long start,end, duration;
    Serial.print("Task 1 start millis : ");
    start = millis();
    Serial.println(start);
    LoadTest();
    end=millis();
    Serial.print("Task 1 end millis : ");
    Serial.print(end);
    Serial.println(" ms");
    duration=end-start;
    Serial.print("Finish Task 1 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time : ");
    Serial.print(duration);
    Serial.println(" ms");
    Serial.println("Finished Task 1 Load Test");
    
  }
}


void Task2( void * parameter )
{
  for (;;) {
    
    long start,end, duration;
    Serial.print("Task 2 start millis : ");
    start = millis();
    Serial.println(start);
    LoadTest();
    end=millis();
    Serial.print("Task 2 end millis : ");
    Serial.print(end);
    Serial.println(" ms");
    duration=end-start;
    Serial.print("Finish Task 2 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time : ");
    Serial.print(duration);
    Serial.println(" ms");
    delay(10);
    
  }
}


void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    Task1,
    "Task1",
    1000,
    NULL,
    1,
    0,
    1);

  delay(100);  

  xTaskCreatePinnedToCore(
    Task2,
    "Task2",
    1000,
    NULL,
    1,
    0,
    0);
}


void loop() {
   
  long start,end, duration;
  Serial.print("Main Loop start millis : ");
  start = millis();
  Serial.println(start);
  Serial.println ("Execute Main Load Test");
  LoadTest();
  end=millis();
  Serial.println("Finished Main Load Test");
  Serial.print("Main Loop end millis : ");
  Serial.print(end);
  Serial.println(" ms");
  duration=end-start;
  Serial.print("Finish Loop Task which runs on Core ");
  Serial.print( xPortGetCoreID());
  Serial.print(" Time : ");
  Serial.print(duration);
  Serial.println(" ms");
  //while(1){
  //  delay(100);
  //}
}

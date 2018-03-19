int threshold = 40;
bool touch1detected = false;
bool touch2detected = false;
long lastmillisA, lastmillisB = 0;

void gotTouchA(){
 if (millis()-lastmillisA>500){
    touch1detected = true;
    lastmillisA=millis();
 }
}
void gotTouchB(){
  if (millis()-lastmillisB>500){
    touch2detected = true;
    lastmillisB=millis();
}
}

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  printf("\n ESP32 Touch Interrupt Test\n");
  touchAttachInterrupt(T4, gotTouchA, threshold);
  touchAttachInterrupt(T2, gotTouchB, threshold);
}

void loop(){
  if(touch1detected){
    touch1detected = false;
    Serial.println("Touch 1 detected");
  }
  if(touch2detected){
    touch2detected = false;
    Serial.println("Touch 2 detected");
  }
}

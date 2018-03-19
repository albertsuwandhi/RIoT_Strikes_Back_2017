#include <Arduino.h>
#include "arduinoFFT.h" // https://github.com/kosme/arduinoFFT  

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
/*
These values can be changed in order to evaluate the functions
*/
const uint16_t samples = 64; //This value MUST ALWAYS be a power of 2
const double signalFrequency = 1000;
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;
double vReal[samples];
double vImag[samples];

void do_fft() {
  /* Build raw data */
  double cycles = (((samples-1) * signalFrequency) / samplingFrequency); //Number of signal cycles that the sampling will read
  for (uint16_t i = 0; i < samples; i++) {
    vReal[i] = int8_t((amplitude * (sin((i * (twoPi * cycles)) / samples))) / 2.0);/* Build data with positive and negative values*/
  }
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  double x = FFT.MajorPeak(vReal, samples, samplingFrequency);
}

uint32_t float_sqrt(uint32_t count) {
  uint32_t pos;
  float t = 0;
  uint32_t start_millis,stop_millis;
  
  Serial.print(String("float ")+String(count)+String(" sqrt: "));
  start_millis=millis();
  for (pos=0; pos<count; pos++) {
    t = sqrt(pos);
 }
  stop_millis=millis();
  Serial.println(String(t)+String(" ")+String(stop_millis-start_millis)+String(" ms"));
  return stop_millis-start_millis;
}

uint32_t double_sqrt(uint32_t count) {
  uint32_t pos;
  double t = 0;
  uint32_t start_millis,stop_millis;
  
  Serial.print(String("double ")+String(count)+String(" sqrt: "));
  start_millis=millis();
  for (pos=0; pos<count; pos++) {
    t = sqrt(pos);
 }
  stop_millis=millis();
  Serial.println(String(t)+String(" ")+String(stop_millis-start_millis)+String(" ms"));
  return stop_millis-start_millis;
}

uint32_t double_pow(uint32_t count) {
  uint32_t pos;
  double t = 0;
  uint32_t start_millis,stop_millis;
  
  Serial.print(String("double ")+String(count)+String(" pow: "));
  start_millis=millis();
  for (pos=0; pos<count; pos++) {
    t = pow(pos,2);
 }
  stop_millis=millis();
  Serial.println(String(t)+String(" ")+String(stop_millis-start_millis)+String(" ms"));
  return stop_millis-start_millis;
}

uint32_t double_fft(uint32_t count) {
  uint32_t pos;
  uint32_t start_millis,stop_millis;
  
  Serial.print(String("double ")+String(count)+String(" fft: "));
  start_millis=millis();
  for (pos=0; pos<count; pos++) {
    do_fft();
  }
  stop_millis=millis();
  Serial.println(String(" ")+String(stop_millis-start_millis)+String(" ms"));
  return stop_millis-start_millis;
}


void LoadTest() {
  uint32_t total_millis=0;
  total_millis += float_sqrt(100000);
  total_millis += double_sqrt(50000);
  total_millis += double_pow(50000);
  total_millis += double_fft(1000);
  Serial.println(String("ESP32 Total Time : ")+String((double)total_millis)+String(" ms\n"));
}


void setup(){
    Serial.begin(115200);
}

void loop() {
  LoadTest();
  delay(1000);
}
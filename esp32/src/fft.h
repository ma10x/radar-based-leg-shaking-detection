#include <arduinoFFT.h>
#include <Arduino.h>
#define SAMPLE_FREQ 10 // 采样频率，单位Hz
#define MAX_SAMPLES 64 // 假设最大采样点数为 64
#define beep_pin 32
extern double vReal;
extern double vImag;
extern double samples;

extern ArduinoFFT<double> FFT;
void fft();
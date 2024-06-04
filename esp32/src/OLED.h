#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 OLED;

void init_oled();
void oled_show_string(String show_string);
void oled_show_int(int show_number);
void oled_show_float(float show_frequency);
void displayTimeDistanceCurve();

#endif // OLED_H
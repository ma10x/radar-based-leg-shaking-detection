#include <Arduino.h>
#include <iostream>
#include <fstream>
#include <string>
#include <OLED.h>
#include <my_wifi.h>
#include <fft.h>


int distanceIndex = 0;
int filtered_distance = 0;
double alpha = 0.2;  // 指数平滑滤波的参数
int distances[MAX_SAMPLES]; // 存储距离数据的数组
int num_samples = 0; // 已存储的样本数
extern float frequency;


extern int number;
extern float fre;



using namespace std;


//void writeToCSV(const string & distance);
  /*    void writeToCSV(const string & distance) {
    // 将距离信息写入CSV文件

  ofstream file("E:/data.csv",ios::out);
    if (file.is_open()) {
        file << distance << endl;
        file.close();
        cout << "Data has been written to distance_data.csv" << endl;
    } else {
        cout << "Error: Unable to open file distance_data.csv for writing!" << endl;
    }
  }
  */
 
// 从串口数据中解析距离参数
int parseDistance(char *data) {
    char *distancePtr = strstr(data, "Distance=");//找到Distance英文的位置
    if (distancePtr != NULL) {
        distancePtr += strlen("Distance=");//找到距离数据的位置


        // 解析距离参数
        int distance;
        sscanf(distancePtr, "%d", &distance);//从字符串distanceptr中读取格式化数据写到distance
        return distance;
    }
    return -1; // 如果未找到距离参数，则返回负值
}



void setup() {

  string distanceData;
  Serial.begin(115200);
  pinMode(beep_pin, OUTPUT);//蜂鸣器

  init_oled();
  oled_show_string("connecting wifi");
  WiFi_Connect();
  oled_show_string("welcome");
  startTCPClient();

}

void loop() {

  static char buffer[100]; // 用于存储串口接收的数据
  static int index = 0;     // 当前缓冲区中的数据索引
  
  while (Serial.available()) {
    
    char data = Serial.read();
//    Serial.write(data); // 回显接收到的字符



    // 如果接收到换行符，则说明已经接收完整一行数据
    if (data == '\n') {
      buffer[index] = '\0'; // 将缓冲区末尾置为字符串结尾标记
      int distance = parseDistance(buffer);
      // 现在可以处理距离参数 distance 了
      //printf("distance=%d",distance);
    // 将距离数据存储到数组中
    if (distance != -1) {
      distances[num_samples++] = distance;
      
      // 检查是否超出了数组容量
      if (num_samples >= MAX_SAMPLES) {
        // 如果超出了容量，可以选择停止存储新数据或者进行其他处理
        // 此处仅打印一条消息并清空数组，以便继续接收新数据
  
        fft();
        doTCPClientTick(number,fre);
        oled_show_int(number);
        delay(100);
        oled_show_float(fre);

        num_samples = 0;
      }
    }
      index = 0; // 重置索引以准备接收下一行数据
    } else {
      // 将接收到的字符存储到缓冲区中
      buffer[index++] = data;
      // 检查缓冲区是否已满，如果是，则重置索引以避免溢出
      if (index >= sizeof(buffer)) {
        index = 0;
      }
    }
  }
}








/*oled显示曲线图
#include <U8g2lib.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,  U8X8_PIN_NONE, 22, 21); 

void drawPoint(int distance) {
  static int prevDistance = 0;
  static int x = 0;
  int y = SCREEN_HEIGHT - distance;
  
  if (x > SCREEN_WIDTH) {
    // Clear display and reset x position when reaching end
    x = 0;
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB14_tr);

  }
  
  // Draw line from previous point to current point
  u8g2.drawLine(x - 1, SCREEN_HEIGHT - prevDistance, x, y);
  u8g2.sendBuffer();
  
  // Update previous distance and increment x position
  prevDistance = distance;
  x++;
}

void setup() {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.clearBuffer();

  u8g2.sendBuffer();
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int distance = data.toInt();
    if (distance >= 0 && distance <= SCREEN_HEIGHT) {
      drawPoint(distance);
    }
  }
}
*/














































/*
#include <Arduino.h>
#include <SoftwareSerial.h>

// 设置与 Python 通信的软件串口
SoftwareSerial pythonSerial(10, 11); // RX, TX

void setup() {
  // 初始化串口
  Serial.begin(115200);
  pythonSerial.begin(9600); // 与 Python 程序通信的波特率
  
  // 向 Python 发送开始信号
  pythonSerial.println("start");
}

void loop() {
  // 从 Arduino 的串口接收数据
  if (Serial.available()) {
    char data = Serial.read();
    // 将接收到的数据发送给 Python
    pythonSerial.write(data);
  }
  
  // 从 Python 的串口接收数据
  if (pythonSerial.available()) {
    char data = pythonSerial.read();
    // 将接收到的数据发送给 Arduino 的串口
    Serial.write(data);
  }
}
*/
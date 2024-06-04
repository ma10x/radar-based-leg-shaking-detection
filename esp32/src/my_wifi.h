#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <Wire.h>

//巴法云服务器地址默认即可
#define TCP_SERVER_ADDR "bemfa.com"
//服务器端口//TCP创客云端口8344//TCP设备云端口8340
#define TCP_SERVER_PORT "8344"

//设置上传速率2s（1s<=upDataTime<=60s）
//下面的2代表上传间隔是2秒
#define upDataTime 2*1000






void WiFi_Connect();
void startTCPClient();
void sendtoTCPServer(String p);
void doTCPClientTick(int n,double f);
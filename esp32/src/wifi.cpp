#include <my_wifi.h>



// 记得解压ArduinoJson文件夹

// JOSN是一种轻量级的数据交换格式，遵循以下规则：
// 1.并列的数据之间用逗号(,)分隔
// 2.映射用冒号(:)表示
// 3.并列数据的集合(数组)用方括号([])表示
// 4.映射的集合(对象)用大括号({})表示

//	WiFi的初始化和连接

//const char *host="47.120.55.39";
//const int port=3000;

//tcp客户端相关初始化，默认即可
WiFiClient TCPclient;
//用户私钥，可在控制台获取,修改为自己的UID
String UID = "18b9fc4f1fa220695bfc0b2b035c7fbc";
//主题名字，可在控制台新建
String TOPIC = "esp32"; //用于传输温湿度的主题

String TcpClient_Buff = "";
unsigned int TcpClient_BuffIndex = 0;
unsigned long TcpClient_preTick = 0;
unsigned long preHeartTick = 0;//心跳
unsigned long preTCPStartTick = 0;//连接
bool preTCPConnected = false;
int N=0;
float F=0;

void WiFi_Connect()
{
	WiFi.begin("Free-Wifi", "88886666");
	while (WiFi.status() != WL_CONNECTED)
	{ //这里是阻塞程序，直到连接成功
		delay(300);
		Serial.print(".");
	}
	Serial.println("WiFi connected");

	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

}



/*
  *初始化和服务器建立连接
*/
void startTCPClient(){
  if(TCPclient.connect(TCP_SERVER_ADDR, atoi(TCP_SERVER_PORT))){
  //  Serial.print("\nConnected to server:");
  //  Serial.printf("%s:%d\r\n",TCP_SERVER_ADDR,atoi(TCP_SERVER_PORT));
    String tcpTemp="";
    tcpTemp = "cmd=1&uid="+UID+"&topic="+TOPIC+"\r\n";

    sendtoTCPServer(tcpTemp);
    preTCPConnected = true;
    preHeartTick = millis();
    TCPclient.setNoDelay(true);
  }
  else{
  //  Serial.print("Failed connected to server:");
  //  Serial.println(TCP_SERVER_ADDR);
    TCPclient.stop();
    preTCPConnected = false;
  }
  preTCPStartTick = millis();
}





/*
  *发送数据到TCP服务器
 */
void sendtoTCPServer(String p){
  
/* if (!TCPclient.connected()) 
  {
    Serial.println("Client is not readly");
    return;
  }
 */ 
  TCPclient.print(p);
 // Serial.println("[Send to TCPServer]:String");
 // Serial.println(p);
}

/*
  *检查数据，发送数据
*/
void doTCPClientTick(int n,double f){
 //检查是否断开，断开后重连
 //  if(WiFi.status() != WL_CONNECTED) return;

/*  if (!TCPclient.connected()) {//断开重连

  if(preTCPConnected == true){

    preTCPConnected = false;
    preTCPStartTick = millis();
  //  Serial.println();
  //  Serial.println("TCP Client disconnected.");
    TCPclient.stop();
  }
  else if(millis() - preTCPStartTick > 1*1000)//重新连接
    startTCPClient();    //刷新preHeartTick
  }
  
  else
  {
    if(millis() - preHeartTick >= upDataTime){//上传数据
      preHeartTick = millis();

*/       
      /*********************数据上传*******************/
      /*
        数据用#号包裹，以便app分割出来数据，&msg=#23#80#on#\r\n，app端会根据#号分割字符串进行取值，以便显示
        如果上传的数据更多，可在#号后面继续添加&msg=#23#80#data1#data2#data3#data4#\r\n,app字符串分割的时候，要根据上传的数据进行分割
      */
      String upstr = "";
      if(N!=n){//数据变
      upstr = "cmd=2&uid="+UID+"&topic="+TOPIC+"&msg=#"+n+"#"+f+"#\r\n";
      sendtoTCPServer(upstr);
      N=n;
      F=f;
      }
      else{
        upstr = "cmd=2&uid="+UID+"&topic="+TOPIC+"&msg=#"+N+"#"+F+"#\r\n";//数据不变
        sendtoTCPServer(upstr);
      }
     
      upstr = "";
/*     
    }
  }
*/ 
}
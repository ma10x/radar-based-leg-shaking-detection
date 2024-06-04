#include <OLED.h>
#define SCREEN_WIDTH 128 // OLED显示屏宽度（像素）
#define SCREEN_HEIGHT 64 // OLED显示屏高度（像素）
extern int num_samples; // 已存储的样本数
extern int distances[];

Adafruit_SSD1306 OLED(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire);
void init_oled(){
  Wire.begin(21,22,100000);
  OLED.begin(SSD1306_SWITCHCAPVCC,0X3C);
  OLED.clearDisplay();
  OLED.setTextColor(SSD1306_WHITE);
  OLED.setTextSize(1);
}
void oled_show_string(String show_string){
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setCursor(2,0);
  OLED.print(show_string);
  OLED.display();
}

void oled_show_int(int show_number){
  OLED.clearDisplay();
  OLED.setTextSize(2);
  OLED.setCursor(57,5);
  OLED.print(show_number);
  OLED.display();
}

void oled_show_float(float show_frequency){
  char buffer[10]; // 用于存储转换后的字符串
  dtostrf(show_frequency, 4, 2, buffer); // 将浮点数转换为字符串，保留两位小数
  OLED.setTextSize(2); // 设置文字大小为2
  OLED.setCursor(40, 35); // 设置光标位置为 (2, 30)
  OLED.print(buffer); // 在OLED上显示字符串
  OLED.display(); // 更新OLED显示屏以显示内容
}

void displayTimeDistanceCurve() {
  // 清空显示缓冲区
  OLED.clearDisplay();

  // 定义曲线的尺寸和位置
  int curveWidth = SCREEN_WIDTH - 8; // 曲线宽度为屏幕宽度减去边距
  int curveHeight = SCREEN_HEIGHT - 8; // 曲线高度为屏幕高度减去边距
  int xOffset = 2; // X轴偏移量
  int yOffset = 2; // Y轴偏移量

  // 绘制坐标轴
  OLED.drawLine(xOffset, yOffset, xOffset, SCREEN_HEIGHT, SSD1306_WHITE); // Y轴（起点，终点，颜色）
  OLED.drawLine(xOffset, SCREEN_HEIGHT - yOffset, SCREEN_WIDTH, SCREEN_HEIGHT - yOffset, SSD1306_WHITE); // X轴

  // 计算距离数据点的坐标并绘制折线 200-600mm
  if (num_samples > 1) {
    for (int i = 1; i < num_samples; ++i) {
      int x1 = map(i - 1, 0, num_samples - 1, xOffset, xOffset + curveWidth);
      int y1 = map(distances[i - 1], 0, 600, SCREEN_HEIGHT - yOffset, yOffset); // 这里假设距离范围为0到600
      int x2 = map(i, 0, num_samples - 1, xOffset, xOffset + curveWidth);
      int y2 = map(distances[i], 0, 600, SCREEN_HEIGHT - yOffset, yOffset);

      // 绘制线段
      OLED.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
    }
  }

  // 刷新显示
  OLED.display();
}
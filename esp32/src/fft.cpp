#include <fft.h>
#include <OLED.h>
extern int distances[MAX_SAMPLES];
float frequency;
int number=0;
float fre=0;
ArduinoFFT<double> FFT;
void fft()
{
  float sumvReal=0;
      // 执行FFT处理
  double vReal[MAX_SAMPLES];
  double vImag[MAX_SAMPLES];
  double maxvReal=0;
  for (int i = 0; i < MAX_SAMPLES; i++) {
    // 将距离数据存储到vReal数组中
    vReal[i] = distances[i];
    // 虚部置为0
    vImag[i] = 0;
  }

  // 执行FFT
  FFT.windowing(vReal, MAX_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.compute(vReal, vImag, MAX_SAMPLES, FFT_FORWARD);//执行 FFT 计算
  FFT.complexToMagnitude(vReal, vImag, MAX_SAMPLES);//计算复数幅度
  // 打印频率分量
  for (int i = 0; i < MAX_SAMPLES / 2; i++) {
    frequency = ((float)i * SAMPLE_FREQ) / MAX_SAMPLES; //0到4.84hz
    if(frequency>=1.56&&frequency<=3.91)
    {
      sumvReal+=vReal[i];
      if(vReal[i]>vReal[i-1] && vReal[i]>maxvReal){//寻找幅度最大值
        maxvReal=vReal[i];
        
        fre=frequency;
      }

    }
    else if(frequency>3.91){
      sumvReal=sumvReal-maxvReal;
      if(maxvReal<700 && maxvReal>65&&maxvReal>2.8*(sumvReal/15))//振动的幅度越低，maxveal就需要调的越低
      {
      //Serial.print("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      number+=1;
      //蜂鸣器
      digitalWrite(beep_pin,1);//引脚输出电平翻转
      delay(3000);//延时3s
      digitalWrite(beep_pin,0);//引脚输出电平翻转
      break;
      }
      break;
    }


    //Serial.print(frequency);
    //Serial.print(" Hz: ");
    //Serial.println(vReal[i]);    //幅度





  }

  // 等待下一次采样
  //delay(1000);


}
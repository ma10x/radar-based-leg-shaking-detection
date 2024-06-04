# radar-based-leg-shaking-detection
基于雷达的抖腿检测（脉冲相干雷达PCR）

以esp32作为主控板。采用佰誉达公司的产品：PCR20D雷达模块作为本设计的传感器，以此采集腿部左右抖动。此模块搭载的传感器芯片为acconeer公司开发的脉冲相干雷达：a111。使用I2C协议的OLED屏幕显示wifi连接情况和抖腿参数信息：抖腿次数、频率。
# esp32文件夹为基于vscode平台的platformio插件开发的esp32程序。
\esp32\.pio\libdeps\esp32dev为platformio上需要下载的库。\esp32\src下为程序，my_serial.py可以绘图来可视化雷达输出的距离数据。
# esp32_radar_ad文件夹为使用AltiumDesigner设计的电路板
其中gerber文件可在嘉立创上直接打板。
# 3d_model为使用Solidworks设计的外壳模型
stl文件可打印3d模型。

The esp32 is used as the main control board. PCR20D radar module of Baiyuda Company is used as the sensor in this design to collect the left and right leg jitter. The sensor chip in this module is the pulse coherence radar a111 developed by acconeer. The OLED screen using the I2C protocol displays wifi connection and leg shake parameter information: the number and frequency of leg shake.
 # The esp32 folder is an esp32 program developed based on the platformio plug-in of the vscode platform.
\esp32\.pio\libdeps\esp32dev is the library you need to download from platformio. Under \esp32\src is the program, my_serial.py can plot to visualize the range data output by radar.
 # The esp32_radar_ad folder is for boards designed using AltiumDesigner
Among them, gerber files can be directly hit the plate on Jialicang.
# 3d_model is a shell model designed for use with Solidworks
stl files can print 3d models.

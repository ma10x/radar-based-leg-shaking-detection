'''import serial
import csv

# 打开串口
ser = serial.Serial('COM7', 115200)  # 替换为正确的串口号和波特率

# 打开CSV文件
with open('E:/data.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    
    # 监听串口数据并写入CSV文件
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode().strip()
            print(data)  # 打印数据到控制台
            csvwriter.writerow([data])  # 将数据写入CSV文件
'''
import serial
import re
import matplotlib.pyplot as plt
import numpy as np

# 设置串口参数
port = 'COM7'  # 根据您的系统和连接端口进行调整
baudrate = 115200
timeout = 1

# 打开串口
ser = serial.Serial(port, baudrate, timeout=timeout)

# 初始化数据列表
distances = []
filtered_distance = None
alpha = 0.2  # 指数平滑滤波的参数，可以根据需要调整

# 初始化FFT参数
N = 64  # FFT的点数
T = 0.1  # 采样间隔
xf = np.linspace(0, 1, N//2)

# 创建距离曲线图和频谱图的子图
fig, (ax1, ax2) = plt.subplots(2, 1)
# 设置距离曲线图的标题和标签
ax1.set_title('Distance over Time')
ax1.set_xlabel('Time')
ax1.set_ylabel('Distance (mm)')
"""
# 设置频谱图的标题和标签
ax2.set_title('FFT Spectrum')
ax2.set_xlabel('Frequency (Hz)')
ax2.set_ylabel('Amplitude')
"""
plt.ion()  # 开启交互模式


try:
    while True:
        if ser.in_waiting > 0:
            # 读取并解析串口数据
            data = ser.readline().decode().strip()
            
            # 使用正则表达式从数据中提取距离
            match = re.match(r'Distance=\s*(\d+)mm', data)
            if match:
                distance = int(match.group(1))
            '''    if distance<300:
                 distance=None
              '''     
            '''     # 应用指数平滑滤波算法
                if filtered_distance is None:
                    filtered_distance = distance
                else:
                    filtered_distance = alpha * distance + (1 - alpha) * filtered_distance
            '''
                # 将距离数据添加到列表中
            distances.append(distance)

            # 绘制距离曲线图
            ax1.plot(distances, 'b-')
            plt.pause(0.01)
            """
            # 执行FFT
            if len(distances) >= N:
                yf = np.fft.fft(distances)
                yf = 2.0/N * np.abs(yf[:N//2])

                ax2.clear()  # 清空频谱图
                ax2.plot(xf, yf, 'r-')
                plt.pause(0.01)

            """

            
except KeyboardInterrupt:
    # 当按下 Ctrl+C 时退出循环
    pass
finally:
    # 关闭串口
    ser.close()

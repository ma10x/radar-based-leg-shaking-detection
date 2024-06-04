import serial
import matplotlib.pyplot as plt

# 设置串口参数
port = 'COM7'  # 根据您的系统和连接端口进行调整
baudrate = 115200
timeout = 1

# 打开串口
ser = serial.Serial(port, baudrate, timeout=timeout)

# 初始化数据列表
distances = []

# 绘制曲线图
plt.ion()  # 开启交互模式
plt.xlabel('Time')
plt.ylabel('Distance (mm)')
plt.title('Distance over Time')

try:
    while True:
        if ser.in_waiting > 0:
            # 读取并解析串口数据
            data = ser.readline().decode().strip()
            distance = int(data)
            
            # 将距离数据添加到列表中
            distances.append(distance)
            
            # 绘制距离曲线图
            plt.clf()
            plt.plot(distances)
            plt.pause(0.01)
except KeyboardInterrupt:
    # 当按下 Ctrl+C 时退出循环
    pass
finally:
    # 关闭串口
    ser.close()

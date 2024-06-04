import serial
import numpy as np

# 设置串口参数
port = 'COM8'  # 根据您的系统和连接端口进行调整
baudrate = 115200
timeout = 1

# 打开串口
ser = serial.Serial(port, baudrate, timeout=timeout)
# 从终端读取输入数据
data_to_send = input("Enter data to send (press 'q' to quit): ")
        
# 向串口发送数据
ser.write(data_to_send.encode('ascii'))
try:
    while True:
        if ser.in_waiting > 0:
            # 读取并解析串口数据
            data = ser.readline().decode().strip()
            # 处理数据，例如打印
            print(data)


except KeyboardInterrupt:
    # 当按下 Ctrl+C 时退出循环
    pass
finally:
    # 关闭串口
    ser.close()
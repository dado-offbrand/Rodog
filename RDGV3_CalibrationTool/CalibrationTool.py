import sys
from adafruit_pca9685 import PCA9685
import busio
import board

i2c = busio.I2C(board.SCL, board.SDA)

pca = PCA9685(i2c_bus=i2c)
pca.frequency = 50
pca.channels[0].duty_cycle = 0

SERVO_MIN = 0
SERVO_MAX = 4095

def position_servo(channel, angle):
    pulse_width = int((angle / 180) * (SERVO_MAX - SERVO_MIN) + SERVO_MIN)
    pca.channels[channel].duty_cycle = pulse_width

if __name__ == '__main__':
    if (len(sys.argv)) != 3: # first arguement was the script to run, it is actually 3 arguements total
        print("Failed to position, ==2 arguements required (channel, angle)")
    else:
        channel = sys.argv[1]
        angle = sys.argv[2]
        position_servo(channel, angle)

    pca.channels[0].duty_cycle = 0

# command to run via SSH terminal
# python /home/rodog/Desktop/RDGV2_CalibrationTool/main.py 0 90
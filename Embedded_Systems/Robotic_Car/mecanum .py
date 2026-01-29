#!/usr/bin/python3
# coding=utf8
import sys
sys.path.append('/home/pi/MasterPi/')
import time
import signal
import HiwonderSDK.mecanum as mecanum
if sys.version_info.major == 2:
print('Please run this program with python3!')
sys.exit(0)
''')
chassis = mecanum.MecanumChassis()
start = True
#Pre-closing processing
def Stop(signum, frame):
global start
start = False
print('Closing...')
chassis.set_velocity(0,0,0) #Stop all motors
signal.signal(signal.SIGINT, Stop)
if __name__ == '__main__':
while start:
chassis.set_velocity(50,90,0)
time.sleep(1)
chassis.set_velocity(50,0,0)
time.sleep(1)
chassis.set_velocity(50,270,0)
time.sleep(1)
chassis.set_velocity(50,180,0)
time.sleep(1)
chassis.set_velocity(0,0,0) #Stop all motors
print(Closed)

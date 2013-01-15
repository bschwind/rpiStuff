import RPi.GPIO as GPIO
import math
import os
from time import sleep

OKLED = 16

GPIO.setmode(GPIO.BCM)
GPIO.setup(OKLED, GPIO.OUT)

sleepAmt = 0.0
refresh = 1.0/60
time = 0
maxPeriod = 5.0

while True:
	load = 1.0 - os.getloadavg()[0]
	sleepAmt = math.sin(time/(0.001 + maxPeriod*load)) + 1
	sleepAmt *= 0.5

	GPIO.output(OKLED, GPIO.LOW)
	sleep(refresh*sleepAmt)
	GPIO.output(OKLED, GPIO.HIGH)
	sleep(refresh * (1-sleepAmt))

	sleepAmt += 0.001
	time += 1
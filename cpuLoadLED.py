import RPi.GPIO as GPIO
import math
import os
from time import sleep

OKLED = 16
dutyCycle = 0.0
frequency = 1.0/60.0
time = 0
maxPeriod = 5.0

GPIO.setmode(GPIO.BCM)
GPIO.setup(OKLED, GPIO.OUT)

while True:
	load = 1.0 - os.getloadavg()[0]

	dutyCycle = math.sin(time/(0.001 + maxPeriod*load)) + 1
	dutyCycle *= 0.5

	GPIO.output(OKLED, GPIO.LOW)
	sleep(frequency*dutyCycle)
	GPIO.output(OKLED, GPIO.HIGH)
	sleep(frequency * (1-dutyCycle))

	time += 1

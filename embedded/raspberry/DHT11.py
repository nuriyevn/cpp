#!/usr/bin/python
import sys
import Adafruit_DHT

while True:
    humidity, temperature = Adafruit_DHT.read_retry(11, 4)
    if humidity is not None and temperature is not None:
        print ('Temp=%.0f*C  Humidity=%.0f%%' % (temperature, humidity))
    else:
        print ('Failed to get reading. Try again!')

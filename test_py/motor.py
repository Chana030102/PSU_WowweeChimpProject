# Aaron Chan
# Wowwee Chimpanzee Hack Project
# Using MCP3008 (ADC) and L239D (motor driver)
#
# Move a motor UNTIL a designated "limit" value previously 
# recorded to get the motor to move to a certain position

# GPIO Library 
import time
import RPi.GPIO as GPIO

# SPI library and MCP3008
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008

GPIO.setmode(GPIO.BOARD)
L_Upper = 345
L_Lower = 580
wait = 0.2

# Hardware SPI Config
SPI_PORT   = 0
SPI_DEVICE = 0
mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))

# Define Pins for motors and ADC read
Motor1A  = 29 # 1A open
Motor2A  = 31 # 2A close
Motor12E = 37 # Enable CH1 CH2
MotorCH  = 5  # Read MCP3008 CH0

# Setup GPIO pin modes
GPIO.setup(Motor1A ,GPIO.OUT)
GPIO.setup(Motor2A ,GPIO.OUT)
GPIO.setup(Motor12E,GPIO.OUT)

# Initialize to low (just in case)
GPIO.output(Motor1A ,GPIO.LOW)
GPIO.output(Motor2A ,GPIO.LOW)
GPIO.output(Motor12E,GPIO.HIGH)

# Move motor back and forth
while True:
    try:
        test = mcp.read_adc(MotorCH)
#       print "Position: {}".format(test)
        if test<= L_Upper:
            GPIO.output(Motor2A,GPIO.LOW)
            GPIO.output(Motor1A,GPIO.HIGH)
            time.sleep(wait)
        else:
            GPIO.output(Motor1A,GPIO.LOW)
            GPIO.output(Motor2A,GPIO.HIGH)
    # Exception for Ctrl+C interrupt for cleanup
    except KeyboardInterrupt:
        time.sleep(wait)
        print" Closig Program"
        GPIO.cleanup()

GPIO.cleanup()

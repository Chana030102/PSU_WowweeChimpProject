# Wowwee Chimpanzee Hack Project
# Using MCP3008 (ADC) and L293D (motor driver)
#
# Control multiple motors and see how smoothly the
# head moves. Use limit values to test for stopping
# conditions.
#
#  Motor      Lower   Upper
# Head_LR      278     840
# Head_UpD     360     772
# Mouth        351     580
# Eyebrows     407     602
# Eyes_UpD     483     758
# Eyes_LR      392     627

import time
import RPi.GPIO as GPIO
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008

# Hardware SPI Config
SPI_PORT   = 0
SPI_DEVICE = 0
mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))

GPIO.setmode(GPIO.BOARD)

# Limit Values
BrowUp    = 602
BrowLo    = 407
EyesUpDUp = 758
EyesUpDLo = 483
MouthUp   = 580
MouthLo   = 351
EyesLRUp  = 627
EyesLRLo  = 392

# Define Pins for Motors
M_Enable   = 35
M_BrowU    = 15
M_BrowD    = 13
M_EyesU    = 11 
M_EyesD    = 7
M_MouthO   = 8
M_MouthC   = 10
M_EyesL    = 5
M_EyesR    = 3

# Define pins for ADC channels
E_Brow    = 2
E_EyesLR  = 0
E_EyesUpD = 1
E_Mouth   = 3

# Setup GPIO pin modes
GPIO.setup(M_Enable  ,GPIO.OUT)
GPIO.setup(M_BrowU   ,GPIO.OUT)
GPIO.setup(M_BrowD   ,GPIO.OUT)
GPIO.setup(M_EyesU,GPIO.OUT)
GPIO.setup(M_EyesD,GPIO.OUT)
GPIO.setup(M_MouthO  ,GPIO.OUT)
GPIO.setup(M_MouthC  ,GPIO.OUT)
GPIO.setup(M_EyesL ,GPIO.OUT)
GPIO.setup(M_EyesR ,GPIO.OUT)

GPIO.output(M_Enable, GPIO.HIGH) # Enable motor drivers

# Turn motors on in one direction to start
GPIO.output(M_BrowU, GPIO.HIGH)
GPIO.output(M_BrowD, GPIO.LOW)
GPIO.output(M_EyesU, GPIO.HIGH)
GPIO.output(M_EyesD, GPIO.LOW)
GPIO.output(M_MouthO, GPIO.HIGH)
GPIO.output(M_MouthC, GPIO.LOW)
GPIO.output(M_EyesL, GPIO.HIGH)
GPIO.output(M_EyesR, GPIO.LOW)


while True:
    try:
        time.sleep(0.5)
        if mcp.read_adc(E_Brow) <= BrowLo:
            GPIO.output(M_BrowU, GPIO.LOW)
            print "BrowA"
        elif mcp.read_adc(E_Brow) >= BrowUp:
            GPIO.output(M_BrowU,GPIO.LOW)
            print "BrowB"
        
        if mcp.read_adc(E_EyesLR) <= EyesLRLo:
            GPIO.output(M_EyesL, GPIO.LOW)
            print "EyesLR A"
        elif mcp.read_adc(E_EyesLR) >= EyesLRUp:
            GPIO.output(M_EyesL, GPIO.LOW)
            print "EyesLR B"
        
        if mcp.read_adc(E_EyesUpD) <= EyesUpDLo:
            GPIO.output(M_EyesU,GPIO.LOW)
            print "EyesUpD A"       
        elif mcp.read_adc(E_EyesUpD) >= EyesUpDUp:
            GPIO.output(M_EyesU,GPIO.LOW)
            print "EyesUpDB"
        
        if mcp.read_adc(E_Mouth) <= MouthLo:
            GPIO.output(M_MouthO,GPIO.LOW)
            print "Mouth A"
        elif mcp.read_adc(E_Mouth) >= MouthUp: 
            GPIO.output(M_MouthO,GPIO.LOW)
            print "Mouth B"

# Exception for Ctrl+C interrupt. Cleanup before leaving
    except KeyboardInterrupt:
        time.sleep(0.5)
        print "Closing Program...."
        GPIO.cleanup()

# Shouldn't make it out here, but just in case... 
GPIO.cleanup()

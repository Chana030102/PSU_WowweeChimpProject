/*
 * chimp_def.h
 *
 * Interface with Chimp using Raspberry Pi 3.
 * Drive motors using L293D.
 * Read analog data from rotary encoders for motor
 * positions with the assistance of MCP3008.
 *
 * The Chimp has a total of 8 motors:
 * (1) Head     : Up,Down
 * (2) Head     : L, R
 * (3) Eyes     : U, D
 * (4) Eyes     : L, R
 * (5) Eyebrows : U, D
 * (6) Eyelids  : U, D
 * (7) Mouth    : U, D
 * (8) Nose     : U, D
 *
 * All but the nose have rotary encoders. The nose has a limit switch.
 *
 * Motor drivers will be powered by 5V pin from Raspberry Pi.
 * The ADC (MCP3008) will be powered by a 3.3V pin.
 * Encoders will be powered by a 3.3V pin.
 *
 * In this header file, we define the following
 * necessary items for motors and encoders:
 *  - GPIO pins
 *  - Limit values
 *  - Analog input channels
 **/
// arbitrary base for wiringPi to assign
// pins for use. 
#define BASE 200 
#define SPI_CHAN 0 

// MCP3008 analog channels 
#define E_EYES_LR 0
#define E_EYES_UD 1
#define E_BROWS   2
#define E_MOUTH   3
#define E_HEAD_UD 4
#define E_HEAD_LR 5
//#define E_LIDS    6

// GPIO pins for motors
#define M_ENABLE  26 // physical pin 37
#define M_MOUTH_O 14 // physical pin 8
#define M_MOUTH_C 15 // physical pin 10
#define M_EYES_U  17 // physical pin 11 
#define M_EYES_D   4 // physical pin 7
#define M_EYES_L   3 // phyiscal pin 5
#define M_EYES_R   2 // physical pin 3  
#define M_BROWS_U 27 // physical pin 13
#define M_BROWS_D 22 // physical pin 15
#define M_HEAD_U  23 // physical pin 16
#define M_HEAD_D  24 // physical pin 18
#define M_HEAD_R   5 // physical pin 29
#define M_HEAD_L   6 // physical pin 31
//#define M_LIDS_U 
//#define M_LIDS_D
//#define M_NOSE

// Limit values for motor positions
#define L_MOUTH_C 370
#define L_MOUTH_O 530
#define L_EYES_L  390
#define L_EYES_R  620
#define L_EYES_U   14
#define L_EYES_D   30
#define L_BROWS_U 415
#define L_BROWS_D 590
#define L_HEAD_U  400
#define L_HEAD_D  740
#define L_HEAD_R  760
#define L_HEAD_L  330
//#define L_LIDS_U
//#define L_LIDS_D

// Macros for driving motors
#define WRITE_HIGH(pin)  digitalWrite(pin,HIGH)
#define WRITE_LOW(pin)   digitalWrite(pin,LOW)
#define SET_OUT(pin)     pinMode(pin,OUTPUT) 
#define SET_IN(pin)      pinMode(pin,INPUT)

extern int mcp3004Setup(int pinBase, int spiChannel);


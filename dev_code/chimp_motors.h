/*
 * chimp_motors.h 
 *
 * Functions to work with the hacked Wowwee Chimpanzee.
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
 **/
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

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
#define M_ENABLE  25 // physical pin 22
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
/*
#define M_LIDS_U 
#define M_LIDS_D
#define M_NOSE
*/

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
/*
#define L_LIDS_U
#define L_LIDS_D
*/

// Macros for driving motors
#define WRITE_HIGH(pin)  digitalWrite(pin,HIGH)
#define WRITE_LOW(pin)   digitalWrite(pin,LOW)


/*
 * Setup GPIO pins with BCM numbering.
 * Also setup SPI interfacing with MCP3008.
 * pins to read from for different analog inputs
 * will be BASE+channel 
 **/
int chimp_setup(void)
{
   wiringPiSetupGpio();  
   mcp3004Setup( BASE,SPI_CHAN );
   return 0;
}

/* 
 * move_motor - move motor to desired position
 * @motor        - string to display for error message
 * @limit_h      - upper limit value
 * @limit_l      - lower limit value
 * @channel      - analog channel on ADC to read from
 * @motor_h      - motor that will increase position value
 * @motor_l      - motor that will decrease position value
 * @position_val - desired position to move motor to
 *
 * returns 0 upon success
 * returns -1 when given position value out of range
 **/
int move_motor(char *motor, int limit_h, int limit_l, int channel, 
               int motor_h, int motor_l, int position_val)
{
    int current = analogRead(BASE+channel);

    // Test for out of range position value request
    if(position_val < limit_l || position_val > limit_h)
    {
        fprintf(stderr,"position_val of %d out of range for %s.\n",motor,position_val);
        return -1;
    } 
    
    WRITE_HIGH(M_ENABLE); // Enable motor drivers
    // Move head to desired position
    if(position_val < current)
    {
        while(position_val < analogRead(BASE+channel))
        {   
            WRITE_HIGH(motor_h);   
        }
        WRITE_LOW(motor_h);
    }
    else if(position_val > current)
    {
        while(position_val > analogRead(BASE+channel))
        {   
            WRITE_HIGH(motor_l);  
        }
        WRITE_LOW(motor_l);
    }
    
    WRITE_LOW(M_ENABLE); // disable motor drivers
    return 0;
}

// Move head up or down to desired position
int head_UpD(int position_val)
{
    return move_motor("Head_UpD",L_HEAD_D,L_HEAD_U,E_HEAD_UD,
                      M_HEAD_D,M_HEAD_U,position_val);
}

// Move head left or right to desired position
int head_LR(int position_val)
{
    return move_motor("Head_LR",L_HEAD_L,L_HEAD_R,E_HEAD_LR,
                      M_HEAD_R,M_HEAD_L,position_val);
}

// Move eyes up or down to desired position
int eyes_UpD(int position_val)
{
    return move_motor("Eyes_UpD",L_EYES_D,L_EYES_U,E_EYES_UD,
                      M_EYES_D,M_EYES_U,position_val);
}

// Move eyes left or right to desired position
int eyes_LR(int position_val)
{
    return move_motor("Eyes_LR",L_EYES_R,L_EYES_L,E_EYES_LR,
                      M_EYES_R,L_EYES_L,position_val);
}

// Move eye brows up or down to desired position
int brows_UpD(int position_val)
{
    return move_motor("Eyebrows",L_BROWS_D,L_BROW_U,E_BROWS,
                      M_BROWS_D,M_BROWS_U,position_val);
}

// Move mouth open or close to desired position
int mouth_UpD(int position_val);
{
    return move_motor("Mouth",L_MOUTH_O,L_MOUTH_C,E_MOUTH,
                      M_MOUTH_O,M_MOUTH_C,position_val);
}

/*
// Move nose
int nose(int position_val);
// Move eye lids up or down to desired position
int lids_UpD(int position_val)
{
    return move_motors("Eyelids",
}
*/

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

// GPIO pins for motors
#define M_ENABLE 26
#define M_MOUTH_O 2
#define M_MOUTH_C 3
/*
#define M_EYES_U
#define M_EYES_D
#define M_EYES_L
#define M_EYES_R
#define M_BROWS_U
#define M_BROWS_D
#define M_LIDS_U
#define M_LIDS_D
#define M_NOSE
*/

// Limit values for motor positions
#define L_MOUTH_C 370
#define L_MOUTH_O 530
#define L_EYES_L 390
#define L_EYES_R 620
#define L_EYES_U 14
#define L_EYES_D 30
#define L_BROWS_U 415
#define L_BROWS_D 590

/*
#define L_HEAD_U 
#define L_HEAD_D
#define L_HEAD_R
#define L_HEAD_L
#define L_LIDS_U
#define L_LIDS_D
*/

// Macros for driving motors

/*
 * Setup GPIO pins with BCM numbering.
 * Also setup SPI interfacing with MCP3008.
 * pins to read from for different analog inputs
 * will be BASE+channel 
 **/
int chimp_setup(void)
{
   wiringPiSetupGpio();  
   mcp3004Setup(BASE,0);
   return 0;

}

/*
 * Face the head up or down,
 * moving it to the desired position.
 **/
int head_UpD(int position_val)
{
    int current = analogRead(BASE+E_HEAD_UpD);

    if(position_val < L_HEAD_U && position_val > L_HEAD_D)
    {
        fprintf(stderr,"position_val of %d out of range for motor HEAD_UpD\n",position_val);
        return -1;
    }
    else if(position_val < current)
    {
        while(position_val < analogRead(BASE+E_HEAD_UpD))
        {
            digitalWrite(M_MOUTH_C, HIGH);
        }
        digitalWrite(M_MOUTH_C,LOW);
    }

        
    

}


int head_LR(int position_val);

int eyes_UpD(int position_val);
int eyes_RL(int position_val);

int brows_UpD(int position_val);
int lids_UpD(int position_val);

int mouth_UpD(int position_val);

int nose_up(int position_val);
int nose_down(int position_val);

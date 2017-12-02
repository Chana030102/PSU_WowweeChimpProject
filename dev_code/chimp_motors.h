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
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include "chimp_def.h"

/*
 * Setup GPIO pins with BCM numbering.
 * Also setup SPI interfacing with MCP3007.
 * pins to read from for different analog inputs
 * will be BASE+channel 
 **/
int chimp_setup(void)
{
   wiringPiSetupGpio();  
   mcp3004Setup( BASE,SPI_CHAN );
   
   // Set pins as output
   SET_OUT(M_ENABLE);
   SET_OUT(M_MOUTH_O);
   SET_OUT(M_MOUTH_C);
   SET_OUT(M_EYES_U);
   SET_OUT(M_EYES_D);
   SET_OUT(M_EYES_L);
   SET_OUT(M_EYES_R);
   SET_OUT(M_BROWS_U);
   SET_OUT(M_BROWS_D);
   SET_OUT(M_HEAD_U);
   SET_OUT(M_HEAD_D);
   SET_OUT(M_HEAD_R);
   SET_OUT(M_HEAD_L);
   //SET_OUT(M_LIDS_U);
   //SET_OUT(M_LIDS_D);
   //SET_OUT(M_NOSE);

   // Set all motor pins to low at start
   WRITE_LOW(M_ENABLE);
   WRITE_LOW(M_MOUTH_O);  
   WRITE_LOW(M_MOUTH_C);  
   WRITE_LOW(M_EYES_U);  
   WRITE_LOW(M_EYES_D);  
   WRITE_LOW(M_EYES_L);  
   WRITE_LOW(M_EYES_R);  
   WRITE_LOW(M_BROWS_U);  
   WRITE_LOW(M_BROWS_D);  
   WRITE_LOW(M_HEAD_U);  
   WRITE_LOW(M_HEAD_D);  
   WRITE_LOW(M_HEAD_R);  
   WRITE_LOW(M_HEAD_L);
   //WRITE_LOW(M_LIDS_U);
   //WRITE_LOW(M_LIDS_D);
   //WRITE_LOW(M_NOSE);
   
   return 0;
}

/* 
 * move_motor - move motor to desired position
 * @motor        - string to display for error message
 * @limit_h      - upper limit value
 * @limit_l      - lower limit value
 * @channel      - analog channel on ADC to read from
 * @motor_h      - motor that will increment position value
 * @motor_l      - motor that will decrement position value
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
        fprintf(stderr,"position_val of %d out of range for %s.\n",position_val,motor);
        return -1;
    } 
    
    printf("moving %s\n",motor);    
    WRITE_HIGH(M_ENABLE); // Enable motor drivers
// Move head to desired position
    if(position_val < current)
    {
        printf("desired position is less than current(%d)\n",current);   
        while(position_val < analogRead(BASE+channel))
        {   
            WRITE_HIGH(motor_h);
        }
        WRITE_LOW(motor_h);
    }
    else if(position_val > current)
    {
        printf("desired position is greater than current(%d)\n",current);

        while(position_val > analogRead(BASE+channel))
        {   
            WRITE_HIGH(motor_l);  
        }
        WRITE_LOW(motor_l);
    }
    WRITE_LOW(M_ENABLE); // disable motor drivers
    return 0;
}

/*
 * calc_position - calculates a position value based off degrees given
 * @degrees - degrees position desired for chimp position
 * @pos_max - the upper limit value of the motor
 * @pos_min - the lower limit value of the motor
 *
 * returns calculated position upon success
 **/
int calc_position(int degrees, int pos_max, int pos_min)
{
    div_t temp; // struct to hold quotient and remainder
    int position; // return this upon success

    // Calculate position value
    position = abs(pos_max - pos_min);
    position *= (degrees + 90);
    
    if(position != 0)
    {
        temp = div(position,180);
        position = temp.quot;
        if(temp.rem >= 90)
            position++;
    }
    return pos_min + position;
}

/*
 * head_UpD - moves motor for up and down motion for the head
 * @degrees - desired position in the form of degrees
 *
 * The head is limited to looking straight forward and upward,
 * so the input range will be limitted between 0 and +90.
 *
 * returns -1 if invalid input
 * returns 0 on success
 **/
int head_UpD(int degrees)
{
    int position;
    
    if(degrees < 0 || degrees > 90)
    {
        fprintf(stderr,"Position of %d degrees is out of range for Head_UD\n",degrees);
        return -1;
    }
    else if(degrees == 0)
        degrees-=90;
    position = calc_position(degrees, L_HEAD_D, L_HEAD_U);

    fprintf(stdout,"Head_UD value = %d\n",position);   

    return move_motor("Head_UpD",L_HEAD_D,L_HEAD_U,E_HEAD_UD,
                      M_HEAD_D,M_HEAD_U,position);
}

/*
 * head_LR - moves motor for left and right motion for the head
 * @degrees - desired position in the form of degrees
 *
 * Degrees input will be limitted to the range of -90 and +90
 * 
 * returns -1 if invalid input
 * returns 0 on success
 **/
int head_LR(int degrees)
{
    int position;

    if(degrees < -90 || degrees > 90)
    {
        fprintf(stderr,"Position of %d degrees is out of range for HEAD_LR\n",degrees);
        return -1;
    }
    position = calc_position(degrees, L_HEAD_R, L_HEAD_L);
    fprintf(stdout,"Head_LR value = %d\n",position);
    
    return move_motor("Head_LR",L_HEAD_R,L_HEAD_L,E_HEAD_LR,
                      M_HEAD_R,M_HEAD_L,position);
}

/*
 * eyes_UpD - moves motor for up and down motion for the eyes
 * @degrees - desired position in the form of degrees
 *
 * Degrees input will be limited to the range of -90 and +90
 *
 * returns -1 if invalid input
 * returns 0 on success
 **/
int eyes_UpD(int degrees)
{
    int position;

    if(degrees < -90 || degrees > 90)
    {
        fprintf(stderr,"Position of %d degrees is out of range for EYES_UD\n",degrees);
        return -1;
    }
    position = calc_position(degrees, L_EYES_D, L_EYES_U);
    fprintf(stdout,"Eyes_UpD value = %d\n",position);

    return move_motor("Eyes_UpD",L_EYES_D,L_EYES_U,E_EYES_UD,
                      M_EYES_D,M_EYES_U,position);
}

/*
 * eyes_LR - moves motor for left and right motion for the eyes
 * @degrees - desired position in the form of degrees
 *
 * Degrees input will be limited to the range of -90 and +90
 *
 * returns -1 if invalid input
 * returns 0 on success
 **/
int eyes_LR(int degrees)
{
    int position;

    if(degrees < -90 || degrees > 90)
    {
        fprintf(stderr,"Position of %d degrees is out of range for Eyes_LR\n,"degrees);
        return -1;
    }
    position = calc_position(degrees, L_EYES_R, L_EYES_L);
    fprintf(stdout,"Eyes_LR value = %d\n",position);

    return move_motor("Eyes_LR",L_EYES_R,L_EYES_L,E_EYES_LR,
                      M_EYES_R,L_EYES_L,position_val);
}

/*
 * brows_UpD - moves motor for the up and down motion for the eyebrows
 * @degrees - desired position in the form of degrees
 *
 * Degrees input will be limited to the range of 0 and +90
 *
 * returns -1 if invalid input
 * returns 0 on success
 **/
int brows_UpD(int degrees)
{
    int position;

    if(degrees < 0 || degrees > 90)
    {
        fprintf(stderr,"Position of %d degrees is out of range for Brows\n",degrees);
        return -1;
    }
    else if(degrees == 0)
        degrees-=90;

    position = calc_position(degrees, L_BROWS_D, L_BROWS_U);
    fprintf(stdout,"Brows value = %d\n",position);

    return move_motor("Eyebrows",L_BROWS_D,L_BROWS_U,E_BROWS,
                      M_BROWS_D,M_BROWS_U,position_val);
}

/*
 * mouth_UpD - moves motor for the up and down motion for the mouth
 * @degrees - desired position in the form of degrees
 *
 * Degrees input will be limited to the range of 0 and +90
 *
 * returns -1 if invalid input
 * returns 0 on success
 **/
int mouth_UpD(int degrees)
{
    int position;

    if(degrees < 0 || degrees > 90)
    {
        fprintf(stderr,"Position of %d degrees is out of range for Mouth\n",degrees);
        return -1;
    }
    else if(degrees == 0)
        degrees-=90;

    position = calc_position(degrees, L_MOUTH_O, L_MOUTH_C);
    fprintf(stdout,"Mouth value = %d\n",position);

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

/*
 *
 **/


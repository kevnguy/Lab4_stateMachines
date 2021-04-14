/*	Author: Kevin Nguyen knguy523@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: Buttons are connected to PA0 and PA1. Output for PORTC is waitPressially 7. Pressing PA0 
 *	increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). 
 *	If both buttons are depressed (even if not waitPressially simultaneously), PORTC resets to 0. 
 *		
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum C_states {C_start, C_waitPress, C_inc, C_dec, C_waitI, C_waitD, C_reset} c_state;

void Tick_C(){
    switch(c_state){
        case C_start:
            c_state = C_waitPress;
	    PORTC = 0x07;
            break;
	case C_waitPress:
            if((PINA & 0x03) == 0x01){
                c_state = C_inc;
            }
            else if((PINA & 0x03) == 0x02){
                c_state = C_dec;
            }
            else if((PINA & 0x03) == 0x03){ 
		c_state = C_reset;
            }
            else{
                c_state = C_waitPress;
            }
            break;
        case C_inc:
	    c_state = C_waitI;
	    break;
	case C_waitI:
	    if((PINA & 0x03) == 0x01){
            	c_state = C_waitI;
	    }
	    else if((PINA & 0x03) == 0x02){
            	c_state = C_dec;
	    }
	    else if((PINA & 0x03) == 0x03){
		c_state = C_waitPress;
		PORTC = 0x00;
	    }
	    else 
		c_state = C_waitPress;
            break;
        case C_dec:
	    c_state = C_waitD;
	    break;
	case C_waitD:
	    if((PINA & 0x03) == 0x02){
            	c_state = C_waitD;
	    }
	    else if((PINA & 0x03) == 0x01){
            	c_state = C_inc;
	    }
	    else if((PINA & 0x03) == 0x03){
		c_state = C_waitPress;
		PORTC = 0x00;
	    }
	    else 
		c_state = C_waitPress;
            break;
        case C_reset:
            c_state = C_waitPress;
            break;
        default:
            c_state = C_waitPress;
            break;
    }

    switch(c_state){
        case C_start:
            PORTC = 0x07; break;
        case C_waitPress:
            break;
        case C_inc:
            if(PORTC < 0x09){
                PORTC++;
            }
            break;
	case C_waitI:
	    break;
	case C_waitD:
	    break;
        case C_dec:
            if(PORTC > 0x00){
                PORTC--;
            }
            break;
        case C_reset:
            PORTC = 0x00; break;
        default:
            break;
    }   

}

int main(void) {
    /* Insert DDR and PORT waitPressializations */
	DDRA = 0x00; PORTA = 0x03;	// PORTA is input
	DDRC = 0xFF; PORTB = 0x00;	// PORTC is output
    /* Insert your solution below */
	//unsigned char temp = 0x00;
	c_state = C_start;
    while (1) {
        Tick_C();
	//temp = PORTC;
    }
    return 1;
}

/*	Author: Kevin Nguyen knguy523@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: A household has a digital combination deadbolt lock system on the doorway. 
 *	The system has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing
 *	and releasing 'Pnd', then pressing 'Y', should unlock the door by setting PB0 to 1. Any other sequence
 *	fails to unlock. Pressing a button from inside the house (PA7) locks the door (PB0=0). For debugging
 *	purposes, give each state a number, and always write the current state to PORTC (consider using the
 *	enum state variable). Also, be sure to check that only one button is pressed at a time. 
 *
 *			
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum l_states {l_start, l_wait, l_Pnd, l_Y, l_unlock, l_lock} l_state;

void Tick(){
    switch(l_state){
        case l_start:
            l_state = l_wait;
            break;
	case l_wait:
            if((PINA & 0x87) == 0x04){
                l_state = l_Pnd;
            }
	    else if((PINA & 0x87) == 0x80){
		l_state = l_lock;
	    }
            else{
                l_state = l_wait;
            }
            break;
        case l_Pnd:
	    if((PINA & 0x87) == 0x04){
		l_state = l_Pnd;
	    }		
	    else if((PINA & 0x87) == 0x00){
		l_state = l_Y;
	    }	   
	    else{
		l_state = l_start;
	    }
            break;
	case l_Y:
	    if((PINA & 0x87) == 0x02){
		l_state = l_unlock;
	    }
	    else if((PINA & 0x87) == 0x00){
		l_state = l_Y;
	    }
	    else{
		l_state = l_start;
	    }
        case l_unlock:
	    if((PINA & 0x87) == 0x02 || PINA == 0x00){
		l_state = l_unlock;
	    }
	    else{ 
		l_state = l_wait;
	    }
            break;
        case l_lock:
	    l_state = l_wait;
	    break;
        default:
            l_state = l_start;
            break;
    }

    switch(l_state){
        case l_start:
            PORTC = l_state;
	    PORTB = 0x00; 
	    break;
        case l_wait:
            break;
        case l_Pnd:
	    PORTC = l_state;
            break;
	case l_Y:
	    PORTC = l_Y;
	    break;
        case l_unlock:
            PORTC = l_state;
	    PORTB = 0x01;
	    break;
        case l_lock:
	    PORTC = l_state;
	    PORTB = 0x00;
            break;
        default:
            break;
    }   

}

int main(void) {
    /* Insert DDR and PORT waitializations */
	DDRA = 0x00; PORTA = 0x87;	// PORTA is input
	DDRB = 0xFF; PORTB = 0x00;	// PORTB is output for lock
	DDRC = 0xFF; PORTB = 0x00;	// PORTC is output for states
    /* Insert your solution below */
    l_state = l_start;
    while (1) {
        Tick();
    }
    return 1;
}

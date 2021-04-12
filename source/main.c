/*	Author: Kevin Nguyen knguy523@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: A household has a digital combination deadbolt lock system on the doorway. 
 *	The system has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing
 *	and releasing '#', then pressing 'Y', should unlock the door by setting PB0 to 1. Any other sequence
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

enum l_states {l_start, l_init, l_waitPress#, l_#, l_unlock, l_lock} l_state;

void Tick_C(){
    unsigned char btnX = PINA & 0x01;
    unsigned char btnY = PINA & 0x02;
    unsigned char btn# = PINA & 0x06;
    unsigned char btnL = PINA & 0x80;
    switch(l_state){
        case C_start:
            l_state = l_init;
            break;
	case C_init:
            l_state = l_waitPress#;
            break;
        case l_waitPress#:
            if(!btnX && !btnY && !btnL && btn#){
                l_state = l_#;
            }
            else{
                l_state = l_waitPress#;
            }
            break;
        case l_#:
	    if(!btnX && btnY && !btnL && !btn#){
		l_state = l_unlock;
	    }
	    else if(btn#){
		l_state = l_#;
	    }
	    else{
		l_state = l_init;
	    }
            break;
        case l_unlock:
	    if(btnY || PINA == 0x00){
		l_state = l_unlock;
	    }
/*	    else{
		l_state = init;
	    } */
	    else if(btnL)
		l_state = l_lock;
            break;
        case l_lock:
	    l_state = l_waitPress#;
        default:
            l_state = l_init;
            break;
    }

    switch(l_state){
        case C_init:
            PORTC = 0x07; break;
        case C_waitPress:
            break;
        case C_inc:
            if(PORTC < 0x09){
                PORTC++;
            }
            break;
        case C_dec:
            if(PORTC > 0x00){
                PORTC--;
            }
            break;
        case C_waitFall:
            break;
        case C_reset:
            PORTC = 0x00; break;
        case C_waitFallR:
            break;
        default:
            break;
    }   

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x03;	// PORTA is input
	DDRC = 0xFF; PORTB = 0x00;	// PORTC is output
    /* Insert your solution below */
    l_state = C_start;
    while (1) {
        Tick_C();
    }
    return 1;
}

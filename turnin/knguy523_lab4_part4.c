/*	Author: Kevin Nguyen knguy523@ucr.edu
 *	 *  Partner(s) Name: 
 *	  *	Lab Section:
 *	   *	Assignment: Lab #4  Exercise #4
 *	    *	Exercise Description: Extend exercise 3 to lock when inputing code
 *	     *			
 *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	code, is my own original work.
 *	        */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum l_states {l_start, l_init, l_waitPressPnd, l_Pnd, l_unlock, l_lock} l_state;

void Tick(){
    unsigned char btnX = PINA & 0x01;
    unsigned char btnY = PINA & 0x02;
    unsigned char btnPnd = PINA & 0x04;
    unsigned char btnL = PINA & 0x80;
    unsigned char isopen = PORTB & 0x01;
    switch(l_state){
        case l_start:
            l_state = l_init;
            break;
	case l_init:
            l_state = l_waitPressPnd;
            break;
        case l_waitPressPnd:
            if(!btnX && !btnY && !btnL && btnPnd){
                l_state = l_Pnd;
            }
	    else if(btnL)
		l_state = l_lock;
            else{
                l_state = l_waitPressPnd;
            }
            break;
        case l_Pnd:
	    if(!btnX && btnY && !btnL && !btnPnd){
		if(!isopen){
		    l_state = l_unlock;
		}
		else{
		    l_state = l_lock;
		}
	    }
	    else if(btnPnd){
		l_state = l_Pnd;
	    }
	    else{
		l_state = l_init;
	    }
            break;
        case l_unlock:
	    if(btnY){
		l_state = l_unlock;
	    }
	    else if(btnL){
		l_state = l_lock;
	    }
	    else{
		l_state = l_waitPressPnd; 
	    } 
            break;
        case l_lock:
	    l_state = l_waitPressPnd;
	    break;
        default:
            l_state = l_init;
            break;
    }

    switch(l_state){
        case l_init:
            PORTC = l_state;
	    PORTB = 0x00; 
	    break;
        case l_waitPressPnd:
	    PORTC = l_state;
            break;
        case l_Pnd:
	    PORTC = l_state;
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
    /* Insert DDR and PORT initializations */
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

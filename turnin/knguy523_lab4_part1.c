/*	Author: Kevin Nguyen knguy523@ucr.edu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED is initially on.
 *	Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way
 *	after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LED_states {LED_init, LED_waitPress, LED_switch, LED_waitFall} LED_state;

void Tick_LED(){
    switch(LED_state){
	    case LED_init:
            LED_state = LED_waitPress;
            break;
        case LED_waitPress:
            if(PINA & 0x01){
                LED_state = LED_switch;
            }
            else{
                LED_state = LED_waitPress;
            }
            break;
        case LED_switch:
            LED_state = LED_waitFall;
            break;
        case LED_waitFall:
            if(PINA & 0x01){
                LED_state = LED_waitFall;
            }
            else{
                LED_state = LED_init;
            }
            break;
        default:
            LED_state = LED_init;
            break;
    }

    switch(LED_state){
        case LED_init:
            PORTB = 0x01; break;
        case LED_waitPress:
            break;
        case LED_switch:
            PORTB = 0x02; break;
        case LED_waitFall:
            break;
         default:
            break;
    }   

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;	// PORTA is input
	DDRB = 0xFF; PORTB = 0x01;	// PORTB is output
    /* Insert your solution below */
	unsigned char tempB = 0x00;
    while (1) {
        Tick_LED();
    }
    return 1;
}

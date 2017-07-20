#ifndef Interrupts_h
#define Interrupts_h

#include <avr/interrupt.h>

void enableExternalInterrupt(unsigned int INTX, unsigned int mode);
void disableExternalInterrupt(unsigned int INTX);
void attachISR(unsigned int INTX, void (*f)());
void attachTimer0Interrupt(void (*f)());
void detachTimerInterrupt();

#endif
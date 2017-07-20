
#include <avr/interrupt.h>

namespace {
	void(*isr0)();
	void(*isr1)();
	void(*isr2)();
	void(*isr3)();
	void(*timer)();
}
//ISR(INT0_vect) { (*isr0)(); }
ISR(INT1_vect) {
	(*isr1)();
}
ISR(INT2_vect) {
	(*isr2)();
}
ISR(INT3_vect) {
	(*isr3)();
}
ISR(TIMER0_COMP_vect) {
	(*timer)();
}

/*  Enables an external interrupt pin
INTX: Which interrupt should be configured?
INT0    - will trigger ISR(INT0_vect)
INT1    - will trigger ISR(INT1_vect)
INT2    - will trigger ISR(INT2_vect)
INT3    - will trigger ISR(INT3_vect)
mode: Which pin state should trigger the interrupt?
LOW     - trigger whenever pin state is LOW
FALLING - trigger when pin state changes from HIGH to LOW
RISING  - trigger when pin state changes from LOW  to HIGH
*/
void enableExternalInterrupt(unsigned int INTX, unsigned int mode)
{
	if (INTX > 3 || mode > 3 || mode == 1) return;
	cli();
	/* Allow pin to trigger interrupts        */
	EIMSK |= (1 << INTX);
	/* Clear the interrupt configuration bits */
	EICRA &= ~(1 << (INTX * 2 + 0));
	EICRA &= ~(1 << (INTX * 2 + 1));
	/* Set new interrupt configuration bits   */
	EICRA |= mode << (INTX * 2);
	sei();
}

void disableExternalInterrupt(unsigned int INTX)
{
	if (INTX > 3) return;
	EIMSK &= ~(1 << INTX);
}

void attachISR(unsigned int INTX, void(*f)())
{
	switch (INTX)
	{
	case INT0:
		isr0 = f;
		break;
	case INT1:
		isr1 = f;
		break;
	case INT2:
		isr2 = f;
		break;
	case INT3:
		isr3 = f;
		break;
	}
}

/* Configures Timer0 to call an interrupt routine*/
/* The interrupt routine that is called is ISR(TIMER0_COMP_vect)             */
/* Timer0 affects the arduino delay() function */
void attachTimer0Interrupt(void(*f)()) {

	cli();
	TCCR0 = 0;                         /* Clear current comparison value */
	TCNT0 = 0;                         /* Clear current timer value      */
	TCCR0 = (1 << CS00);              /* Set timer comparison mode      */
	TCCR0 |= (1 << CS01);			/* This is only an 8 bit timer*/
	TCCR0 |= (1 << CS02);			/* so set a 1024 prescaler */
	TIMSK |= (1 << OCIE0);            /* Set timer interrupt enable     */
	timer = f;
	sei();
	return;

}

/* Disables the Timer1 comparison interrupt */
void detachTimer0Interrupt()
{
	TIMSK &= ~(1 << OCIE0);
}
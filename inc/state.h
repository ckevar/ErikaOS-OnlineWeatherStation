/*
 * FSM Framework
 *
 * - C. Alvarado on 15th May, 2024
 * */

#ifndef STATE_H
#define STATE_H

#define SUBSTATEBITS        6
#define SUBSTATEMASK        ((1u << SUBSTATEBITS) - 1)
#define MKSTATE(super, sub) ((sub << SUBSTATEBITS) | (super & SUBSTATEMASK))
#define SUBSTATE(state)     (state >> SUBSTATEBITS)
#define SUPERSTATE(state)   (state & SUBSTATEMASK)
#define MAX_STATES          32

void state_init(void);
void allocate_state(void); 

#endif

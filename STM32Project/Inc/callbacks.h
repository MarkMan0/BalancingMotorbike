#ifndef _CALLBACKS_H
#define _CALLBACKS_H 1

//file containing prototypes for registering and calling callbacks
//for various communication events

#include <stdint.h>

/*		USART2 CALLBACKS		*/
//RX not empty
extern void (*usart2_rxne_callback)(uint8_t);
void USART2_register_RXNE_callback(void (*callback)(uint8_t));



#endif

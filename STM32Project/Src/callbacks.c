//definition of functions in callbacks.h

#include <stdlib.h>
#include "callbacks.h"

//usartx_rxne_callback is called from the ISR, for incoming data

void (*usart2_rxne_callback)(uint8_t) = NULL;	//callback is null at start

void USART2_register_RXNE_callback(void (*callback)(uint8_t)) {
	usart2_rxne_callback = callback;
}

void (*usart1_rxne_callback)(uint8_t) = NULL;	//callback is null at start

void USART1_register_RXNE_callback(void (*callback)(uint8_t)) {
	usart1_rxne_callback = callback;
}
//definition of functions in callbacks.h

#include <stdlib.h>
#include "callbacks.h"


void (*usart2_rxne_callback)(uint8_t) = NULL;	//callback is null at start

void USART2_register_RXNE_callback(void (*callback)(uint8_t)) {
	usart2_rxne_callback = callback;
}

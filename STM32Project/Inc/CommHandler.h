#ifndef _COMM_HANDLER_H
#define _COMM_HANDLER_H		1

#include <stdint.h>
#include "MovementController.h"
#include "CurrentController.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>

#define UART_RX_BUFLEN 	20





void handleCommand(uint8_t *cmd);

void receiveCharCallback(uint8_t c);

#endif

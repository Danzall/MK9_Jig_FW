/*
 * UART.c
 *
 *  Created on: Jun 21, 2018
 *      Author: Jeefo
 */
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include "stdio.h"
#include "board.h"
#include <string.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

int intFlag0;

void UART_Tx(char *data){
	int length;
	length = strlen(data);
	while(*data != 0){
		sendByte(*data);
		data++;
	}
}

void tx0Done(){
	intFlag0 = 1;
}


void sendByte(char send){

	TXD0 = send;
	while (intFlag0 != 1);
	intFlag0 = 0;

}

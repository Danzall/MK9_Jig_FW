/*
 * OW.c
 *
 *  Created on: Jun 22, 2018
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
#include "OW.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

int OWtimer;
int errorTimer;
char count[20];

void usDelay(int time){
	OWtimer = 0;
	while (OWtimer < time);
}

void ResetWait(){
	int time;

	TAGI = 0;
	while (TAGO == 1);
	OWtimer = 0;
	while (TAGO == 0);
	time = OWtimer;
	if (time > 500) Presence();
	sprintf(count, "OWtimer-%d\r\n", time);
	//UART_Tx(count);
}

void Presence(){
	usDelay(20);		//wait 20 us
	TAGI = 1;			//pull OW line line low
	usDelay(60);		//hold OW line low for 60us
	TAGI = 0;			//release OW line
	ReadByte();
}

void ReadByte(){
	char data = 0;
	char bitPlace = 1;
	char bitCount = 8;
	R_WDT_Restart();
	while (bitCount > 0){
		while (TAGO == 1) 		//wait for high to low
		OWtimer = 0;
		usDelay(3);
		LED2 ^= 1;
		if (TAGO == 1) data |= bitPlace;
		bitPlace = bitPlace << 1;
		bitCount--;
		while (TAGO == 0);		//wait for line to go high
	}
	//if (data == 0x33) txData();
	ProcessByte(data);
	sprintf(count, "OW data-%x\r\n", data);
	UART_Tx(count);
}

void ProcessByte(char dataR){

	if (dataR == 0x33){
		//
		txData();
		UART_Tx("Reset received Testing MK9 unit inputs....\r\n");
		LED1 ^= 1;
		Reset();
	}
	else if (dataR == 0x34){
		txData();
		SetIGN();
		LED2 ^= 1;
	}
	else if (dataR == 0x35){
		txData();
		SetRPM();
		LED3 ^= 1;
	}
	else if (dataR == 0x36){
		txData();
		SetPanic();
		LED4 ^= 1;
	}
	else if (dataR == 0x37){
		txData();
		SetInputA();
		LED5 ^= 1;
	}
	else if (dataR == 0x38){
		txData();
		SetInputB();
		LED6 ^= 1;
	}
	else if (dataR == 0x39){
		txData();
		SetInputC();

	}
	else if (dataR == 0x3A){
		txData();
		UART_Tx("Testing MK9 unit outputs....\r\n");

	}
	else if (dataR == 0x3B){
		txData();
		ReadDefault();

	}
	else if (dataR == 0x3C){
		txData();
		ReadImmob();

	}
	else if (dataR == 0x3D){
		txData();
		ReadOutput();

	}
	else if (dataR == 0x3E){
		txData();
		ReadLED();
		UART_Tx("Test complete\r\n");
	}
	else if (dataR == 0x53){

		UART_Tx("IGN trigger faulty\r\n");

	}
	else if (dataR == 0x54){
		UART_Tx("Panic trigger faulty\r\n");

	}
	else if (dataR == 0x55){
		UART_Tx("Input1 trigger faulty\r\n");

	}
	else if (dataR == 0x56){
		UART_Tx("Input2 trigger faulty\r\n");

	}
	else if (dataR == 0x57){
		UART_Tx("Input3 trigger faulty\r\n");

	}
	else if (dataR == 0x58){
		UART_Tx("RPM trigger faulty\r\n");

	}
	else if (dataR == 0x63){
		UART_Tx("IGN default faulty\r\n");

	}
	else if (dataR == 0x64){
		UART_Tx("Panic default faulty\r\n");

	}
	else if (dataR == 0x65){
		UART_Tx("Input1 default faulty\r\n");

	}
	else if (dataR == 0x66){
		UART_Tx("Input2 default faulty\r\n");

	}
	else if (dataR == 0x67){
		UART_Tx("Input3 default faulty\r\n");

	}
	else if (dataR == 0x68){
		UART_Tx("RPM default faulty\r\n");

	}

}

void Reset(){
	RPM = 0;
	PANIC = 0;
	INPUTA = 0;
	INPUTB = 0;
	INPUTC = 0;
	IGN = 1;
}

void SetIGN(){
	IGN = 0;
}

void SetRPM(){
	RPM = 1;
}

void SetPanic(){
	PANIC = 1;
}

void SetInputA(){
	INPUTA = 1;
}

void SetInputB(){
	INPUTB = 1;
}

void SetInputC(){
	INPUTC = 1;
}

void ReadDefault(){
	if (OUTPUTA == 0) UART_Tx("OutputA default faulty\r\n");
	if (TAGLED == 0) UART_Tx("Tag LED default faulty\r\n");
	if (IMMOB == 0) UART_Tx("Immob default faulty\r\n");
}

void ReadImmob(){
	if (IMMOB == 1) UART_Tx("Immob trigger faulty\r\n");
}

void ReadOutput(){
	if (OUTPUTA == 1) UART_Tx("OutputA trigger faulty\r\n");
}

void ReadLED(){
	if (TAGLED == 1) UART_Tx("Tag LED trigger faulty\r\n");
}

void txData(){
	char data = 0x52;
	char bit = 1;
	char bitCount = 8;

	while (bitCount){

		while (TAGO == 1);			//wait for clock to go low
		//usDelay(2);					//master asserts low read pulse
		//TAGI ^= 1;
		if ((data&bit) == 0){		//if bit is 0 pull down OW line
			TAGI = 1;
		}
		bit = bit << 1;				//shift bit to right
		usDelay(35);				//wait for master to read bit
		TAGI = 0;					//relaese OW line
		while (TAGO == 0);			//wait til OW line goes high
		bitCount--;
	}
	TAGI = 0;
}


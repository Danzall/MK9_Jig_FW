/*
 * board.h
 *
 *  Created on: Jun 19, 2018
 *      Author: Jeefo
 */

#include "r_cg_port.h"

#ifndef BOARD_H_
#define BOARD_H_

#define LED1 P2_bit.no1
#define LED2 P2_bit.no2
#define LED3 P2_bit.no3
#define LED4 P14_bit.no7
#define LED5 P1_bit.no0
#define LED6 P1_bit.no1

#define INPUTB P1_bit.no5
#define INPUTC P1_bit.no6
#define PANIC P1_bit.no7
#define TAGI P5_bit.no1
#define INPUTA P3_bit.no0
#define RPM P2_bit.no0
#define IGN P12_bit.no0

#define TAGO P3_bit.no1
#define OUTPUTA P12_bit.no1
#define TAGLED P12_bit.no2
#define IMMOB P13_bit.no7

#endif /* BOARD_H_ */

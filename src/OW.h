/*
 * OW.h
 *
 *  Created on: Jun 22, 2018
 *      Author: Jeefo
 */

#ifndef OW_H_
#define OW_H_

void usDelay(int time);
void ResetWait();
void Presence();
void ReadByte();
void txData();
void ProcessByte(char dataR);
void Reset();
void SetIGN();
void SetRPM();
void SetPanic();
void SetInputA();
void SetInputB();
void SetInputC();
void ReadDefault();
void ReadImmob();
void ReadOutput();
void ReadLED();

#endif /* OW_H_ */

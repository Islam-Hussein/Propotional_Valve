/*
 * ENCODER.h
 *
 * Created: 09.02.2022 09:20:00
 *  Author: student
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#include "ENC_Cfg.h"

void ENC_Init(void);

uint16 ENC_Read(void);

uint16 ENC_Read_In_Degree(void);

uint16 ENC_Deg_to_Bit(uint16 Degree);



#endif /* ENCODER_H_ */
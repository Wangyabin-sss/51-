#ifndef _iic_H
#define _iic_H

#include "delay.h"


/**********************
���ű�������
***********************/	
sbit   SCL=P0^0;			//IICʱ�����Ŷ���
sbit   SDA=P0^1;			//IIC�������Ŷ���



void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendACK(bit ack);
bit I2C_RecvACK(void);
void I2C_SendByte(u8 dat);
u8 I2C_RecvByte(bit n);  //0ack 1nack

#endif





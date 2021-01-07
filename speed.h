#ifndef _speed_H
#define _speed_H


#include "delay.h"
#include "PID.h"

extern int number[2];
/*
INT0--P32   ���������½���
INT1--P33		���������½���
INT2--P36		���½���
INT3--P37		���½���
INT4--P30		���½���
*/

#define  Ps  160.0
#define  Is  0.95


void INT_init(void);
int speed_pwm(void);
int velocity(int encoder_left,int encoder_right);


#endif



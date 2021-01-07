#ifndef _PID_H
#define _PID_H

#include "MPU6050.h"

extern bit motor_direction;

#define P 1320
#define D 38
sbit AIN1 = P2^3;
sbit AIN2 = P2^1;
sbit BIN1 = P2^5;
sbit BIN2 = P2^6;
sbit STBY = P2^4;


float Kalman_Filter(float angle_m, float gyro_m);//angleAx �� gyroGy  �������˲�
float angle_average(float a_angle); //ƽ��ֵ�˲�
void yijielvbo(float a_angle,float *angle,float g_speed);  //һ���˲�
float A_angle(void); //���ٶȼƼ���Ƕ�
float G_speed(void); //�����Ǽ���Ƕ�
int PID_PWM(float a_angle,float acc);//�����˲���Ƕȣ������ǽ��ٶ�
void Motor_control(int pwm,float a_angle);



#endif
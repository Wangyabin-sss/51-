#ifndef _PWM_H
#define _PWM_H


#include "stc8.h"
#include "GPIO.h"

#define PWM_Pin_1 P20  //��ʱ�����PWM���Ŷ��壬�޸ĺ�Ҫ��ʼ����Ӧ����Ϊ�����������Timer_PWM_init�
#define PWM_Pin_2 P27


/*---------�Ƚ�ֵ--------------*/
extern int occ;//��ʱ��0���PWM
extern int val0,val1;//15λ��ǿ��PWM����Ӧ����ΪP20,P21


void Timer_PWM_init(void);//��ʱ��PWM��ʼ��
void PWM_init(void);//15λPWM��ʼ��


#endif


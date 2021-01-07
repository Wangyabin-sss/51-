#include "PWM.h"

 /*-------��ʱ��PWM���ֵ-------*/
int time;
int occ;
int time_occ;
/*-------15λӲ��PWM���ֵ---------*/
int val0,val1;

void Timer_PWM_init()
{
	TMOD = 0x00;
	TL0 = 0xec;//������ֵ=65536-24Mhz/12��Ƶ/(100000)hz=65516
	TH0 = 0xff;
	TR0 = 1;//������ʱ��0
	ET0 = 1;//ʹ�ܶ�ʱ���ж�
	EA = 1;
}

void TM0_Isr() interrupt 1
{
	time+=1;
	if(time==1000)//0.01ms����һ�Σ�����1000�Σ�Ƶ��Ϊ100hz
	{
		time=0;
		if(occ>0)  //��occ��ֵ��Ϊ��ֵ
		{
			time_occ=occ;
		}
		else
		{
			time_occ=-occ;
		}
	}
	if(time<=time_occ)//ռ�ձ�=occ/1000%
	{
		PWM_Pin_1=1;
		PWM_Pin_2=1;
	}
	else
	{
		PWM_Pin_1=0;
		PWM_Pin_2=0;
	}
}


void PWM_init()
{
	P_SW2 = 0x80;  
	PWMCKS = 0x0f;  //ѡ�������ʱ��Ϊ�ⲿʱ��16��Ƶ
	PWMC = 0x4e20;  //����15λpwm����������ֵΪ20000
	
	PWM0T1= 0x0000; //������ֵ����T1ʱ����תΪ�͵�ƽ��T1=T2ʱ����T2��
	PWM0T2= 0x0000; //������ֵ����T2ʱ����תΪ�ߵ�ƽ��T1=T2ʱ����T2��
	PWM0CR= 0x80;   //PWM��ʼ��ƽΪ�ͣ��������ΪP20
	
	PWM7T1= 0x0000; //������ֵ����T1ʱ����תΪ�͵�ƽ��T1=T2ʱ����T2��
	PWM7T2= 0x0000; //������ֵ����T2ʱ����תΪ�ߵ�ƽ��T1=T2ʱ����T2��
	PWM7CR= 0x80;   //PWM��ʼ��ƽΪ�ͣ��������ΪP27
	
	P_SW2 = 0x00;   
	PWMCR = 0xc0;   //ʹ��PWM���η�������PWM������������ʼ����
	EA=1;
	
}

void PWM_Isr() interrupt 22
{
	if (PWMCFG & 0x80) 
	{	
		PWMCFG &= ~0x80; //���жϱ�־λ
		_push_(P_SW2);
		P_SW2 |= 0x80;
		
		if(val0>=0)  //val6ȡ����ֵ
		{
			PWM0T1 = val0;
		}
		else
		{
			PWM0T1 = -val0;
		}
		
		if(val1>=0)  //val7ȡ����ֵ
		{
			PWM7T1 = val1;
		}
		else
		{
			PWM7T1 = -val1;
		}
		
		_pop_(P_SW2);
	}
}







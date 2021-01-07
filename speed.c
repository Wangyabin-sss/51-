#include "speed.h"

int number[2]={0,0};

void INT_init()
{
	IT0 = 0;//ʹ�� INT0 �����غ��½����ж�
	EX0 = 1;//ʹ�� INT0 �ж�
	
	IT1 = 0;//ʹ�� INT1 �����غ��½����ж�
	EX1 = 1;//ʹ�� INT1 �ж�
	
//	INTCLKO = EX2;//ʹ�� INT2 �½����ж�
//	
//	INTCLKO |= EX3;//ʹ�� INT3 �½����ж�
	
	EA = 1;
	
}


void INT0_Isr() interrupt 0  //INT0--P32���1-A��
{
	
		if(motor_direction==1)
		{
			number[0]+=1;
		}
		else
		{
			number[0]-=1;
		}
	
}

void INT1_Isr() interrupt 2  //INT1--P33���2-A��
{

		if(motor_direction==1)
		{
			number[1]+=1;
		}
		else
		{
			number[1]-=1;
		}
		
}

//void INT2_Isr() interrupt 10  //INT2--P36���1-B��
//{
////		if(P32==1)
////		{
//			number[0]+=1;
////		}
////		else
////		{
////			number[0]-=1;
////		}
////		
//}

//void INT3_Isr() interrupt 11  //INT3--P37���2-B��
//{
////		if(P33==0)
////		{
//			number[1]+=1;
////		}
////		else
////		{
////			number[1]-=1;
////		}
////		
//}

int speed_pwm()
{
	static float speed=0,position=0,spwm=0;
	static float speed_r=0;
	
	speed_r =(float)(number[0] + number[1])*0.8;
	number[0] = number[1] = 0;
	speed *= 0.8;	    		 //��һ�ε�     //�����ٶ��˲�
	speed += speed_r*0.4;
	position += speed;               //���ֵõ�λ��
	
	if(position>3500)  position=3500;          //===�����޷�
	if(position<-3500)	position=-3500;         //===�����޷�
	
	spwm = Is*position + Ps*speed;   //PID���ٶȺ�λ��
	
	return spwm;

	
}


int velocity(int Encoder_Left,int Encoder_Right)
{  
	static float Velocity,Encoder_Least,Encoder,Movement;
	static float Encoder_Integral;
	float kp=8,ki=0.04;
	//=============�ٶ�PI������=======================//	
	Encoder_Least =(Encoder_Left+Encoder_Right)-0;  //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
	Encoder *= 0.7;		                         //===һ�׵�ͨ�˲���       
	Encoder += Encoder_Least*0.3;	             //===һ�׵�ͨ�˲���    
	Encoder_Integral +=Encoder;                                     //===���ֳ�λ�� ����ʱ�䣺10ms
	Encoder_Integral=Encoder_Integral-Movement;                     //===����ң�������ݣ�����ǰ������
	if(Encoder_Integral>10000)  	Encoder_Integral=10000;          //===�����޷�
	if(Encoder_Integral<-10000)	Encoder_Integral=-10000;         //===�����޷�	
	Velocity=Encoder*kp+Encoder_Integral*ki; //===�ٶȿ���	

	return Velocity;
}



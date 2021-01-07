#include "uart.h"

void Uart1_Init(void) //ʹ�ö�ʱ��2�������ʷ�����
{		
	GPIO_init(GPIO_P3,GPIO_Pin_0,GPIO_PullUp);//����P3.0Ϊ׼˫���
	GPIO_init(GPIO_P3,GPIO_Pin_1,GPIO_OUT_PP);//����P3.1Ϊ�������
	
	SCON = 0x50;
	T2L = 0xcc;		//115200
	T2H = 0xff;
	AUXR = 0x15;		//������ʱ��2
	ES = 1;				//ʹ�ܴ����ж�
	EA = 1;
}

void U1SendData(u8 ch)
{
		
    SBUF = ch;                  //д���ݵ�UART���ݼĴ���
		while(TI == 0);             //��ֹͣλû�з���ʱ��TIΪ0��һֱ�ȴ�
		TI = 0;  	//���TIλ����λ����������㣩
		
}

void UartSendStr(u8 *p)
{
	while (*p)
	{
		U1SendData(*p++);
	}
}

void UART1_Isr() interrupt 4
{
	if (TI)
	{
		TI = 0;//���жϱ�־
	}
	if (RI)
	{
		RI = 0;//���жϱ�־
	}
}


char putchar(char c)
{
	ES=0;
	U1SendData(c);
	ES=1;
	return c;
}
	
























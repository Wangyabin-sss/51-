#include "uart.h"
#include "MPU6050.h"
#include "PID.h"
#include "GPIO.h"
#include "PWM.h"
#include "OLED.h"
#include "speed.h"

/*------------��ʹ�õ�Ӳ����Դ--�����ظ�ʹ��-----------

��ʱ��0�ж���PWM������
��ʱ��1�ж���OLED��ʾ
��ʱ��2�������ʷ�����
�ⲿ�ж�P32��P33��P36��P37������������

���ţ�IIC--SCL=P00��SDA=P01
			��ʱ��PWM--P04 Ӳ��PWM--P20��P21
			�����������--AIN1 = P2^3;
										AIN2 = P2^1;
										BIN1 = P2^5;
										BIN2 = P2^6;
										STBY = P2^4;
										
			OLED����--OLED_CS=P0^3; //Ƭѡ
								OLED_RST =P0^5;//��λ
								OLED_DC =P0^4;//����/�������
								OLED_SCL=P0^7;//ʱ�� D0��SCLK)
								OLED_SDIN=P0^6;//D1��MOSI�� ����
*/


void Systeminit(void)
{
	P_SW2 = 0x80;
  XOSCCR = 0xc0;			//�����ⲿ����
  while (!(XOSCCR & 1));//�ȴ�ʱ���ȶ�
  CLKDIV = 0x00;			//ʱ�Ӳ���Ƶ
  CKSEL = 0x01;			//ѡ���ⲿ����
  P_SW2 = 0x00;
}



void main()
{
	int PWM=0;
	float angle=0,a_angle=0,g_speed=0;

	Systeminit();  //ʹ���ⲿ����
	delay_ms(10);
//	P2M0 = 0xff;//���� P2.0~P2.7 Ϊ�������ģʽ
//  P2M1 = 0x00;
//	P0M0 = 0xff;//���� P0.0~P0.7 Ϊ�������ģʽ
//  P0M1 = 0x00;
	
//	OLED_Init();  //OLED��ʼ��
	delay_ms(10);
	InitMPU6050(); //mpu6050��ʼ��
	delay_ms(10);
	Uart1_Init();  //���ڳ�ʼ��
	delay_ms(10);
//	Timer_PWM_init();
	PWM_init();   //Ӳ��PWM��ʼ��
	delay_ms(10);
	INT_init();
	delay_ms(10);

	
	while(1)
	{	P55=0;
		
		a_angle=-A_angle();
		g_speed=G_speed();
		angle=Kalman_Filter(a_angle,g_speed)-0.78;
//		angle=angle_average(a_angle);
//		yijielvbo(a_angle,&angle,g_speed);
		
//		printf("%f��%f��%f\n",angle,a_angle,g_speed);
		
//		PWM=PID_PWM(angle,g_speed);
		PWM=PID_PWM(angle,g_speed)+speed_pwm();  //pid_pwm������ speed_pwmҲҪ������
//		PWM=speed_pwm();
//		PWM=PID_PWM(angle,g_speed)+velocity(number[0],number[1]);
//		PWM=velocity(number[0],number[1]);
		
//		occ=PWM;
		val1=val0=PWM;
		
		Motor_control(PWM,angle);
		
		delay_ms(8);
		
	}
	
	
}








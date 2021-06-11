#include<reg51.h>

sbit LSA=P2^2;//����LSAΪP2�ڵĵڶ�λ
sbit LSB=P2^3;//����LSAΪP2�ڵĵ���λ
sbit LSC=P2^4;//����LSAΪP2�ڵĵ���λ

unsigned char count = 0;

unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��¼LED��ʾ����
unsigned char RECORD[8] = {0,0,0,0,0,0,0,0};//��¼λ����ʾ
void init(void);
void counter(void);
void delay(void);

int main(void)
{
	init();
	while (1) {
		counter();
	};
}

//��ʼ��
void init(void)
{
	 EX0 = 0X01;
	 EA = 0X01;
	 IT0 = 0x01;
}

//��ʾ
void display(unsigned char index)
{
	switch(index)
	{
		case(0):LSA=0;LSB=0;LSC=0; break;
		case(1):LSA=1;LSB=0;LSC=0; break;
		case(2):LSA=0;LSB=1;LSC=0; break;
		case(3):LSA=1;LSB=1;LSC=0; break;
		case(4):LSA=0;LSB=0;LSC=1; break;
		case(5):LSA=1;LSB=0;LSC=1; break;
		case(6):LSA=0;LSB=1;LSC=1; break;
		case(7):LSA=1;LSB=1;LSC=1; break;
	}

}

//��ʱ
void counter(void)
{
	unsigned char tmp = count;
	unsigned char index = 0;
	unsigned char i = 0;
	while(tmp != 0) {
		RECORD[index] = DIG_CODE[tmp % 10];
		tmp /= 10;
		index ++;
	}
	for (i = index; i > 0; i --) {
		display(i-index);
		P0=RECORD[i-index];
	}
}

//�ӳ�
void delay(void)
{
	unsigned char a = 0;
	unsigned char b = 0;
	for (a = 0; a < 100; a++)
		for (b = 0; b < 100; b++);
}

//�����ť
void PressKey(void) interrupt 1 using 0
{

	delay();
	count ++;
}


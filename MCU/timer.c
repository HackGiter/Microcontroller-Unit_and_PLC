#include<reg51.h>

#define GPIO_KEY P1

sbit LSA=P2^2;//定义LSA为P2口的第二位
sbit LSB=P2^3;
sbit LSC=P2^4;


unsigned int count = 0;
unsigned int count1 = 0;
unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
unsigned char RECORD[8] = {
0,0,0,0,0,0,0,0};


void time_init(void);
void counter(void);
void display(unsigned char index);
void delay(void);

int main(void)
{
	 time_init();
	 while(1) {
	 	 counter();
	 };

}

void time_init(void)
{
	TCON = 0X00;
	EA = 1; //打开总中断
	TMOD |= 0x01;
	TH0 = (65536-50000) / 256;
	TL0 = (65536-50000) % 256;
	ET0 = 1;	//打开定时器0中断允许
	TR0 = 1;	//定时器0开始计时


}

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

void counter(void)
{
	unsigned int tmp = count1;
	unsigned char index = 0;
	unsigned char i = 0;
	while(tmp != 0) {
		RECORD[index] = DIG_CODE[tmp % 10];
		tmp /= 10;
		index ++;
	}
	for (i = index; i > 0; i --) {
		P0=RECORD[index-i];
		display(index-i);
		delay();
		
	}
}

void delay(void)
{
	unsigned char a = 0;
	unsigned char b = 0;
	for (a = 0; a < 50; a++)
		for (b = 0; b < 100; b++);
}

void timer(void) interrupt 1
{
	TR0 = 0X00;
	ET0 = 0X00;
	count ++;
	if (count==500) {
		count = 0;
	}
	if (count % 10 == 1) {
		count1 ++;
	}
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	TR0 = 0X01;
	ET0 = 0X01;


}

#include<reg52.h>

sbit P34 = P3^4;
sbit P36 = P3^6;
sbit P35 = P3^5;

unsigned char index;
unsigned char index1;
unsigned char cycle;
unsigned char line;
unsigned char colume;

unsigned char code B2T[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char code SEVEN[8] = {0X00,0X80,0X80,0X8F,0X90,0XA0,0XC0,0X00}; // �洢���ֵı���
unsigned char code DEN[8] = {0X61,0XFE,0X14,0X63,0X44,0X42,0X7F,0X40};	 // �洢�ַ��ı���
unsigned char code GRAPH2[8] = {0X8F,0XC2,0XA4,0X98,0X19,0X25,0X43,0XF1};// �洢ͼƬ2�ı���
														  
void delay(void);
void sdelay(void);
void nop(void);
void L2R2L_B2T2B(void);
void showNumber(void);
void scanLine(unsigned char line1);
void showCharacter(void);
void showGraph(void);

int main ()
{

	P36 = 0;
	P35 = 0;
	
	while (1) 
	{
		 L2R2L_B2T2B();
		 delay();
		 showNumber();
		 delay();
		 showCharacter();
		 delay();
		 showGraph();
		 delay();
	}
	return 0;
}

// ��ʱ��ʾ
void delay(void)
{
	unsigned char out, in;

	for (out=0;out<150;out++)
		for (in=0;in<150;in++);
}

void sdelay(void)
{
	unsigned char out, in;

	for (out=0;out<50;out++)
		for (in=0;in<50;in++);	
}

// �ղ���
void nop(void)
{
	unsigned char out, in;

	for (out=0;out<2;out++)
		for (in=0;in<1;in++);
}

// LED������ʾ
void L2R2L_B2T2B(void) 
{
		P0 = 0XFF;		

		for (cycle = 0; cycle < 6; cycle ++) {
			
			if (cycle < 3) {
				colume = 0X7F;
			} else {
				colume = 0XFE;
			}
			
			for (index = 0; index < 8; index ++) {
				P0 = colume;
		
				P34 = 0XFF;
				P36 = 1;
				P36 = 0;
				P35 = 1;

				if (cycle < 3) {
					colume >>= 1;
					colume += 0X80;
				} else {
					colume <<= 1;
					colume += 1;	
				}
				P35 = 0;
				
				delay();
			}
		}
		
		for (cycle = 0; cycle < 6; cycle ++) {		
			for (index = 0; index < 8; index ++) {
				P0 = 0X00;
				if (cycle < 3) {
					line = B2T[7 - index];
				} else {
					line = B2T[index];
				}
				scanLine(line);
				delay();
				scanLine(0x00);
				
			}
		}
		
		delay();
}
// ��ɨ��
void scanLine(unsigned char line1) {
	P36 = 0;
	P35 = 0;
	for	(index1 = 0; index1 < 8; index1 ++) {
		P34 = line1 >> 7;
		line1 <<= 1;
		P36 = 1;
		nop();
		P36 = 0;
	}
	P35 = 1;
	P35 = 0;	
}
//LED������ʾ����
void showNumber(void)
{
		P0 = 0XFF;		

		for (cycle = 0; cycle < 10; cycle ++) {
			
			colume = 0X7F;
			
			for (index = 0; index < 8; index ++) {
				P0 = colume;
				scanLine(SEVEN[index]);
				sdelay();
				//scanLine(0x00);
				colume >>= 1;
				colume += 0X80;
			}
		}	
}
// LED������ʾ�ַ�
void showCharacter(void)
{
		P0 = 0XFF;		
		for (cycle = 0; cycle < 10; cycle ++) {		
			colume = 0X7F;			
			for (index = 0; index < 8; index ++) {
				P0 = colume;
				scanLine(DEN[index]);
				sdelay();
				colume >>= 1;
				colume += 0X80;
			}
		}
}
// LED������ʾͼ��
void showGraph(void)
{
		P0 = 0XFF;		
		for (cycle = 0; cycle < 10; cycle ++) {		
			colume = 0X7F;			
			for (index = 0; index < 8; index ++) {
				P0 = colume;
				scanLine(GRAPH2[index]);
				sdelay();
				colume >>= 1;
				colume += 0X80;
			}
		}
}

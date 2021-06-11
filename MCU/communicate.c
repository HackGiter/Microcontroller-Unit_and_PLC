#include<reg51.h>

unsigned char XUEHAO1[10];
unsigned char flag = 0;
unsigned char IND=0;

int main()
{
	IND=0;
	
	TMOD = 0X20;
	TH1 = 0XF3;
	TL1 = 0XF3;
	
	SCON = 0X50;
	PCON = 0x80;

	EA = 1;
	ES = 1;
	TR1 = 1;

	while(1);

	return 0;
}

void RecieveAndSend() interrupt 4
{
	if (RI==1) {
		XUEHAO1[IND]=SBUF;
		IND+=1;
		RI=0;
	}

	if (IND==10) {
		flag = 1 - flag;
		IND = 0;
	}

	if (flag == 1) {
		SBUF=XUEHAO1[IND];
		IND+=1;
		TI=0;
	}
}

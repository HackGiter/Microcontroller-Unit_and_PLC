#include <reg52.h>
sbit BUZZ = P1^5; //��������������

unsigned int t;
unsigned char t_H,t_L;
unsigned char n=0;  //nΪ���ĳ�������    

code unsigned int toneH[10]={     //������Ӧ�Ķ�ʱ������ֵ�ĸ�8λ ��һ����Ϊ����7
0XF8,0XF8,0XF9,0XFA,0XFA,0XFB,0XFB,0XFC,0XFC,0XFC//
};
code unsigned int toneL[10]={     //������Ӧ�Ķ�ʱ������ֵ�ĵ�8λ
0X18,0X8C,0X6B,0X15,0X67,0X04,0X90,0X0C,0X44,0XAC
};

code unsigned int soundtone[42]={
1,1,5,5,6,6,5,4,4,3,3,2,2,1,
5,5,4,4,3,3,2,5,5,4,4,3,3,2,
1,1,5,5,6,6,5,4,4,3,3,2,2,1
};

code unsigned int soundlong[42]={
1,1,1,1,1,1,2,1,1,1,1,1,1,2,
1,1,1,1,1,1,2,1,1,1,1,1,1,2,
1,1,1,1,1,1,2,1,1,1,1,1,1,2
};

code unsigned int easytone[28]={
1,2,3,1,5,6,6,8,6,5,6,6,8,
5,6,5,6,5,3,5,3,1,2,3,1
};

code unsigned int easylong[28]={
1,1,1,1,2,1,1,1,1,2,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,2
};

void init_T0(void)
{
	TMOD|= 0x01;	  //ʹ�÷�ʽ1��16λ��ʱ��		     
	TH0=0x00;	      //��TH0��TL0����ֵ����������0��ʼ��������65535���
	TL0=0x00;
	EA=1;            //���жϴ�
	ET0=1;           //��ʱ���жϴ�
	TR0=0;           //�رն�ʱ��
}

void delay1ms(unsigned int x)
{
	unsigned int i,j;
	for(j=0;j<x;j++)
		for(i=0;i<123;i++);
}

void main(void) 
{
    init_T0();  
    for(;;) 
    {
        for(t=0;t<28;t++) 
        {
            t_H=toneH[easytone[t]];     //��ȡ������Ӧ�Ķ�ʱ����ʼֵ
            t_L=toneL[easytone[t]];
        	TH0=t_H;		  //��TH0��TL0��ֵ
        	TL0=t_L;
            TR0=1;              //�򿪶�ʱ��������������
            delay1ms(easylong[t]*300);    //��ʱsoundlong[t]ָ����ʱ�䳤��
            BUZZ=0;             //��������������ͣ��Ƭ��
            TR0=0;
            delay1ms(50);
        }
        delay1ms(2000);
     } 

     
}

void T0_ISR(void) interrupt 1 using 1
{
	TH0=t_H;		  //��TH0��TL0���¸�ֵ
	TL0=t_L;
	BUZZ=~BUZZ;      //BUZZ��ֵȡ�����ı��������״̬��
}


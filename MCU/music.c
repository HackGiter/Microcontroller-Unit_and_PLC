#include <reg52.h>
sbit BUZZ = P1^5; //蜂鸣器控制引脚

unsigned int t;
unsigned char t_H,t_L;
unsigned char n=0;  //n为节拍常数变量    

code unsigned int toneH[10]={     //音调对应的定时器计数值的高8位 第一个音为低音7
0XF8,0XF8,0XF9,0XFA,0XFA,0XFB,0XFB,0XFC,0XFC,0XFC//
};
code unsigned int toneL[10]={     //音调对应的定时器计数值的低8位
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
	TMOD|= 0x01;	  //使用方式1，16位定时器		     
	TH0=0x00;	      //给TH0和TL0赋初值，计数器由0开始计数，到65535溢出
	TL0=0x00;
	EA=1;            //总中断打开
	ET0=1;           //定时器中断打开
	TR0=0;           //关闭定时器
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
            t_H=toneH[easytone[t]];     //提取音调对应的定时器初始值
            t_L=toneL[easytone[t]];
        	TH0=t_H;		  //给TH0和TL0赋值
        	TL0=t_L;
            TR0=1;              //打开定时器，蜂鸣器发声
            delay1ms(easylong[t]*300);    //延时soundlong[t]指定的时间长度
            BUZZ=0;             //蜂鸣器不发声，停顿片刻
            TR0=0;
            delay1ms(50);
        }
        delay1ms(2000);
     } 

     
}

void T0_ISR(void) interrupt 1 using 1
{
	TH0=t_H;		  //给TH0和TL0重新赋值
	TL0=t_L;
	BUZZ=~BUZZ;      //BUZZ的值取反，改变蜂鸣器的状态。
}


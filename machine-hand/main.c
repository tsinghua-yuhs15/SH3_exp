
#include "includes.h"

unsigned long gFLAG;
unsigned long tFLAG;
char STATE;
short mode;
int control;
int *CTL;
// #define xyz (*(volatile int *)0x0c300000) 
// #define sum (*(volatile int *)0x0c300004) 



void delay_mms(long ms){
//	init_timer();
	tFLAG=ms;
	while(tFLAG>0){}
//	TMU.TSTR.BYTE &= 0x00;	
}

void main()
{
	int ctl[6]={30,30,30,30,30,30};
	int angle[6]={-135,-90,-45,0,45,90};

	CTL=ctl;
	control=-1;
	STATE=0;
	init_timer();
	tFLAG=0;
	init_PWM();
	init_state();
	LED_DATA=0x00;
	delay_mms(10000);
	LED_DATA=0x34;
	mode=5;
	init_timer();
	while(1){
		PWM_ctl(ctl);
	}

	while(1){
	switch(mode){
	case(0):
	LED_DATA=0xff;
	PWM_work();
	LED_DATA=0x00;
	break;
	case(1):
	LED_DATA=0x00;
	PWM_ctl(angle);
	break;
	}
	}


	sleep();		// 用于独立HEW3环境调试，针对“PC指针 = 当前执行指令 + 2”的问题
//	sleep();		// 同上
//	sleep();		// 同上

//	for(;;){}		// 循环
}

void init_timer()
{

   TMU.TSTR.BYTE  = 0x00;                // 在操作前停步计数
   TMU0.TCOR = (PCLK/256/20000) - 1;		// 设置比较寄存器      
   TMU0.TCNT = (PCLK/256/20000) - 1;  		//  
                                		// 每秒5次
   TMU0.TCR.WORD  = 0x0023;             // 中断使能
      
	  
	                            		// 时钟源= PCLK/256
   TMU1.TCOR = (PCLK/4/100) - 1;		// 设置比较寄存器      
   TMU1.TCNT = (PCLK/4/100) - 1; 

   TMU1.TCR.WORD  = 0x0020;



   TMU2.TCR.WORD  = 0x0000;

   TMU.TSTR.BYTE |= 0x03;						


}

void init_state(){
	PFC.PDCR.BIT.PD0MD = 0x01;
	PFC.PDCR.BIT.PD1MD = 0x01;
	PFC.PDCR.BIT.PD2MD = 0x01;
	PFC.PDCR.BIT.PD3MD = 0x01;
}

void state(){
	switch(STATE){
		case(0): 
			PD.DR.BIT.B0 = 0;
			PD.DR.BIT.B1 = 1;
			PD.DR.BIT.B2 = 1;
			PD.DR.BIT.B3 = 1;
			break;
		case(1):
			PD.DR.BIT.B0 = 1;
			PD.DR.BIT.B1 = 0;
			PD.DR.BIT.B2 = 1;
			PD.DR.BIT.B3 = 1;
			break;
		case(2):
			PD.DR.BIT.B0 = 1;
			PD.DR.BIT.B1 = 1;
			PD.DR.BIT.B2 = 0;
			PD.DR.BIT.B3 = 1;
			break;
		case(3):
			PD.DR.BIT.B0 = 1;
			PD.DR.BIT.B1 = 1;
			PD.DR.BIT.B2 = 1;
			PD.DR.BIT.B3 = 0;
			break;
	}
}

void TMU0_ISR()
{
	TMU0.TCR.WORD = 0x0023;				// 清中断标志
	tFLAG--;
}

void TMU1_ISR()
{
	TMU1.TCR.WORD = 0x0020;	
	//LED_DATA=STATE;
	STATE=(STATE+1)%4;
	state();
}
void NMI_ISR()
{
	mode=11-mode;
}

void IRQ0_ISR()
{
	INTX.IRR0.BIT.IRQ0R = 0;
	LED_DATA=STATE;
	switch(STATE){
		case(0)://key1
		key_1();
		break;
		case(1):
		key_4();
		break;
		case(2):
		key_7();
		break;
		case(3):
		key_star();
		break;
	}
}
void IRQ1_ISR()
{
	INTX.IRR0.BIT.IRQ1R = 0;
	LED_DATA=STATE;
	switch(STATE){
		case(0)://key1
		key_2();
		break;
		case(1):
		key_5();
		break;
		case(2):
		key_8();
		break;
		case(3):
		key_0();
		break;
	}
}

void IRQ2_ISR()
{
	INTX.IRR0.BIT.IRQ2R = 0;
	LED_DATA=STATE;
	switch(STATE){
		case(0)://key1
		key_3();
		break;
		case(1):
		key_6();
		break;
		case(2):
		key_9();
		break;
		case(3):
		key_sharp();
		break;
	}
}

void IRQ3_ISR()
{
	INTX.IRR0.BIT.IRQ3R = 0;
	LED_DATA=STATE;
	switch(STATE){
		case(0)://key1
		key_A(CTL);
		break;
		case(1):
		key_B(CTL);
		break;
		case(2):
		key_C(CTL);
		break;
		case(3):
		key_D(CTL);
		break;
	};
}

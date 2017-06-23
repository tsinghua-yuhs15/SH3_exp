
#include "includes.h"

void init_PWM(){
	init_timer();
	PFC.PECR.BIT.PE0MD = 0x01;
	PFC.PECR.BIT.PE1MD = 0x01;
	PFC.PECR.BIT.PE2MD = 0x01;
	PFC.PECR.BIT.PE3MD = 0x01;
	PFC.PECR.BIT.PE4MD = 0x01;
	PFC.PECR.BIT.PE5MD = 0x01;
	PWM_resetall();
}

void PWM_resetall(){
	PE.DR.BIT.B0 = 0;
	PE.DR.BIT.B1 = 0;
	PE.DR.BIT.B2 = 0;
	PE.DR.BIT.B3 = 0;
	PE.DR.BIT.B4 = 0;
	PE.DR.BIT.B5 = 0;
}

void PWM_work(){
	int i;
	PWM_resetall();
	LED_DATA=0x15;
	//0-M control
	PE.DR.BIT.B0 = 1;
	delay_mms(15);
	PE.DR.BIT.B0 = 0;
	delay_mms(10);
	//1-M control
	PE.DR.BIT.B1 = 1;
	delay_mms(15);
	PE.DR.BIT.B1 = 0;
	delay_mms(10);
	//2-M control
	PE.DR.BIT.B2 = 1;
	delay_mms(15);
	PE.DR.BIT.B2 = 0;
	delay_mms(10);
	//3-M control
	PE.DR.BIT.B3 = 1;
	delay_mms(15);
	PE.DR.BIT.B3 = 0;
	delay_mms(10);
	//4-M control
	PE.DR.BIT.B4 = 1;
	delay_mms(15);
	PE.DR.BIT.B4 = 0;
	delay_mms(10);
	//5-M control
	PE.DR.BIT.B5 = 1;
	delay_mms(15);
	PE.DR.BIT.B5 = 0;
	delay_mms(10);
	delay_mms(50);
}

void PWM_ctl(int* args){
	//0-M control
	PE.DR.BIT.B0 = 1;
	delay_mms(args[0]);
	PE.DR.BIT.B0 = 0;
	delay_mms(50-args[0]);
	//1-M control
	PE.DR.BIT.B1 = 1;
	delay_mms(args[1]);
	PE.DR.BIT.B1 = 0;
	delay_mms(50-args[1]);
	//2-M control
	PE.DR.BIT.B2 = 1;
	delay_mms(args[2]);
	PE.DR.BIT.B2 = 0;
	delay_mms(50-args[2]);
	//3-M control
	PE.DR.BIT.B3 = 1;
	delay_mms(args[3]);
	PE.DR.BIT.B3 = 0;
	delay_mms(50-args[3]);
	//4-M control
	PE.DR.BIT.B4 = 1;
	delay_mms(args[4]);
	PE.DR.BIT.B4 = 0;
	delay_mms(50-args[4]);
	//5-M control
	PE.DR.BIT.B5 = 1;
	delay_mms(args[5]);
	PE.DR.BIT.B5 = 0;
	delay_mms(50-args[5]);
	delay_mms(100);
}

void PWM_test(int mode){
	int ctl[6]={30,30,30,30,30,30};
	if(mode==5){
		PWM_ctl(ctl);
	}
	else
		return;
}

void angle_to_args(int *para){
	int i;
	for(i=0;i<6;i++){
		para[i]=(para[i]+135)*200/270+5;
	}
	return;
}
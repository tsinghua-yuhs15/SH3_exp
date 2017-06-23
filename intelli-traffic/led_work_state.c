#include "includes.h"
void LED_init(){
	PFC.PJCR.BIT.PJ5MD = 0x01; // 交通灯显示控制端口
	PFC.PECR.BIT.PE1MD = 0x01; // 绿灯显示端口
	PFC.PECR.BIT.PE3MD = 0x01; // 黄灯显示端口
	PFC.PECR.BIT.PE4MD = 0x01; // 红灯显示端口
	PJ.DR.BIT.B5 = 0;
}
void LED_reset(){
	PE.DR.BIT.B1 = 0;
	PE.DR.BIT.B3 = 0;
	PE.DR.BIT.B4 = 0;
}
void light_LED(int i){
	PFC.PJCR.BIT.PJ5MD = 0x01;
	LED_reset();
	switch(i){
	case 0:PE.DR.BIT.B1 = 1;//green
	break;
	case 1:PE.DR.BIT.B3 = 1;//yellow
	break;
	case 2:PE.DR.BIT.B4 = 1;//red
	break;
	}
	return;
}
void light_all_LED(){
	PE.DR.BIT.B1 = 1;
	PE.DR.BIT.B3 = 1;
	PE.DR.BIT.B4 = 1;
}
void led_test(){
int i;
	while(1){
		light_LED(0);
		for(i = 0; i < 6400000; i++)
		{
		}
		light_LED(1);
		for(i = 0; i < 6400000; i++)
		{
		}
		light_LED(2);
		for(i = 0; i < 6400000; i++)
		{
		}
	}
}
void LED_day_mode(){
	int i,j;
	LED_reset();
	light_LED(0);
	delay_ms(5000);
	for(i=0;i<4;i++){
		light_LED(1);
		delay_ms(400);
		LED_reset();
		delay_ms(400);
	}
	light_LED(2);
	delay_ms(5000);
}
//night mode
void LED_night_mode(){
	LED_reset();
	light_LED(0);
}
//night to day mode
void LED_night_to_day_mode(){
	DAC.DADR0=0xFF;
	LED_day_mode();
	mode=1;
}
//remote mode
void LED_remote_mode(){
	int j;
	digit_reset();
	light_digit(9,1);
	for(j=0;j<1000;j++){
	}
	light_digit(9,2);
	for(j=0;j<1000;j++){
	}
}
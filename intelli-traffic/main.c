
#include "includes.h"
#define MAX_LIGHT 0x80

unsigned long gFLAG;
unsigned long tFLAG;
int mode;
int wd_flag;
int break_flag;
int set_para;
int light;
char *p;
char *gpchar;
// #define xyz (*(volatile int *)0x0c300000) 
// #define sum (*(volatile int *)0x0c300004) 

void AD_DA_init(){
	ADC.ADCSR.BIT.ADST = 0; //AD关闭
	ADC.ADCSR.BIT.ADIE = 0; //中断允许/关闭
	ADC.ADCSR.BIT.MULTI = 0; //采集模式选择
	ADC.ADCSR.BIT.CKS = 1; //转换时间设置
	ADC.ADCSR.BIT.CH = 0; //通道选择

	DAC.DACR.BIT.DAOE0 = 1; // 通道0使能
	DAC.DACR.BIT.DAE = 1; // 通道0&1使能
}
void sensor_init(){
	PFC.PECR.BIT.PE6MD = 0x03;
}

void digit_init(){
	PFC.PJCR.BIT.PJ1MD = 0x01; // 数码管个位显示控制端口
	PFC.PJCR.BIT.PJ4MD = 0x01; // 数码管十位显示控制端口
	PFC.PCCR.WORD = 0x5555; // 数码管显示数据端口
}
void delay_ms(long ms){
	init_timer();
	tFLAG=ms;
	while(tFLAG>0){}
	TMU.TSTR.BYTE &= 0x00;
	
}

void digit_reset(){
	PJ.DR.BIT.B1 = 1; 
	PJ.DR.BIT.B4 = 1; 
}


void light_digit(int number,int position){
	switch(number) {
	case 0: PC.DR.BYTE = 0x3F; break;
	case 1: PC.DR.BYTE = 0x06; break;
	case 2: PC.DR.BYTE = 0x5B; break;
	case 3: PC.DR.BYTE = 0x4F; break;
	case 4: PC.DR.BYTE = 0x66; break;
	case 5: PC.DR.BYTE = 0x6D; break;
	case 6: PC.DR.BYTE = 0x7D; break;
	case 7: PC.DR.BYTE = 0x07; break;
	case 8: PC.DR.BYTE = 0x7F; break;
	case 9: PC.DR.BYTE = 0x6F; break;
	default: PC.DR.BYTE = 0x00; break;
	}
	switch(position) {
	case 1: PJ.DR.BIT.B1 = 1; // 显示个位
			PJ.DR.BIT.B4 = 0;
			break;
	case 2: PJ.DR.BIT.B1 = 0;
			PJ.DR.BIT.B4 = 1; // 显示十位
			break;
	}
}
void digit_test(){
int i,j;
int count;
count=0;
	while(1){
	count=count%100;
	for(i=0;i<3200;i++){
		light_digit(count/10,1);
		for(j=0;j<1000;j++){
		}
		light_digit(count%10,2);
		for(j=0;j<1000;j++){
		}
	}
	digit_reset();
	count++;
	}
}
void test_breakdown(){
	int j;
	light_all_LED();
	light_digit(8,1);
	for(j=0;j<1000;j++){
	}
	light_digit(8,2);
	for(j=0;j<1000;j++){
	}
}
//daylight mode


//light_sensor_AD_SHOW_TEST
int get_AD_data(){
	int gADData;
	ADC.ADCSR.BIT.ADST = 1; // 启动AD采集
	while(ADC.ADCSR.BIT.ADF == 0) {} // 判断AD采集完成标志
	gADData = ADC.ADDRAH; // 从ADC.ADDRAH, ADC.ADDRAL取值运算
	ADC.ADCSR.BIT.ADF = 0; // 重置AD采集完成标志
	LED_DATA = gADData;
	return gADData;
}
void traffic_light_NMI_demo(){
	while(1){
		switch(mode){
		case 0://day
			LED_day_mode();
			break;
		case 1://night
			LED_night_mode();
			break;
		case 2://night to day for a cycle
			LED_night_to_day_mode();
		}
	}
}
void send_char(char x);
void send_str(char *s,int len);
void traffic_light_sensor_demo(){
	int light;
	//break_flag=0;
	break_flag=1;
	LED_reset();
	digit_reset();
	while(1){
		
		light=get_AD_data();
		//if(light>MAX_LIGHT){
		//	mode=1;
		//}
		//else if(mode!=2){
		//	mode=0;
		//}

		//
	//	if(break_flag==0){
	//		mode=9;
	//	}
		//
	//	LED_DATA = wd_flag;
		switch(mode){
		case 0://day
			digit_reset();
			DAC.DADR0=0;
			LED_day_mode();
			break;
		case 1://night
			DAC.DADR0=light;
			LED_night_mode();
			break;
		case 2://night to day for a cycle
			LED_night_to_day_mode();
			break;
		case 7://remote control mode
			LED_remote_mode();
			break;
		case 9:
			test_breakdown();
			break;
		}
		send_str("LEDMode=",8);
		send_char(mode+0x30);
		send_char('!');
		delay_ms(1000);
	//	LED_DATA=0;
	}
}

void init_timer();
void uart_init(){
	SCI.SCSCR.BYTE = 0x00;
	SCI.SCSMR.BYTE = 0x00;
	SCI.SCBRR = 0x19;
	delay_ms(10);
	SCI.SCSCR.BYTE = 0x70;
}
void send_char(char x){
	SCI.SCSCR.BYTE = 0x70; // 允许发送
	while(SCI.SCSSR.BIT.TDRE == 0) {} // 等待
	SCI.SCTDR = x; // 写数据
	SCI.SCSSR.BYTE &= 0x7F; // 清TDRE位
	delay_ms(5); // 等待少许时钟周期
	SCI.SCSCR.BYTE = 0x50; // 关闭发送
}
void send_str(char *s,int len){
	int i=0;
	send_char('\r');
	send_char('\n');
	while(i<len){
		send_char(s[i]);
		i++;
		LED_DATA=i;
	}
	send_char('\0');
	send_char('\r');
	send_char('\n');
}

void main()
{
//	

//  HEW3编译器要求所有变量定义必须放在所有程序代码最前面，否则会报错

	int i, j, a, b, c;
	char x;
	a = 1;
	b = 2;
	c = a + b;
	a = 0;
	b = 0;
	c = 0;
	//set_para = 0xA587;
	mode=0;
	light=0;
	//
	//CPG.WTCNT.WRITE = 0x5A00;
	//CPG.WTCSR.WRITE = 0xA587;

	//wd_flag=0;
	//
	uart_init();
	delay_ms(500);
	send_str("uart initialized successfully",29);
	LED_init();
	digit_init();
	AD_DA_init();
	

	//test

	traffic_light_sensor_demo();
	sleep();		// 用于独立HEW3环境调试，针对“PC指针 = 当前执行指令 + 2”的问题
//	sleep();		// 同上
//	sleep();		// 同上

//	for(;;){}		// 循环
}

void init_timer()
{

   TMU.TSTR.BYTE  = 0x00;                // 在操作前停步计数
   TMU0.TCOR = (PCLK/256/1000) - 1;		// 设置比较寄存器      
   TMU0.TCNT = (PCLK/256/1000) - 1;  		//  
                                		// 每秒100次
   TMU0.TCR.WORD  = 0x0023;             // 中断使能
                                		// 时钟源= PCLK/256

   TMU1.TCOR = (PCLK/256/1000) - 1;		// 设置比较寄存器      
   TMU1.TCNT = (PCLK/256/1000) - 1;
   TMU1.TCR.WORD  = 0x0023;

   TMU2.TCR.WORD  = 0x0000;
   TMU.TSTR.BYTE |= 0x03;				// 启动TMU0	,1			
	
}

void TMU0_ISR()
{

	TMU0.TCR.WORD = 0x0023;				// 清中断标志
	/*
	if(gFLAG == 0){
		gFLAG = 1;
		LED_DATA = 0x0000;
	}
	else{
		gFLAG = 0;
		LED_DATA = 0x00FF;
	}
	*/
	gFLAG--;
	tFLAG--;
}
void WGT_ISR(){
	CPG.WTCNT.WRITE = 0x5A00;
	CPG.WTCSR.WRITE = set_para;
	wd_flag++;
	LED_DATA=0xAA+1;
	if(mode!=9){
		wd_flag=0;
	}
	if(wd_flag>100&&break_flag==0){
		mode=0;
		wd_flag=0;
		break_flag=1;
		digit_reset();
	}
}
void NMI_ISR(){
	set_para = 0xA5C7;
	break_flag=0;
	LED_DATA=break_flag;
}
void RXI0_ISR(){
	LED_DATA=0x00;
	*gpchar = SCI.SCRDR;
	LED_DATA=*gpchar;
	if(mode!=7){
		if(*gpchar == 'R'){
			mode=7;
		}
	}
	else{
		if(*gpchar == 'L'){
			mode=0;
		}
		else if(*gpchar == 'N'){
			LED_reset();
			light=(light+1)%3;
			light_LED(light);
		}
	}
	SCI.SCSSR.BIT.RDRF = 0;
}

/*****************************************************************************

在新添加的文件中需要包含此头文件


******************************************************************************/
#ifndef		_INCLUDES_H
#define		_INCLUDES_H

// inherent functions
#include    <machine.h>
#include	<stddef.h>
#include	<ctype.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<string.h>
#include	<limits.h>

// 7709S 寄存器定义头文件
#include	"7709S.h"

// 配置变量定义
#define		SP_BASE		0x0D000000							// 堆栈底部地址
#define		VBR_BASE	0x0C000000							// VBR地址
#define		PCLK		32000000UL							// 系统外部时钟32MHz
#define		LED_DATA 	(*(unsigned short *) 0x00800000) 	// 指示LED



// 请将所有函数的声明置于此处

// 段定义
extern char * _D_ROM, * _B_BGN, * _B_END, * _D_BGN, * _D_END;
extern int mode;
extern int wd_flag;
extern int set_para;
// 异常和中断处理程序
void GEHandler( void );
void TLBHandler( void );
void INTHandler ( void );

// 初始化
void hardware_init();
void system_init();
void SCT_init ( void );
void INTC_init ();
int get_sound_sensor_data();

// delay
void delay_ms();

//LED_operate
void LED_reset();
void light_LED(int i);
void light_all_LED();
void led_test();
void LED_day_mode();
void LED_night_mode();
void LED_night_to_day_mode();

//digit_operate
void light_digit(int number,int position);

// 主函数
void main();

// 用户定义函数
void TMU0_ISR();		// 定时器0中断服务程序
void init_timer ();		// 定时器初始化
void IRQ0_ISR();		// IRQ0 服务程序
void IRQ4_ISR();
void RXI0_ISR();
void MNI_ISR();
void WGT_ISR();
#endif

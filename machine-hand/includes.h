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
extern int control;
// 异常和中断处理程序
void GEHandler( void );
void TLBHandler( void );
void INTHandler ( void );

// 初始化
void hardware_init();
void system_init();
void SCT_init ( void );
void INTC_init ();


// 主函数
void main();

// 用户定义函数
void TMU0_ISR();		// 定时器0中断服务程序
void TMU1_ISR();
void init_timer ();		// 定时器初始化
void init_state ();
void IRQ0_ISR();	
void IRQ1_ISR();
void IRQ2_ISR();
void IRQ3_ISR();

void NMI_ISR();

//key
void key_1();
void key_2();
void key_3();
void key_4();
void key_5();
void key_6();
void key_7();
void key_8();
void key_9();
void key_0();
void key_A(int *ctl);
void key_B(int *ctl);
void key_C(int *ctl);
void key_D(int *ctl);
void key_star();
void key_sharp();
// PWM函数
void init_PWM();
void delay_mms(long ms);
void PWM_resetall();
void PWM_work();
void PWM_test(int mode);
void PWM_ctl(int* args);
void angle_to_args(int *para);
#endif

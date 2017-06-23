/*****************************************************************************

������ӵ��ļ�����Ҫ������ͷ�ļ�


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

// 7709S �Ĵ�������ͷ�ļ�
#include	"7709S.h"

// ���ñ�������
#define		SP_BASE		0x0D000000							// ��ջ�ײ���ַ
#define		VBR_BASE	0x0C000000							// VBR��ַ
#define		PCLK		32000000UL							// ϵͳ�ⲿʱ��32MHz
#define		LED_DATA 	(*(unsigned short *) 0x00800000) 	// ָʾLED



// �뽫���к������������ڴ˴�

// �ζ���
extern char * _D_ROM, * _B_BGN, * _B_END, * _D_BGN, * _D_END;
extern int control;
// �쳣���жϴ������
void GEHandler( void );
void TLBHandler( void );
void INTHandler ( void );

// ��ʼ��
void hardware_init();
void system_init();
void SCT_init ( void );
void INTC_init ();


// ������
void main();

// �û����庯��
void TMU0_ISR();		// ��ʱ��0�жϷ������
void TMU1_ISR();
void init_timer ();		// ��ʱ����ʼ��
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
// PWM����
void init_PWM();
void delay_mms(long ms);
void PWM_resetall();
void PWM_work();
void PWM_test(int mode);
void PWM_ctl(int* args);
void angle_to_args(int *para);
#endif

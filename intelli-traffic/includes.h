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
extern int mode;
extern int wd_flag;
extern int set_para;
// �쳣���жϴ������
void GEHandler( void );
void TLBHandler( void );
void INTHandler ( void );

// ��ʼ��
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

// ������
void main();

// �û����庯��
void TMU0_ISR();		// ��ʱ��0�жϷ������
void init_timer ();		// ��ʱ����ʼ��
void IRQ0_ISR();		// IRQ0 �������
void IRQ4_ISR();
void RXI0_ISR();
void MNI_ISR();
void WGT_ISR();
#endif

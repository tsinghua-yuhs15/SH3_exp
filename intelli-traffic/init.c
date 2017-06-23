
#include	"includes.h"

// ʹ�ö���HEW3�������޷�����������Debugʱ�����øö��壬������������Ӳ����ʼ��
// ��������mot�ļ���ʵ���֮ǰ������ע�͵��ö��壬���±�������
//
//#define	_HEW3Simu

// ϵͳ��ʼ������
void system_init ()
{

 	set_vbr((void *) VBR_BASE);	// ����VBR 

#ifndef		_HEW3Simu			// ʹ�ö�����HEW3�������޷�����������Debug

	set_imask(15);				// ���ж�
	hardware_init();			// Ӳ����ʼ��
	set_imask(0);				// ���ж�
	
#endif

	main();						// ������
//	for(;;){}

}

// Ӳ����ʼ������
void hardware_init()
{
	SCT_init();					// ����ROM�г�ʼ��������ֵ��RAM�еĶ�Ӧ��ַ
	INTC_init();				// �жϳ�ʼ��

// ���ڴ˴�����û���Ӳ����ʼ������


// ********************************

}

void SCT_init ()
{
   char * p, * q;

   // ���÷ǳ��������ĳ�ֵΪ0 
   for ( p = _B_BGN; p < _B_END; ++p ){
       *p = 0x00;
	  }
   // ����ROM�г�ʼ��������ֵ��RAM�еĶ�Ӧ��ַ
   for ( p = _D_BGN, q = _D_ROM; p < _D_END; ++p, ++q ) {
       *p = *q;	
	}
}

// �ж����ȼ���ʼ��������
// ����õ�������ϵ㷽ʽ���ԣ����û�ֻ�ı��Լ���Ҫ�ĵط�
void INTC_init ()
{


	INTC.ICR0.WORD  = 0x8000;		// NMI is detected by falling edge            */
	INTX.ICR1.WORD  = 0x0002;		// MAI=0, All Interrupts are not masked.      */
									/* Use IRQ3-IRQ0 four independent interrupt   */
									/* NMI is masked when BL is 1.                */
									/* IRQ5 - IRQ0 are detected by falling edge   */
	INTX.ICR2.WORD  = 0x0000;		/* Interrupt are detected at low level input  */
									/* to the PINT pins.                          */
	INTX.PINTER.WORD = 0x0000;		/* Disable PINT input interrupt requests      */

	/*-----------------------------------------------------------------*/
	/*  ����Ƭ�Ϲ���ģ����ж����ȼ�									*/
	/*-----------------------------------------------------------------*/
	INTC.IPRA.WORD  = 0xF000;		/* TMU0,        TMU1,         TMU2,  RTC      */
	INTC.IPRB.WORD  = 0xF000;		/* WDT,         REF,          SCI0,  reserevd */
	INTX.IPRC.WORD  = 0x000F;		/* IRQ3,        IRQ2,         IRQ1,  IRQ0     */
	INTX.IPRD.WORD  = 0x000F;		/* PINT0-PINT7, PINT8-PINT15, IRQ5,  IRQ4     */
	INTX.IPRE.WORD  = 0x0000;		/* DMAC,        IrDA,         SCIF2,  A/D     */

}



#include	"includes.h"

// 使用独立HEW3环境（无仿真器）进行Debug时，设置该定义，用以跳过部分硬件初始化
// 最终下载mot文件到实验板之前，必须注释掉该定义，重新编译生成
//
//#define	_HEW3Simu

// 系统初始化函数
void system_init ()
{

 	set_vbr((void *) VBR_BASE);	// 设置VBR 

#ifndef		_HEW3Simu			// 使用独立的HEW3环境（无仿真器）进行Debug

	set_imask(15);				// 关中断
	hardware_init();			// 硬件初始化
	set_imask(0);				// 开中断
	
#endif

	main();						// 主函数
//	for(;;){}

}

// 硬件初始化函数
void hardware_init()
{
	SCT_init();					// 拷贝ROM中初始化变量的值到RAM中的对应地址
	INTC_init();				// 中断初始化

// 请在此处添加用户的硬件初始化程序


// ********************************

}

void SCT_init ()
{
   char * p, * q;

   // 设置非初化变量的初值为0 
   for ( p = _B_BGN; p < _B_END; ++p ){
       *p = 0x00;
	  }
   // 拷贝ROM中初始化变量的值到RAM中的对应地址
   for ( p = _D_BGN, q = _D_ROM; p < _D_END; ++p, ++q ) {
       *p = *q;	
	}
}

// 中断优先级初始化函数，
// 如果用单步或设断点方式调试，请用户只改变自己需要的地方
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
	/*  设置片上功能模块的中断优先级									*/
	/*-----------------------------------------------------------------*/
	INTC.IPRA.WORD  = 0xF000;		/* TMU0,        TMU1,         TMU2,  RTC      */
	INTC.IPRB.WORD  = 0xF000;		/* WDT,         REF,          SCI0,  reserevd */
	INTX.IPRC.WORD  = 0x000F;		/* IRQ3,        IRQ2,         IRQ1,  IRQ0     */
	INTX.IPRD.WORD  = 0x000F;		/* PINT0-PINT7, PINT8-PINT15, IRQ5,  IRQ4     */
	INTX.IPRE.WORD  = 0x0000;		/* DMAC,        IrDA,         SCIF2,  A/D     */

}


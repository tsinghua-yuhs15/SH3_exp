
#include "includes.h"

// 一般异常处理函数，请在对应的地方添加中断服务程序;

void IRQ0_ISR(){
	if(mode==1) mode=2;
}
void IRQ4_ISR(){
	INTX.IRR0.BIT.IRQ4R = 0;
	if(mode==1){
		LED_DATA=0xAA;
		mode=2;
	}
}

void GEHandler ()
{
	switch ( INTC.EXPEVT )
	{
		case 0x0E0 :  /*  Address Error (Instruction Access)  */
      	case 0x100 :  /*  & Address Error (Data Access)       */
			
			break;
		case 0x040 :  /*  TLB Invalid (Instruction Access)  */
		case 0x060 :  /*  & TLB Invalid (Data Access)       */
		
			break;
		case 0x0A0 :  /*  TLB Protection Violation (Instruction Access)  */
		case 0x0C0 :  /*  & TLB Protection Violation (Data Access)       */
		
			break;
      	case 0x180 :  /*  Reserved Instruction Code Exception  */

			break;
		case 0x1A0 :  /*  Illegal Slot Instruction Exception  */
		
			break;
		case 0x080 :  /*  Initial Page Write  */
		
			break;
		case 0x160 :  /*  Unconditional Trap  (TRAP instruction)  */
		
			break;
		case 0x1E0 :  /*  User Breakpoint Trap  */
				
			break;
		default:		
		break;
   }
}
// TLB丢失异常
void TLBHandler( void )
{
	switch ( INTC.EXPEVT )
	{
		case 0x040 :  /*  TLB Miss (Instruction Access)  */
		case 0x060 :  /*  & TLB Miss (Data Access)  */
			break;
		default:

			break;
   }
}
// 中断处理程序，请在对应地方添加中断服务程序
void INTHandler ( void )
{
	int iExcepCode1;
	int iExcepCode2;

	iExcepCode1 = INTC.INTEVT ;
	iExcepCode2 = INTX.INTEVT2 ;
	switch ( iExcepCode1 )
	{
		case 0x0000 :
			/*PowerON ();*/
			break;
		case 0x0020 :
			/*ManualON ();*/
			break;
		case 0x01c0 :       /*  NMI  */
			/*LOWNMI ();*/
			NMI_ISR();
           break;
		case 0x0200 :    /*  Interrupt Priority Level 15  */
		case 0x0220 :    /*  Interrupt Priority Level 14  */
		case 0x0240 :    /*  Interrupt Priority Level 13  */
		case 0x0260 :    /*  Interrupt Priority Level 12  */
		case 0x0280 :    /*  Interrupt Priority Level 11  */
		case 0x02A0 :    /*  Interrupt Priority Level 10  */
		case 0x02C0 :    /*  Interrupt Priority Level  9  */
		case 0x02E0 :    /*  Interrupt Priority Level  8  */
		case 0x0300 :    /*  Interrupt Priority Level  7  */
		case 0x0320 :    /*  Interrupt Priority Level  6  */
		case 0x0340 :    /*  Interrupt Priority Level  5  */
		case 0x0360 :    /*  Interrupt Priority Level  4  */
		case 0x0380 :    /*  Interrupt Priority Level  3  */
		case 0x03A0 :    /*  Interrupt Priority Level  2  */
		case 0x03C0 :    /*  Interrupt Priority Level  1  */
			switch ( iExcepCode2 )
			{
				case 0x0600 :  /*  IRQ0 Interrupt  */
					IRQ0_ISR();
					break;
				case 0x0620 :  /*  IRQ1 Interrupt  */
					/*IRQ1_ISR();*/
					break;
				case 0x0640 :  /*  IRQ2 Interrupt  *
					/*IRQ2_ISR();*/
					break;
				case 0x0660 :  /*  IRQ3 Interrupt  */
					/*IRQ3_ISR();*/
					break;
				case 0x0680 :  /*  IRQ4 Interrupt (Touch Panel Interrupt)  */
					IRQ4_ISR();
 					break;
				case 0x08A0 :  /*  IrDA's RXI1 Interrupt (Debug Port)  */
					/*RXI1_ISR();*/
					break;
				case 0x08E0 :  /*  IrDA's TXI1 Interrupt (Debug Port)  */
                   /*TXI1_ISR();*/
					break;
				case 0x0920 :  /*  SCIF's RXI2 Interrupt  */
					/* RXI2_ISR(); */
					break;
				case 0x0960	:	/* SCIF's TXI2 Interrupt */
					/* TXI2_ISR();*/
					break;
				default:
					break;
			}
		break;
		case 0x0400 :   /*  TMU0's TUNI0 Interrupt  */
			TMU0_ISR(); 
			break;
		case 0x04A0 :   /*  RTC's PRI Interrupt  */
			/*RTC_Periodic_ISR ();*/
			break;
		case 0x04E0 :   /*  SCI0's ERI Interrupt (Smart Card)  */
			/*ERI0_ISR ();*/
			break;
		case 0x0500 :   /*  SCI0's RXI Interrupt (Smart Card)  */
			RXI0_ISR();
			break;
		case 0x0520 :   /*  SCI0's TXI Interrupt (Smart Card)  */
			/*TXI0_ISR();*/
			break;
		case 0x0540 :   /*  SCI0's TEI Interrupt (Smart Card)  */
			/*TEI0_ISR();*/
			break;
		case 0x0560	:
			WGT_ISR();
		default:
			
			break;
	}
}


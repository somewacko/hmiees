#include <p33fj128gp202.h>
#include <hardwareprofile.h>
#include <stdio.h>
#include <uart.h>
#include <adc.h>



//#pragma config WDT = OFF, PBADEN = OFF, BOR = OFF
//#pragma config DEBUG = OFF, MCLRE = OFF, LVP = OFF, FOSC = INTOSCIO_EC

_FOSCSEL(FNOSC_FRCPLL)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)
_FWDT(FWDTEN_OFF)
_FICD(JTAGEN_OFF & ICS_PGD1);



int main (void){

	

	CLKDIVbits.PLLPRE = 0;
	PLLFBD = 41;
	CLKDIVbits.PLLPOST = 0;
		while(!OSCCONbits.LOCK);
	
	U1RXR_I = 14;
	RPOR7bits.RP15R = U1TX_O;	

	U1BRG = 85;
	U1MODE = 0;
	U1MODEbits.BRGH = 1;
	U1STA = 0;
	U1MODEbits.UARTEN = 1;
	IFS0bits.U1RXIF = 0;

        //AD1PCFGL = 0XFFFE;
        //AD1PCFGH = 0XFFFE;
        ADPCFG = 0XFFFE;
	

	while(1)
    {
        printf("ABCDEFGHIJK\n");
//        for(i=0;i<=2000;i++)
//        {}
//        test=test+1;
//        if (test >= 3000)
//        {
//            test = 0;
//        }
//
//	}
        }
}
			

//main()
//{
//    // disable JTAG port
//    
//
//    // 3.1 variable declarations
//    int i;           // i will serve as the index
//	int j;
//    // 3.2 initialization
//    TRISB = 0x0000;      // all PORTA as output
//	PORTB = 0X0000;
////    T1CON = 0x8030; // TMR1 on, prescale 1:256 PB
//
//    // 3.3 the main loop
//    while(1)
//    {
//            for (i = 0;i<9;i++)
//			{
//				for (j = 0;j<2000;j++)
//				{
//					PORTB = 0X0001;
//				}
//			}
//			for (j=0;j<9;j++)
//			{
//	 			for (i = 0;i<2000;i++)
//				{
//					PORTB = 0X0002;
//				}
//			}
//			for (j=0;j<9;j++)
//			{
//				for (i = 0;i<2000;i++)
//				{
//					PORTB = 0X0004;
//				}
//			}
//	       		PORTB = 0X000
// } // main loop
//} // main
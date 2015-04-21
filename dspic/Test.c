#include <p33fj128gp202.h>
#include <hardwareprofile.h>
#include <stdio.h>
#include <uart.h>
#include <adc.h>



//#pragma config WDT = OFF, PBADEN = OFF, BOR = OFF
//#pragma config DEBUG = OFF, MCLRE = OFF, LVP = OFF, FOSC = INTOSCIO_EC
void __attribute__((__interrupt__,__auto_psv__)) _ADC1Interrupt(void);
void __attribute__((__interrupt__, __no_auto_psv__)) _DMA1Interrupt(void);
unsigned int BufferA[4] __attribute__((space(dma)));
unsigned int BufferB[4] __attribute__((space(dma)));
unsigned int dmaBuffer = 0;

_FOSCSEL(FNOSC_FRCPLL)
_FOSC(OSCIOFNC_OFF & POSCMD_NONE)
_FWDT(FWDTEN_OFF)
_FICD(JTAGEN_OFF & ICS_PGD2);



int main (void){


/*-------------------INITIALIZE OSCILLATOR------------------------*/
	CLKDIVbits.PLLPRE = 0;      //clock prescaller 7.37Mhz/2
	PLLFBD = 41;                //multiplyer 41+2=43 (7.37Mhz/2)*43
	CLKDIVbits.PLLPOST = 0;     //postscaller /2   (7.37Mhz/2)*43/2 = 79.23 MHz
		while(!OSCCONbits.LOCK);    //wait for oscillator to set



/*-----------------INITIALZE UART----------------------------*/
        U1RXR_I = 14;               //uart input on Rp14
	RPOR7bits.RP15R = U1TX_O;   //usart output on Rp15

        //Baud Rate scaller = ((FCY/4)*115200)-1  if BRGH=1(creates baud rate of 115200)
        U1BRG = 85;

        //cont uart in idle, IrDA disabled, (uxRTS)' in flow control mode, wake up disabled, Loopback disableed, Autobaud disabled
        //UxRX pin is high in idle mode, 8bit data no parity, 1 stop bit
	U1MODE = 0;
	U1MODEbits.BRGH = 1;    //enables fast oscillator

        //interrupt created when any character transmitted to shift register,
        //UxTX pin is high on idle, sync break transmission is disabled
        //transmitter initialized as disabled UT1XEN bit, int flag set when character is received
	U1STA = 0;

        //enables transmission bit
	U1MODEbits.UARTEN = 1;
        
        //sets recieved interrupt flag to zero
	IFS0bits.U1RXIF = 0;


/*-----------------------INITIALIZE ADC--------------------------*/

//        //AD1PCFGL = 0XFFFE;
//        //AD1PCFGH = 0XFFFE;

        //continue module in idle, DMA buffers written in order of conversion, 10bit conversion
        //integer output, Samples CH0-3 simultaneously,sampling begins auto after last conversion
        AD1CON1 = 0x10FC;
        AD1CON2 = 0x2200;
        AD1CON3bits.ADRC = 0;   //clock derived from system tcy = 25.25 ns
        AD1CON3bits.SAMC = 2;   //2 tads = Tsamp
        AD1CON3bits.ADCS = 98;  // (98+1)*tcy = tad = 2.5us
        AD1CON4bits.DMABL = 0;  // 1 word buffer per input

        //sets negative pins for CH1-3 to Vref-, positive pins are AN3,4,5;
        AD1CHS123 = 0x0101;
        //sets negatve pins for CH0 to Vref-, positive pins are AN12;
        AD1CHS0 =  0x0C0C;

        //the following RP pins set to analog reading
        ADPCFGbits.PCFG12 = 0;
        ADPCFGbits.PCFG5 = 0;
        ADPCFGbits.PCFG4 = 0;
        ADPCFGbits.PCFG3 = 0;


/*------------------------INITIALIZE DMA-------------------------------*/

        DMA1CONbits.AMODE = 0;          //DMA for register indirect post inc mode
        DMA1CONbits.MODE = 2;
        DMA1PAD = (volatile unsigned int)&ADC1BUF0; // Point DMA to ADC1BUF0
        DMA1CNT = 3;            // 4DMA request
        DMA1REQ = 13;           //select ADC request source
        DMA1STA = __builtin_dmaoffset(BufferA);
        DMA1STB = __builtin_dmaoffset(BufferB);

        IFS0bits.DMA1IF = 0; //clear dma interrupt flag
        IEC0bits.DMA1IE = 1; //enable DMA interrupt

        DMA1CONbits.CHEN = 1;       //enable DMA




        //sets R/W-0 pin to be analog, all others digital
        //ADPCFG = 0XFFFE;
        //AD1CON1bits.ASAM = 0; //sampling begins when SAMP bit is set.
        //AD1CON1bits.SAMP = 0; //0 holding, 1 sampling


        unsigned test = 0, i; //adcon1234 need ch

        //turns on ADC
        AD1CON1bits.FORM = 0; //sets AD output (0=int 1=s-int, 2=frac, 3=sfrac
        AD1CON1bits.ADON = 1;
        IFS0bits.AD1IF = 0;
        IPC3bits.AD1IP = 7; //sets ADC1 conversion interrupt priority to 7
        INTTREGbits.ILR = 6; //sets CPU priority to 6
        IEC0bits.AD1IE = 0; //ADC interrupt is off
	while(1)
       {
        for(i=0;i<=2000;i++)
        {}
        test=test+1;

        if (test == 1500)
        {
            //printf("A\n");
        }

        if (test >= 3000)
        {
            test = 0;
            //printf("B\n");
        }

	}
}


void _ADC1Interrupt(void)
{
    unsigned d = ADC1BUF0;
    printf("d=%d\n", d);
    //printf("END CONVERSION\n");
            while(IFS0bits.U1TXIF)
            {
                IFS0bits.U1TXIF = 0;
            }
    IFS0bits.AD1IF = 0;
}

void _DMA1Interrupt(void)
{
    if(dmaBuffer ==0 )
    {
        printf("A:%d\t%d\t%d\t%d\n", BufferA[0], BufferA[1], BufferA[2], BufferA[3]);
    }
    else
    {
        printf("B:%d\t%d\t%d\t%d\n", BufferB[0], BufferB[1], BufferB[2], BufferB[3]);
    }

    dmaBuffer ^= 1;
    IFS0bits.DMA1IF = 0;

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
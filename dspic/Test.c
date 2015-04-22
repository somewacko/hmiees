#include <p33fj128gp202.h>
#include <hardwareprofile.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <uart.h>
#include <adc.h>
#include <math.h>
#include <libq.h>

#include "constants.h"
#include "emg_filter.h"
#include "emg_signal.h"
#include "emg_processing.h"



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


bool processing_is_ready = false;  // Flag to indicate to main loop that
                                   // enough samples have been read to begin
                                   // processing.

const unsigned SPERIOD      = 150; // Number of samples read after.
const double INT10_MAX      = pow(2,  9);
const double UINT10_MAX     = pow(2, 10);

processing_info_t processing_info;
volatile uint32_t ticks = 0;

_Q16 qsamples[8 * MAX_EMG_CHANNELS];


int main (void) {

    init_filters();

    // Init processing struct
    init_processing_info(&processing_info, SPERIOD);
    

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
        AD1CON3bits.ADCS = 60;  // (X+1)*tcy = tad
                                // decrease value to increase sampling frequency
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
        TRISBbits.TRISB13 = 0;



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

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("Starting...\n\n");

        //turns on ADC
        AD1CON1bits.FORM = 3; //sets AD output (0=int 1=s-int, 2=frac, 3=sfrac
        AD1CON1bits.ADON = 1;
        IFS0bits.AD1IF = 0;
        IPC3bits.AD1IP = 7; //sets ADC1 conversion interrupt priority to 7
        INTTREGbits.ILR = 6; //sets CPU priority to 6
        IEC0bits.AD1IE = 0; //ADC interrupt is off


        // Main loop

        unsigned num_late = 0;
        _Q16 qgroup[MAX_EMG_CHANNELS];
        emg_sample_group_t sample_group;


        while (ticks < 32000); // Wait a second

        printf("Running\n\n");
        
	while(1)
        {
//            if (ticks % 2000 < 10)
//            {
//                printf("\r%7.4f %7.4f | ticks: %8lu | sec: %4lu    ",
//                    sample_group[0],
//                    sample_group[1],
//                    ticks,
//                    ticks/8000
//                );
//            }
            
            if (processing_is_ready)
            {
                processing_is_ready = false;

                for (int i = 0; i < 8*MAX_EMG_CHANNELS; i += MAX_EMG_CHANNELS)
                {
                    qgroup[0] = qsamples[i  ];
                    qgroup[1] = qsamples[i+1];
                    filter_sample_group(qgroup);
                }

                sample_group[0] = _itofQ16(qgroup[0]);
                sample_group[1] = _itofQ16(qgroup[1]);


                process_sample(&processing_info, sample_group);

//                if (processing_is_ready)
//                    printf("\rnum_late: %d    ", ++num_late);
            }
	}
}


void _DMA1Interrupt(void)
{
    uint8_t i = ticks % 8;

    if(DMACS1bits.PPST1 == 0)
    {
        // Ignore BufferA[0]
        qsamples[i  ] = BufferA[1];
        qsamples[i+1] = BufferA[2];
        //samples[i+2] = BufferA[3];
    }
    else
    {
        // Ignore BufferB[0]
        qsamples[i  ] = BufferB[1];
        qsamples[i+1] = BufferB[2];
        //samples[i+2] = BufferB[3];
    }

    IFS0bits.DMA1IF = 0;

    if (i == 7)
        processing_is_ready = true;

    ticks++;
}


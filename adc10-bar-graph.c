    //====================================================================================================//
    // Program to display the ADC values in a BarGraph style Display                                      //
	//----------------------------------------------------------------------------------------------------//
	// ADC10 of MSP430G2553 runs in Single Channel,Single Conversion mode.A Potentiometer connected to A0 //
	// channel of ADC10 is varied and the voltage variations are displayed on LED bar display.            //
	//====================================================================================================//
    // www.xanthium.in										                                              //
    // Copyright (C) 2015 Rahul.S                                                                         //
    //====================================================================================================//
    // Compiled on IAR Embedded Workbench for MSP430 version 5.30.1                                       //
    // 18-October-2015                                                                                    //
    // Rahul.S                                                                                            //
    //====================================================================================================//
    
    // Visit http://xanthium.in/msp430-launchpad-adc10-configuration-tutorial   for more details          
	
	#include "msp430g2553.h"
	#include "intrinsics.h"
	void main(void)
	{
		WDTCTL = WDTPW  + WDTHOLD;    // stop WDT
		
		P2DIR = 0xFF;                 // Port 2 all output
		P2OUT = 0x00;                 // Port 2 all zero
		P2SEL  &= ~BIT6;              // Clear P2.6 in P2SEL  (by default Xin)
		P2SEL2 &= ~BIT6;              // Clear P2.6 in P2SEL2
		P2SEL  &= ~BIT7;              // Clear P2.7 in P2SEL  (by default Xin)
		P2SEL2 &= ~BIT7;              // Clear P2.7 in P2SEL2
		// ADC configuration
        // V+ref=3V,V-ref=0V,Channel=A0
                   
        ADC10CTL0  = ADC10ON + ADC10IE;     // Vref Vr+=3v,Vr-=VSS,
											// S&Htime = 4 X ADCCLK,ADC10 on,ADC interrupts enabled
        ADC10CTL1  = ADC10DIV_7 ;           // INCH =0000->A0,ADCCLK src = ADC10CLK,
		                                    // ADCCLK/8,Single Channel Repeat Conversion
        ADC10AE0   = INCH_0;                // channel A0 
                   
        ADC10CTL0 |= ENC + ADC10SC;         // Start Conversion
		
		_BIS_SR(LPM0_bits +GIE);            // Go to LPM0,interrupts enabled
	}

    /********************************************************************************/
	/*                        interrupt vectors for MSP430                          */
	/********************************************************************************/

	#pragma vector = ADC10_VECTOR
    __interrupt void adc10_interrupt(void)
	{
         unsigned int adc_value = 0;
		 adc_value = ADC10MEM;
		 
		 //LED Bar implementation
		 	if ((adc_value > 0) & (adc_value < 10)) 
			    P2OUT = 0x00;
		 	if (adc_value >= 127) 
			  	P2OUT = 0x01;
		 	if (adc_value >= 254) 
			  	P2OUT = 0x03;
		 	if (adc_value >= 381)
			    P2OUT = 0x06;
		 	if (adc_value >= 508) 
			    P2OUT = 0x0F;
		 	if (adc_value >= 635) 
			    P2OUT = 0x1F;
		 	if (adc_value >= 762) 
			    P2OUT = 0x3F;
		    if (adc_value >= 889) 
			    P2OUT = 0x6F;
		 	if (adc_value >= 1016) 
			    P2OUT = 0xFF;
		   ADC10CTL0 |= ENC + ADC10SC;  // Start Conversion  
		 
		 
    }
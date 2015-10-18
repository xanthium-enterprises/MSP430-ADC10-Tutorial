    //====================================================================================================//
    // A simple Program to configure ADC10 of MSP430G2553 in Single Channel,Single Conversion mode        //
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
		// ADC configuration
        // V+ref=3V,V-ref=0V,Channel=A0
                   
        ADC10CTL0  = ADC10ON + ADC10IE; // Vref Vr+=3v,Vr-=VSS,
										// S&Htime = 4 X ADCCLK,ADC10 on,ADC interrupts enabled
        ADC10CTL1  = ADC10DIV_7;        // INCH =0000->A0,ADCCLK src = ADC10CLK,
		                                // ADCCLK/8,Single Channel Single Conversion
        ADC10AE0   = INCH_0;            // channel A0 
                   
        ADC10CTL0 |= ENC + ADC10SC;     // Start Conversion
		
		_BIS_SR(LPM0_bits +GIE);        // Go to LPM0,interrupts enabled
	}

	/********************************************************************************/
	/*                        interrupt vectors for MSP430                          */
	/********************************************************************************/

	#pragma vector = ADC10_VECTOR
    __interrupt void adc10_interrupt(void)
	{
         ADC10CTL0 |= ENC + ADC10SC;  // Start Conversion
    }

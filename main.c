#include "DSP2833x_Device.h"     // DSP2833x header
#include "DSP2833x_Examples.h"   // DSP2833x example
/**
 * main.c
 */
void delay_loop(void);
void Gpio_select(void);
void main(void)
{
   //step1 initial system control
   //Setting PLL,WatchDog, Clock 
   //Can Find this function in DSP2833x_SysCtrl.c
   InitSysCtrl();
   //Step 2. initial GPIO 
   Gpio_select();
   // Step 3. Clear all interrupts and initialize PIE vector table:
   // Disable CPU interrupts
   DINT;
   // Step4. Initialize the PIE vector table with pointers to the shell Interrupt
   // Service Routines (ISR).
   // This will populate the entire table, even if the interrupt
   // is not used in this example.  This is useful for debug purposes.
   // The shell ISR routines are found in F2837xD_DefaultIsr.c.
   // This function is found in F2837xD_PieVect.c.
   InitPieCtrl();
   // Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;
   // Initialize the PIE vector table with pointers to the shell Interrupt 
   // Service Routines (ISR).  
   // This will populate the entire table, even if the interrupt
   // is not used in this example.  This is useful for debug purposes.
   // The shell ISR routines are found in DSP281x_DefaultIsr.c.
   // This function is found in DSP281x_PieVect.c.
   InitPieVectTable();
   // Step 4. Initialize all the Device Peripherals:
   // This function is found in DSP281x_InitPeripherals.c
   // InitPeripherals(); // Not required for this example
   GpioDataRegs.GPBDAT.all    =0x30000000;
   GpioDataRegs.GPCDAT.all    =0x00000007;
   // Step 5. User specific code 
   for(;;)
   {   
       
	   delay_loop();
       GpioDataRegs.GPBTOGGLE.all =0x30000000; 
       GpioDataRegs.GPCTOGGLE.all =0x00000007; 			  
       
       delay_loop();

       GpioDataRegs.GPBTOGGLE.all =0x30000000; 
       GpioDataRegs.GPCTOGGLE.all =0x00000007; 
    
    }
}
//GPIO initial
void Gpio_select(void)
{

   
    EALLOW;
	GpioCtrlRegs.GPAMUX1.all = 0x00000000;  // All GPIO
	GpioCtrlRegs.GPAMUX2.all = 0x00000000;  // All GPIO
	GpioCtrlRegs.GPBMUX1.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPBMUX2.all = 0x00000000;  // All GPIO
	GpioCtrlRegs.GPCMUX1.all = 0x00000000;  // All GPIO
	GpioCtrlRegs.GPCMUX2.all = 0x00000000;  // All GPIO

    GpioCtrlRegs.GPADIR.all = 0xFFFFFFFF;   // All outputs
    GpioCtrlRegs.GPBDIR.all = 0xFFFFFFFF;   // All outputs
    GpioCtrlRegs.GPCDIR.all = 0xFFFFFFFF;   // All outputs
    EDIS; 
}   
void delay_loop()
{
    Uint32      i;
	Uint32      j;
	for(i=0;i<32;i++)
    for (j = 0; j < 100000; j++) {}
}

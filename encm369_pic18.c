/*!**********************************************************************************************************************
@file encm369_pic18.c                                                                
@brief This file provides core and GPIO functions for the ENCM 369 PIC activities.


------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- 

PROTECTED FUNCTIONS
- 

***********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_xxBsp"
***********************************************************************************************************************/
/* New variables */




/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;        /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;         /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;          /*!< @brief From main.c */

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Bsp_" and be declared as static.
***********************************************************************************************************************/

/***********************************************************************************************************************
Function Definitions
***********************************************************************************************************************/


/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/



/*!---------------------------------------------------------------------------------------------------------------------
@fn void ClockSetup(void)

@brief Loads all registers required to set up the processor clocks.

Requires:
- NONE

Promises:
- EFC is set up with proper flash access wait states based on 48MHz system clock
- PMC is set up with proper oscillators and clock sources

*/
void ClockSetup(void)
{
 
  
} /* end ClockSetup */


/*!---------------------------------------------------------------------------------------------------------------------
@fn void GpioSetup(void)

@brief Loads registers required to set up GPIO on the processor.

Requires:
- All configurations must match connected hardware.

Promises:
- Output pin for PA31_HEARTBEAT is configured

*/
void GpioSetup(void)
{
    LATA = 0x80; //Set data latch RA7 
    ANSELA = 0x00; //0 means digital function, 1 means analog function
    TRISA = 0x00; // input=1, output=0
  
  
} /* end GpioSetup() */


/*!---------------------------------------------------------------------------------------------------------------------
@fn  void SysTickSetup(void)

@brief Initializes the 1ms and 1s System Ticks off the core timer.

Requires:
- NVIC is setup and SysTick handler is installed

Promises:
- Both global system timers are reset and the SysTick core timer is configured for 1ms intervals

*/
void SysTickSetup(void)
{
  G_u32SystemTime1ms = 0;      
  G_u32SystemTime1s  = 0;   
  
} /* end SysTickSetup() */



/*!---------------------------------------------------------------------------------------------------------------------
@fn void SystemSleep(void)

@brief Puts the system into sleep mode.  


Requires:
- 
 * 
Promises:
- 

*/
void SystemSleep(void)
{    
  
} /* end SystemSleep(void) */



void TimeXus(u16 u16Microseconds)
{
    T0CON0=T0CON0 & 0x7F;
    
    u16 u16TimeDifference = 0xFFFF-u16Microseconds;
    u8 u8LowInput = u16TimeDifference & 0xFF;
    u8 u8HighInput =(u16TimeDifference>>8) & 0xFF;
    
    TMR0L = u8LowInput;
    TMR0H = u8HighInput;
    PIR3 = PIR3 & 0x7F ;       
    T0CON0 = T0CON0 | 0x80;
    
    while((PIR3 & 0x80)!= 0x80)
    {
        
    }  
} 
/* end TimeXus () */
/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/




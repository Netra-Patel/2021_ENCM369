/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE
*/
void UserAppInitialize(void)
{
    LATA=0x80;      //RA7 digital high
    T0CON0=0x90;    //Set enable, 16-bit, postscaler
    T0CON1=0x54;    //Set clock source, asynchronous, prescaler
    
    
} /* end UserAppInitialize() */
  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    static u16 u16Counter = 0;
    static u8 u8Index = 0;
    u8 au8Pattern[8] = {0x20,0x10,0x08,0x04,0x02,0x01};
    
    if (u16Counter>=500) 
    {  
        if (u8Index==6)   //Pattern array has reached end
        {
            u8Index=0;   //re-start pattern
        }
        LATA= au8Pattern[u8Index];   //LATA gets different index values of the array/pattern
        u8Index= u8Index + 1;        //Update Index
        u16Counter=0;               // Set counter to 0
    }
    else 
    {
        u16Counter= u16Counter +1;    //increment counter 
    }  
} /* end UserAppRun */


void TimeXus(u16 u16Microseconds_)
{
    T0CON0 = T0CON0 & 0x7F;   //sets Timer0 enable tolow   
    u16 u16TimerDifference = 0xFFFF - u16Microseconds_;  //find remaining time before overflow
    
    u8 u8LowInput = u16TimerDifference & 0xFF;   //bitmask 8 LSBs
    u8 u8HighInput = (u16TimerDifference >> 8) & 0xFF;  //bitmask 8 MSBs
    TMR0L = u8LowInput;  //preload Timer0 8 LSBs
    TMR0H = u8HighInput; //preload Timer0 8 MSBs
    
    PIR3 = PIR3 & 0x7F;  //sets TMR0IF to low
    
    T0CON0 = T0CON0 | 0x80;  //sets Timer0 enable to high
    
} 
/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/

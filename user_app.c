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
    LATA=0x81;      //Initialize LEDs
    
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
    static u16 su16Counter = 0x0000;
    static u8 su8Shift = 0x00;   //0 shifts left, 1 shifts right
    u8 u8Value;

    if(su16Counter == 0x01F4)   //if = 500 or 1ms total
    {
        su16Counter = 0x0000;  //reset counter
        u8Value = LATA & 0x7F;  //bitmask LATA 
        
        if(su8Shift == 0x00) //if shifting left
        {
            u8Value = u8Value << 2 ; //shift 2 left
        }
        
        if(su8Shift == 0x01) //if shifting right
        {
            u8Value = u8Value >> 2;  //shift 2 right
        }
        
        LATA = u8Value | 0x80;  //give value back to LATA 
  
         
        if(u8Value == 0x10) //reached far left point
        {
            su8Shift = 1; //change direction to right
        }
        
        if(u8Value == 0x01) //reached far right point
        {
            su8Shift = 0; //change direction to left
        }
    }
    su16Counter++;      //Increase Counter
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/

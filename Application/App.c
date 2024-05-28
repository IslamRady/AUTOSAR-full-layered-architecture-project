/******************************************************************************
 *
 * Module: Application
 *
 * File Name: App.c
 *
 * Description: Source file for Application Tasks.
 *
 * Author: Islam Mohamed Rady
 ******************************************************************************/

#include "App.h"
#include "ECUAL/Button/Button.h"
#include "ECUAL/Led/Led.h"
#include "MCAL/Dio/Dio.h"
#include "MCAL/MCU/Mcu.h"
#include "MCAL/Port/Port.h"
/* Description: Task executes once to initialize all the Modules */
void Init_Task(void)
{
    /* Initialize Mcu Driver */
    Mcu_Init();
    /* Initialize Dio Driver */
    Port_Init(&Port_Pins[0]);
    /* Initialize Dio Driver */
    Dio_Init(&Dio_Configuration);

}

/* Description: Task executes every 20 Mili-seconds to check the button state */
void Button_Task(void)
{
    Button_RefreshState();
}

/* Description: Task executes every 40 Mili-seconds to refresh the LED */
void Led_Task(void)
{
    Led_RefreshOutput();
}

/* Description: Task executes every 60 Mili-seconds to get the button status and toggle the led */
void App_Task(void)
{
    static uint8 button_previous_state = BUTTON_RELEASED;
    static uint8 button_current_state  = BUTTON_RELEASED;

    button_current_state = Button_GetState(); /* Read the button state */

    /* Only Toggle the led in case the current state of the switch is pressed
     * and the previous state is released */ 
    if((button_current_state == BUTTON_PRESSED) && (button_previous_state == BUTTON_RELEASED))
    {
        Led_Toggle();
    }

    button_previous_state = button_current_state;
}

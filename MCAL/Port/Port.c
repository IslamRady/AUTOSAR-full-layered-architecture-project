/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Islam Mohamed Rady
 ******************************************************************************/

#include "Port.h"
#include "Port_REGs.h"
#include "tm4c123gh6pm_registers.h"

/*include the Det.h file and check version compatibility*/
#if (STD_ON== PORT_DEV_ERROR_DETECT)

#include "Service_Layer/Det_Error/Det.h"
/* Software version incompatibility checking between (Det.h, Port)*/
#if ((DET_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (DET_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (DET_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Det.h does not match the expected version"
#endif
#if ((DET_AR_MAJOR_VERSION!= PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION!= PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error"The AR version of Det.h does not match the expected version"
#endif
#endif

STATIC const Port_ConfigType *ptr = NULL_PTR ;
STATIC boolean PortModule_Initialized= FALSE;

/************************************************************************************
 * Service Name: Port_Init
 * Service Id: 0X00
 * Parameters: ConfigPtr | Pointer to configuration set
 * Service Description: The function Port_Init shall initialize ALL ports and port pins
 *                      with the configuration set pointed to by the parameter
 ************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr )
{
    boolean error = FALSE ;
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    uint8 CounterOfChannels =0;

#if(STD_ON== PORT_DEV_ERROR_DETECT)
    if(NULL_PTR==ConfigPtr){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
        error = TRUE ;
    }
    else{
        /* do nothing*/
    }
#endif
    if(error==FALSE){
        ptr = ConfigPtr;
        for( CounterOfChannels=0; CounterOfChannels<NUMBER_OF_PORT_PINS; CounterOfChannels++){
            switch(ConfigPtr->port_num)
            {
            case  PORTA_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
            case  PORTB_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
            case  PORTC_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
            case  PORTD_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
            case  PORTE_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
            case  PORTF_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            default:
#if(STD_ON== PORT_DEV_ERROR_DETECT)
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
#endif
                break;
            }

            if( ((ConfigPtr->port_num == PORTD_ID) && (ConfigPtr->portpin_num == PORTD_PIN7_ID)) || ((ConfigPtr->port_num == PORTF_ID) && (ConfigPtr->portpin_num == PORTF_PIN0_ID)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = MAGIC_NUMBER ;                     /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr->portpin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (ConfigPtr->port_num == PORTC_ID) && (ConfigPtr->portpin_num <= PORTC_PIN3_ID) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            if(ConfigPtr->Portpin_direction == OUTPUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->portpin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if(ConfigPtr->initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->portpin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->portpin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if(ConfigPtr->Portpin_direction == INPUT)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->portpin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if(ConfigPtr->resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->portpin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(ConfigPtr->resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->portpin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->portpin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->portpin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
#if(STD_ON== PORT_DEV_ERROR_DETECT)

                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);/* det error */
#endif
            }
            /* ENable disable digital*/
            if(ConfigPtr->PortPin_DEN==TRUE){
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->portpin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->portpin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

            }
            else if(ConfigPtr->PortPin_DEN==FALSE){
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->portpin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->portpin_num);
            }
            else {
#if(STD_ON== PORT_DEV_ERROR_DETECT)

                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);/* det error */
#endif
            }
            /*modeeee*/
            if(Port_PortPinsMode[CounterOfChannels] & (1<<(Port_Pins[CounterOfChannels].PortPin_Mode))){
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->portpin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->portpin_num * 4));     /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (((0x0000000F& (ConfigPtr->PortPin_Mode)) << (ConfigPtr->portpin_num * 4)));     /* Clear the PMCx bits for this pin */
            }
            else if ((Port_Pins[CounterOfChannels].PortPin_Mode)== PORT_PIN_DIO_MODE){
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->portpin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->portpin_num * 4));     /* Clear the PMCx bits for this pin */
            }
            else {
#if(STD_ON== PORT_DEV_ERROR_DETECT)

                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_INVALID_MODE);/* det error */
#endif
            }
            ConfigPtr++;
        }
    }
    else {
        /* do nothing */
    }

}
/*
 *
 *  Service Name: Port_SetPinDirection
 * Service Id: 0X01
 * Parameters: Pin | Port Pin ID number, Direction | Port Pin Direction
 * Service Description: The function Port_SetPinDirection shall set the port pin
 *                      direction during runtime
 *
 */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){
    volatile uint32 *Port_Ptr = NULL_PTR ;
    boolean error = FALSE ;
#if(STD_ON== PORT_DEV_ERROR_DETECT)


    if(FALSE==PortModule_Initialized){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        error=TRUE;
    }
    /*************************************************************************/
    if(Pin>=NUMBER_OF_PORT_PINS){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error=TRUE;

    }
    /*************************************************************************/
    if(FALSE==(ptr[Pin].PortPin_DirChangeable)){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
        error=TRUE;
    }
    /****************************************************************************/
    else{
        /* do nothing*/
    }

#endif

    if(FALSE==error){
        if(TRUE==(ptr[Pin].PortPin_DirChangeable)){
            switch(ptr[Pin].port_num)
            {
            case  PORTA_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
            case  PORTB_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
            case  PORTC_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
            case  PORTD_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
            case  PORTE_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
            case  PORTF_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            default:
#if(STD_ON== PORT_DEV_ERROR_DETECT)

                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
                error=TRUE;
#endif
                break;
            }
            if(FALSE==error){
                if(INPUT==Direction){

                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , ptr[Pin].Portpin_direction);
                }
                else {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , ptr[Pin].Portpin_direction);

                }
            }


        }
        else {

        }
    }
    else{

    }

}

/********************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service Id: 0X02
 * Parameters: none
 * Service Description: shall refresh the direction of all configured ports to the
 *                      configured direction
 ********************************************************************************/
void Port_RefreshPortDirection(void){
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    boolean error ;
    uint8 CounterOfChannels =0 ;
#if(STD_ON== PORT_DEV_ERROR_DETECT)


    if(FALSE==PortModule_Initialized){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
        error=TRUE;
    }
    else{
        /* do nothing*/
    }

#endif
    if ( FALSE==error){
        for( CounterOfChannels=0; CounterOfChannels<NUMBER_OF_PORT_PINS; CounterOfChannels++){
            switch(ptr[CounterOfChannels].port_num)
            {
            case  PORTA_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
            case  PORTB_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
            case  PORTC_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
            case  PORTD_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
            case  PORTE_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
            case  PORTF_ID: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            default:
#if(STD_ON== PORT_DEV_ERROR_DETECT)
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_PARAM_CONFIG);
#endif
                break;
            }

            if( ((ptr[CounterOfChannels].port_num == PORTD_ID) && (ptr[CounterOfChannels].portpin_num == PORTD_PIN7_ID)) || ((ptr[CounterOfChannels].port_num == PORTF_ID) && (ptr[CounterOfChannels].portpin_num == PORTF_PIN0_ID)) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = MAGIC_NUMBER ;                     /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , ptr[CounterOfChannels].portpin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (ptr[CounterOfChannels].port_num == PORTC_ID) && (ptr[CounterOfChannels].portpin_num <= PORTC_PIN3_ID) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            if(ptr[CounterOfChannels].Portpin_direction == OUTPUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ptr[CounterOfChannels].portpin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            }
            else if(ptr[CounterOfChannels].Portpin_direction == INPUT)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ptr[CounterOfChannels].portpin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            }
            else
            {
#if(STD_ON== PORT_DEV_ERROR_DETECT)

                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_PARAM_CONFIG);/* det error */
#endif
            }


        }
    }
    else{

    }
}

/************************************************************************************
 * Service Name: PORT_GetVersionInfo
 * Service ID[hex]: 0x12
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        GPIO_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif
/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID: 0x04
 * Parameters: Pin | Port pin ID, Mode | New Port Pin mode to be set on port pin
 * Return value: None
 * Description: Function to  set the port pin mode of the referenced pin during runtime.
 ************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode){
    volatile uint32 *Port_Ptr = NULL_PTR ;
    boolean error = FALSE ;
#if(STD_ON== PORT_DEV_ERROR_DETECT)


    if(FALSE==PortModule_Initialized){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
        error=TRUE;
    }
    /*************************************************************************/
    if(Pin>=NUMBER_OF_PORT_PINS){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        error=TRUE;

    }
    /*************************************************************************/
    if(FALSE==(ptr[Pin].PortPin_DirChangeable)){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
        error=TRUE;
    }
    /****************************************************************************/
    else{
        /* do nothing*/
    }

#endif

    if(FALSE==error){
        if(TRUE==(ptr[Pin].PortPin_DirChangeable)){
            switch(ptr[Pin].port_num)
            {
            case  PORTA_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
            case  PORTB_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
            case  PORTC_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
            case  PORTD_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
            case  PORTE_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
            case  PORTF_ID: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
            default:
#if(STD_ON== PORT_DEV_ERROR_DETECT)

                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_CONFIG);
                error=TRUE;
#endif
                break;
            }
            if(FALSE==error){

                if(Port_PortPinsMode[Pin] & (1<<(Mode))){
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ptr[Pin].portpin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                    *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ptr[Pin].portpin_num * 4));     /* Clear the PMCx bits for this pin */
                    *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (((0x0000000F& (Mode)) << (ptr[Pin].portpin_num * 4)));     /* Clear the PMCx bits for this pin */
                }
                else if ((Port_Pins[Pin].PortPin_Mode)== PORT_PIN_DIO_MODE){
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ptr[Pin].portpin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                    *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ptr[Pin].portpin_num * 4));     /* Clear the PMCx bits for this pin */
                }
                else {
#if(STD_ON== PORT_DEV_ERROR_DETECT)

                    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_INVALID_MODE);/* det error */
#endif
                }
            }

        }
        else {

        }
    }
    else{

    }

}


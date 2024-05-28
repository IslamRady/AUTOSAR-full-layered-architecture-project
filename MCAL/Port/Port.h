 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Islam Mohamed Rady
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H
/*******************************************************************************
 *                             PORT DET Errors ID                              *
 *******************************************************************************/
/*
 * The following errors and exceptions shall be detectable by the PORT
 * driver depending on its build version (development/production).
 */
#define PORT_E_PARAM_PIN                            (uint8)0x0A
#define PORT_E_DIRECTION_UNCHANGEABLE               (uint8)0x0B
#define PORT_E_PARAM_CONFIG                         (uint8)0x0C
#define PORT_E_PARAM_INVALID_MODE                   (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE                    (uint8)0x0E
#define PORT_E_UNINIT                               (uint8)0x0F
#define PORT_E_PARAM_POINTER                        (uint8)0x10
/*******************************************************************************
 *                                APIs IDs Macros                              *
 *******************************************************************************/
#define PORT_INIT_SID                       (uint8)0x00
#define PORT_SET_PIN_DIRECTION_SID          (uint8)0x01
#define PORT_REFRESH_PORT_DIRECTION_SID     (uint8)0x02
#define GPIO_GET_VERSION_INFO_SID           (uint8)0x03
#define PORT_SET_PIN_MODE_SID               (uint8)0x04
/*******************************************************************************
 *                               PORT Version info                             *
 *******************************************************************************/
/* The vendors id */
#define PORT_VENDOR_ID                       (1100U)

/* Port Module Id */
#define PORT_MODULE_ID                       (125U)

/* Port Instance Id */
#define PORT_INSTANCE_ID                     (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)
/*******************************************************************************
 *                              Version Error Checking                              *
 *******************************************************************************/
#include "Port_Cfg.h"
/* checking the software version compatibility */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

#include "Std_Types.h"

/* checking the SW version compatibility */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
/*
 * Include the the DIO header file to use its standard types and functions
 */
#include "MCAL/Dio/Dio.h"
/* checking the software version compatibility */
#if ((DIO_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (DIO_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (DIO_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of dio.h does not match the expected version"
#endif

/* checking the AUTOSAR version compatibility */
#if ((DIO_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of dio .h does not match the expected version"
#endif

#include"Port_PBCfg.h"

/* checking the software version compatibility */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_PBCfg.h does not match the expected version"
#endif

/* checking the AUTOSAR version compatibility */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBCfg.h does not match the expected version"
#endif

/* The common macros is not AUTOSAR file so ther is no version checking */
#include "Common_Macros.h"
#include "Port_Regs.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef uint8 Port_PinModeType ; /* Type carry the different port pin mode */

typedef uint8 Port_PinType ;  /*  used for the symbolic name of a Port Pin */

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *  1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *  2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct
{
    uint8 port_num;
    Port_PinType portpin_num;
    Port_PinDirectionType Portpin_direction;
    Port_InternalResistor resistor;
    uint8 initial_value;
    Port_PinModeType PortPin_Mode ;
    boolean PortPin_DirChangeable ;
    boolean PortPin_ModeChangeable;
    boolean PortPin_DEN;


}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/********************************************************************************
 * Service Name: Port_Init
 * Service Id: 0X00
 * Parameters: ConfigPtr | Pointer to configuration set
 * Service Description: The function Port_Init shall initialize ALL ports and port pins
 *                      with the configuration set pointed to by the parameter
 ********************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr );

#if(PORT_SET_PIN_DIRECTION_API == STD_ON)

/********************************************************************************
 * Service Name: Port_SetPinDirection
 * Service Id: 0X01
 * Parameters: Pin | Port Pin ID number, Direction | Port Pin Direction
 * Service Description: The function Port_SetPinDirection shall set the port pin
 *                      direction during runtime
 ********************************************************************************/

void Port_SetPinDirection( Port_PinType Pin,Port_PinDirectionType Direction );

#endif

/********************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service Id: 0X02
 * Parameters: none
 * Service Description: shall refresh the direction of all configured ports to the
 *                      configured direction
 ********************************************************************************/

void Port_RefreshPortDirection(void);

#if(PORT_VERSION_INFO_API == STD_ON)

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

void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);

#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID: 0x04
 * Parameters: Pin | Port pin ID, Mode | New Port Pin mode to be set on port pin
 * Return value: None
 * Description: Function to  set the port pin mode of the referenced pin during runtime.
 ************************************************************************************/

void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

/************************************************************************************
 *                         declaring a Variable using extern classifier to use it in other files                       *
 ************************************************************************************/

extern Port_ConfigType Port_Pins [NUMBER_OF_PORT_PINS];
extern const uint16 Port_PortPinsMode [NUMBER_OF_PORT_PINS];
#endif /* PORT_H */

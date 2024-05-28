 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.c
 *
 * Description:  Source file  for Pre-Compiler configuration used by Port Module
 *
 * Author: Islam Mohamed Rady
 *
 *******************************************************************************/
#include "Port_Cfg.h"
#include "Port.h"

/*
 * Each pin has its own valid modes to be set
 * some has the ability of being UART/ CAN/ PMW.. etc but each mode is available alone
 * Ex: PORT A PIN 0 (PA0) has three different modes which are ( DIO, U0Rx and CAN1Rx).
 * each index of the array will represent available modes of a specific pin and the value corresponding to this index will be the hex value to be able to activate one of the available modes only.
 * arr[0] = 0x102.
 * arr[1] = 0x102.
 * arr[2] = 0x004. ... and so on.
 */
const uint16 Port_PortPinsMode[NUMBER_OF_PORT_PINS]= {

                                  0x102, /* Set pin 1, 8 */              0X102, /* Set pin 1, 8 */
                                  0X004, /* set pin 2    */              0X004, /* set pin 2    */
                                  0X004, /* set pin 2    */              0X004, /* set pin 2    */
                                  0X028, /* set pin 3, 5 */              0X028, /* set pin 3, 5 */
                                  0X082, /* set pin 1, 7 */              0X082, /* set pin 1, 7 */
                                  0X088, /* set pin 3, 7 */              0X088, /* set pin 3, 7 */
                                  0X194, /* set pin 2, 4, 7, 8 */        0X194, /* set pin 2, 4, 7, 8 */
                                  0X094, /* set pin 2, 4, 7 */           0X094, /* set pin 2, 4, 7 */
                                  0x000, /*JTAG Pins */                  0x000, /*JTAG Pins */
                                  0x000, /*JTAG Pins */                  0x000, /*JTAG Pins */
                                  0X1D6, /* set pin 1, 2, 4, 6, 7, 8 */  0X1D6, /* set pin 1, 2, 4, 6, 7, 8 */
                                  0X1C2, /* set pin 1, 6, 7, 8 */        0x182, /* set pin 1, 7, 8 */
                                  0x0BE, /* clear pin 0, 6 */            0x0BE, /* clear pin 0, 6 */
                                  0X196, /* set pin 1, 2, 4, 7, 8 */     0X1C6, /* set pin 1, 2, 6, 7, 8 */
                                  0X082, /* set pin 1, 7 */              0X082, /* set pin 1, 7 */
                                  0X0D2, /* set pin 1, 4, 6, 7 */        0X1C2, /* set pin 1, 6, 7, 8 */
                                  0X002, /* set pin 1 */                 0X002, /* set pin 1 */
                                  0X000, /* only configured as DIO */    0X000, /* only configured as DIO */
                                  0X13A, /* set pin 1, 3, 4, 5, 8 */     0X13A, /* set pin 1, 3, 4, 5, 8 */
                                  0X3EE, /* clear pin 4 */               0X6E6, /*1, 2, 5, 6, 7, 9, 14 */
                                  0X4B4, /*2, 4, 5, 7, 14 */             0X4AC, /*2, 3, 5, 7, 14 */
                                  0X1E0  /*5, 6, 7, 8 */
};


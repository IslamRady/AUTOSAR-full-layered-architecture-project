 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Islam Mohamed Rady
 ******************************************************************************/
#include "Port_PBCfg.h"
#include "Port.h"

Port_ConfigType Port_Pins [NUMBER_OF_PORT_PINS]={
                                                 PORTA_ID , PORTA_PIN0_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_A0_DIO_MODE , TRUE  , FALSE , TRUE,
                                                 PORTA_ID , PORTA_PIN1_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_A1_DIO_MODE , TRUE  , FALSE , TRUE,
                                                 PORTA_ID , PORTA_PIN2_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_A2_DIO_MODE , TRUE  , FALSE , TRUE,
                                                 PORTA_ID , PORTA_PIN3_ID , INPUT ,  PULL_DOWN , STD_LOW  , PORT_A3_DIO_MODE , FALSE , TRUE  , TRUE,
                                                 PORTA_ID , PORTA_PIN4_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_A4_DIO_MODE , TRUE  , FALSE , TRUE,
                                                 PORTA_ID , PORTA_PIN5_ID , INPUT ,  PULL_DOWN , STD_HIGH , PORT_A5_DIO_MODE , FALSE , FALSE , TRUE,
                                                 PORTA_ID , PORTA_PIN6_ID , OUTPUT , PULL_DOWN , STD_LOW  , PORT_A6_DIO_MODE , TRUE  , FALSE , TRUE,
                                                 PORTA_ID , PORTA_PIN7_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_A7_DIO_MODE , FALSE , TRUE  , TRUE,
                                                 /******************************************************************************/
                                                 PORTB_ID , PORTB_PIN0_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B0_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTB_ID , PORTB_PIN1_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B1_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTB_ID , PORTB_PIN2_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B2_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTB_ID , PORTB_PIN3_ID , INPUT ,  PULL_DOWN , STD_LOW  , PORT_B3_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 PORTB_ID , PORTB_PIN4_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B4_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTB_ID , PORTB_PIN5_ID , INPUT ,  PULL_DOWN , STD_HIGH , PORT_B5_DIO_MODE , FALSE ,  FALSE , TRUE,
                                                 PORTB_ID , PORTB_PIN6_ID , OUTPUT , PULL_DOWN , STD_LOW  , PORT_B6_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTB_ID , PORTB_PIN7_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B7_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 /******************************************************************************/
                                                 PORTC_ID , PORTC_PIN0_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B0_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTC_ID , PORTC_PIN1_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B1_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTC_ID , PORTC_PIN2_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B2_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTC_ID , PORTC_PIN3_ID , INPUT ,  PULL_DOWN , STD_LOW  , PORT_B3_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 PORTC_ID , PORTC_PIN4_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B4_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTC_ID , PORTC_PIN5_ID , INPUT ,  PULL_DOWN , STD_HIGH , PORT_B5_DIO_MODE , FALSE ,  FALSE , TRUE,
                                                 PORTC_ID , PORTC_PIN6_ID , OUTPUT , PULL_DOWN , STD_LOW  , PORT_B6_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTC_ID , PORTC_PIN7_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B7_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 /******************************************************************************/
                                                 PORTD_ID , PORTD_PIN0_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B0_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTD_ID , PORTD_PIN1_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B1_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTD_ID , PORTD_PIN2_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B2_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTD_ID , PORTD_PIN3_ID , INPUT ,  PULL_DOWN , STD_LOW  , PORT_B3_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 PORTD_ID , PORTD_PIN4_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B4_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTD_ID , PORTD_PIN5_ID , INPUT ,  PULL_DOWN , STD_HIGH , PORT_B5_DIO_MODE , FALSE ,  FALSE , TRUE,
                                                 PORTD_ID , PORTD_PIN6_ID , OUTPUT , PULL_DOWN , STD_LOW  , PORT_B6_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTD_ID , PORTD_PIN7_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B7_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 /******************************************************************************/
                                                 PORTE_ID , PORTE_PIN0_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B0_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTE_ID , PORTE_PIN1_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B1_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTE_ID , PORTE_PIN2_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_B2_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTE_ID , PORTE_PIN3_ID , INPUT ,  PULL_DOWN , STD_LOW  , PORT_B3_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 PORTE_ID , PORTE_PIN4_ID , OUTPUT , PULL_UP ,   STD_LOW  , PORT_B4_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTE_ID , PORTE_PIN5_ID , INPUT ,  PULL_DOWN , STD_HIGH , PORT_B5_DIO_MODE , FALSE ,  FALSE , TRUE,
                                                 /******************************************************************************/
                                                 PORTF_ID , PORTF_PIN0_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_F0_DIO_MODE , TRUE  ,  FALSE , TRUE,
                                                 PORTF_ID , PORTF_PIN1_ID , OUTPUT , OFF ,       STD_LOW  , PORT_F1_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTF_ID , PORTF_PIN2_ID , INPUT ,  PULL_UP ,   STD_HIGH , PORT_F2_DIO_MODE,  TRUE  ,  FALSE , TRUE,
                                                 PORTF_ID , PORTF_PIN3_ID , INPUT ,  PULL_DOWN , STD_LOW  , PORT_F3_DIO_MODE , FALSE ,  TRUE  , TRUE,
                                                 PORTF_ID , PORTF_PIN4_ID , INPUT , PULL_UP ,    STD_HIGH , PORT_F4_DIO_MODE , TRUE  ,  FALSE , TRUE
                                                 };


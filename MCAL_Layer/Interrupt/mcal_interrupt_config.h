/* 
 * File:   mcal_interrupt_config.h
 * Author: Omar Hisham
 *
 * Created on February 5, 2024, 1:17 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Includes Section */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"

/* Macros Section */
#define INTERRUPT_ENABLE                    1
#define INTERRUPT_DISABLE                   0
#define INTERRUPT_OCCUR                     1
#define INTERRUPT_NOT_OCCUR                 0
#define INTERRUPT_PRIORITY_ENABLE           1
#define INTERRUPT_PRIORITY_DISABLE          0

/* Macro Functions Section */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This macro enable priority levels */
#define INTERRUPT_PriorityLevelsEnable()       (RCONbits.IPEN = 1)
/* This macro disable priority levels */
#define INTERRUPT_PriorityLevelsDisable()      (RCONbits.IPEN = 0)

/****************************************************************************************************/
/* This macro will enable all HIGH priority global interrupts  ( JUST IN CASE IPEN = 1 ) */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/* This macro will disable all HIGH priority global interrupts ( JUST IN CASE IPEN = 1 ) */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

/****************************************************************************************************/
/* This macro will enable all LOW priority global interrupts   ( JUST IN CASE IPEN = 1 ) */
#define INTERRUPT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)
/* This macro will disable all LOW priority global interrupts  ( JUST IN CASE IPEN = 1 ) */
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)

#else
/****************************************************************************************************/
/* This macro enable global interrupt                          ( JUST IN CASE IPEN = 0 ) */
#define INTERRUPT_GlobalInterruptEnable()      (INTCONbits.GIE = 1)
/* This macro disable global interrupt                         ( JUST IN CASE IPEN = 0 ) */
#define INTERRUPT_GlobalInterruptDisable()     (INTCONbits.GIE = 0)

/****************************************************************************************************/
/* This macro will enable peripheral interrupts                ( JUST IN CASE IPEN = 0 ) */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* This macro will disable peripheral interrupts               ( JUST IN CASE IPEN = 0 ) */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

#endif

/* Data Types Declarations */
typedef enum {
    INTERRUPT_LOW_PRIORITY = 0 ,
    INTERRUPT_HIGH_PRIORITY 
}interrupt_priority_cfg;

/* Functions Declarations */

#endif	/* MCAL_INTERRUPT_CONFIG_H */


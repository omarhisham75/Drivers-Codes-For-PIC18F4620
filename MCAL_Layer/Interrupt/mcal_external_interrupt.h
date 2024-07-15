/* 
 * File:   mcal_external_interrupt.h
 * Author: Omar Hisham
 *
 * Created on February 5, 2024, 1:20 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Includes Section */
#include "mcal_interrupt_config.h"

/* Macros Section */
#if EXTERNAL_INTERRUPT_FEATURE_INTx_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the external interrupt (INT0) */
#define EXT_INT0_InterruptDisable()     (INTCONbits.INT0IE = 0)
/* This routine sets the interrupt enable for the external interrupt (INT0) */
#define EXT_INT0_InterruptEnable()      (INTCONbits.INT0IE = 1)
/* This routine clears the interrupt flag for the external interrupt (INT0) */
#define EXT_INT0_InterruptFlagClear()   (INTCONbits.INT0IF = 0)
/* This routine sets the edge detect of the external interrupt (INT0) to negative edge */
#define EXT_INT0_RisingEdgeSet()        (INTCON2bits.INTEDG0 = 1)
/* This routine sets the edge detect of the external interrupt (INT0) to positive edge */
#define EXT_INT0_FallingEdgeSet()       (INTCON2bits.INTEDG0 = 0)
/****************************************************************************************************/
/* This routine clears the interrupt enable for the external interrupt (INT1) */
#define EXT_INT1_InterruptDisable()     (INTCON3bits.INT1IE = 0)
/* This routine sets the interrupt enable for the external interrupt (INT1) */
#define EXT_INT1_InterruptEnable()      (INTCON3bits.INT1IE = 1)
/* This routine clears the interrupt flag for the external interrupt (INT1) */
#define EXT_INT1_InterruptFlagClear()   (INTCON3bits.INT1IF = 0)
/* This routine sets the edge detect of the external interrupt (INT1) to negative edge */
#define EXT_INT1_RisingEdgeSet()        (INTCON2bits.INTEDG1 = 1)
/* This routine sets the edge detect of the external interrupt (INT1) to positive edge */
#define EXT_INT1_FallingEdgeSet()       (INTCON2bits.INTEDG1 = 0)
/****************************************************************************************************/
/* This routine clears the interrupt enable for the external interrupt (INT2) */
#define EXT_INT2_InterruptDisable()     (INTCON3bits.INT2IE = 0)
/* This routine sets the interrupt enable for the external interrupt (INT2) */
#define EXT_INT2_InterruptEnable()      (INTCON3bits.INT2IE = 1)
/* This routine clears the interrupt flag for the external interrupt (INT2) */
#define EXT_INT2_InterruptFlagClear()   (INTCON3bits.INT2IF = 0)
/* This routine sets the edge detect of the external interrupt (INT2) to negative edge */
#define EXT_INT2_RisingEdgeSet()        (INTCON2bits.INTEDG2 = 1)
/* This routine sets the edge detect of the external interrupt (INT2) to positive edge */
#define EXT_INT2_FallingEdgeSet()       (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set INT1 external interrupt priority to be HIGH priority */
#define EXT_INT1_HighPrioritySet()      (INTCON3bits.INT1IP = 1)
/* This routine set INT1 external interrupt priority to be LOW priority */
#define EXT_INT1_LowPrioritySet()       (INTCON3bits.INT1IP = 0)
/* This routine set INT2 external interrupt priority to be HIGH priority */
#define EXT_INT2_HighPrioritySet()      (INTCON3bits.INT2IP = 1)
/* This routine set INT2 external interrupt priority to be LOW priority */
#define EXT_INT2_LowPrioritySet()       (INTCON3bits.INT2IP = 0)

#endif 

#endif

#ifdef EXTERNAL_INTERRUPT_FEATURE_OnChange_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the external interrupt (RBx) (On Change Interrupt) */
#define EXT_RBx_InterruptDisable()      (INTCONbits.RBIE = 0)
/* This routine sets the interrupt enable for the external interrupt   (RBx) (On Change Interrupt) */
#define EXT_RBx_InterruptEnable()       (INTCONbits.RBIE = 1)
/* This routine clears the interrupt flag for the external interrupt   (RBx) (On Change Interrupt) */
#define EXT_RBx_InterruptFlagClear()    (INTCONbits.RBIF = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set RBx external interrupt priority to be HIGH priority */
#define EXT_RBx_HighPrioritySet()      (INTCON2bits.RBIP = 1)
/* This routine set RBx external interrupt priority to be LOW priority */
#define EXT_RBx_LowPrioritySet()       (INTCON2bits.RBIP = 0)

#endif

#endif

/* Macro Functions Section */

/* Data Types Declarations */
typedef enum {
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge ;

typedef enum {
    INTERRUPT_EXTERNAL_INT0 = 0 ,
    INTERRUPT_EXTERNAL_INT1 ,
    INTERRUPT_EXTERNAL_INT2
}interrupt_INTx_src ;

typedef struct {
    void (*EXT_InterruptHandler)(void) ;
    pin_config_t mcu_pin ;
    interrupt_INTx_edge edge ;
    interrupt_INTx_src source ;
    interrupt_priority_cfg priority ;
}interrupt_NTx_t;

typedef struct {
    void (*EXT_InterruptHandler_HIGH)(void) ;
    void (*EXT_InterruptHandler_LOW)(void) ;
    pin_config_t mcu_pin ;
    interrupt_priority_cfg priority ;
}interrupt_RBx_t;

/* Functions Declarations */

Std_ReturnType Interrupt_NTx_Initialize(const interrupt_NTx_t *int_obj);
Std_ReturnType Interrupt_NTx_DeInitialize(const interrupt_NTx_t *int_obj);

Std_ReturnType Interrupt_RBx_Initialize(const interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInitialize(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */


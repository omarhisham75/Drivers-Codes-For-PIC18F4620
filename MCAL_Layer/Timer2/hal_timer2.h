/* 
 * File:   hal_timer2.h
 * Author: Omar Hisham
 *
 * Created on February 25, 2024, 11:42 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Includes Section */
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* Macros Section */

/* Macro Functions Section */

/* TMR2ON: Timer2 On bit */
#define TIMER2_MODULE_ENABLE()                  (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()                 (T2CONbits.TMR2ON = 0)

/* T2OUTPS3:T2OUTPS0: Timer2 Output Postscale Select bits */
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)  (T2CONbits.TOUTPS = _POSTSCALER_)

/* T2CKPS1:T2CKPS0: Timer2 Clock Prescale Select bits */
#define TIMER2_PRESCALER_SELECT(_PRESCALER_)    (T2CONbits.T2CKPS = _PRESCALER_)

/* Data Types Declarations */

/* Timer2 Output Postscaler Select */
typedef enum {
    TIMER2_POSTSCALER_DIV_BY_1 = 0 ,
    TIMER2_POSTSCALER_DIV_BY_2 ,
    TIMER2_POSTSCALER_DIV_BY_3 ,
    TIMER2_POSTSCALER_DIV_BY_4 ,
    TIMER2_POSTSCALER_DIV_BY_5 ,
    TIMER2_POSTSCALER_DIV_BY_6 ,
    TIMER2_POSTSCALER_DIV_BY_7 ,
    TIMER2_POSTSCALER_DIV_BY_8 , 
    TIMER2_POSTSCALER_DIV_BY_9 ,
    TIMER2_POSTSCALER_DIV_BY_10 ,
    TIMER2_POSTSCALER_DIV_BY_11 ,
    TIMER2_POSTSCALER_DIV_BY_12 ,
    TIMER2_POSTSCALER_DIV_BY_13 ,
    TIMER2_POSTSCALER_DIV_BY_14 ,
    TIMER2_POSTSCALER_DIV_BY_15 ,
    TIMER2_POSTSCALER_DIV_BY_16 
}timer2_postscaler_select_t ;

/* Timer2 Clock Prescaler Select */
typedef enum {
    TIMER2_PRESCALER_DIV_BY_1 = 0 ,
    TIMER2_PRESCALER_DIV_BY_2 ,
    TIMER2_PRESCALER_DIV_BY_3 ,
}timer2_prescaler_select_t ;

typedef struct {
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (*TIMER2_InterruptHandler)(void)       ;
    interrupt_priority_cfg priority             ;
#endif
    timer2_postscaler_select_t postscaler_value ;
    timer2_prescaler_select_t prescaler_value   ;
    uint8 timer2_preload_value               ;
}timer2_t ;

/* Functions Declarations */
Std_ReturnType Timer2_Initialize(const timer2_t *_timer);
Std_ReturnType Timer2_DeInitialize(const timer2_t *_timer);
Std_ReturnType Timer2_Write_value(const timer2_t *_timer , uint8 _value);
Std_ReturnType Timer2_Read_value(const timer2_t *_timer , uint8 *_value);

#endif	/* HAL_TIMER2_H */


/* 
 * File:   hal_timer0.h
 * Author: Omar Hisham
 *
 * Created on February 18, 2024, 10:25 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* Includes Section */
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* Macros Section */
#define TIMER0_PRESCALER_ENABLE_CFG            1
#define TIMER0_PRESCALER_DISABLE_CFG           0

#define TIMER0_RISING_EDGE_CFG                 1
#define TIMER0_FALLING_EDGE_CFG                0

#define TIMER0_TIMER_MODE                      1
#define TIMER0_COUNTER_MODE                    0

#define TIMER0_8BIT_REGISTER_MODE              1
#define TIMER0_16BIT_REGISTER_MODE             0

/* Macro Functions Section */

/* PSA: Timer0 Prescaler Assignment bit */
#define TIMER0_PRESCALER_ENABLE()              (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()             (T0CONbits.PSA = 1)

/* T0SE: Timer0 Source Edge Select bit */
#define TIMER0_RISING_EDGE_ENABLE()            (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()           (T0CONbits.T0SE = 1)

/* T0CS: Timer0 Clock Source Select bit */
#define TIMER0_TIMER_MODE_ENABLE()             (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()           (T0CONbits.T0CS = 1)

/* T08BIT: Timer0 8-Bit/16-Bit Control bit */
#define TIMER0_8BIT_REGIDTER_MODE_ENABLE()     (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGIDTER_MODE_ENABLE()    (T0CONbits.T08BIT = 0)

/* TMR0ON: Timer0 On/Off Control bit */
#define TIMER0_MODULE_ENABLE()                 (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()                (T0CONbits.TMR0ON = 0)

/* Data Types Declarations */
typedef enum {
    TIMER0_PRESCALER_DIV_BY_2 = 0 ,
    TIMER0_PRESCALER_DIV_BY_4 ,
    TIMER0_PRESCALER_DIV_BY_8 ,
    TIMER0_PRESCALER_DIV_BY_16 ,
    TIMER0_PRESCALER_DIV_BY_32 ,
    TIMER0_PRESCALER_DIV_BY_64 ,
    TIMER0_PRESCALER_DIV_BY_128 ,
    TIMER0_PRESCALER_DIV_BY_256 
}timer0_prescaler_select_t ;

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (*TIMER0_InterruptHandler)(void)     ;
    interrupt_priority_cfg priority           ;
#endif
    timer0_prescaler_select_t prescaler_value ;
    uint16 timer0_preload_value               ;
    uint8 prescaler_enable                : 1 ;
    uint8 timer0_counter_edge             : 1 ;
    uint8 timer0_mode                     : 1 ;
    uint8 timer0_register_size            : 1 ;
    uint8 timer0_reserved                 : 4 ;
}timer0_t ;

/* Functions Declarations */
Std_ReturnType Timer0_Initialize(const timer0_t *_timer);
Std_ReturnType Timer0_DeInitialize(const timer0_t *_timer);
Std_ReturnType Timer0_Write_value(const timer0_t *_timer , uint16 _value);
Std_ReturnType Timer0_Read_value(const timer0_t *_timer , uint16 *_value);

#endif	/* HAL_TIMER0_H */


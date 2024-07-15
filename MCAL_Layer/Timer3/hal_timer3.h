/* 
 * File:   hal_timer3.h
 * Author: Omar Hisham
 *
 * Created on February 25, 2024, 11:44 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Includes Section */
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* Macros Section */
/* Timer3 clock source ( Counter or Timer ) */
#define TIMER3_COUNTER_MODE                     1
#define TIMER3_TIMER_MODE                       0

/* Timer1 External clock synchronization */
#define TIMER3_ASYNC_COUNTER_MODE               1
#define TIMER3_SYNC_COUNTER_MODE                0

/* Prescaler value */
#define TIMER3_PRESCALER_DIV_BY_1               0
#define TIMER3_PRESCALER_DIV_BY_2               1
#define TIMER3_PRESCALER_DIV_BY_4               2
#define TIMER3_PRESCALER_DIV_BY_8               3

/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_16BIT_MODE                1
#define TIMER3_RW_REG_8BIT_MODE                 0

/* Macro Functions Section */
/* TMR3ON: Timer3 On bit */
#define TIMER3_MODULE_ENABLE()                  (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()                 (T3CONbits.TMR3ON = 0)

/* TMR3CS: Timer3 Clock Source Select bit */
#define TIMER3_TIMER_MODE_ENABLE()              (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()            (T3CONbits.TMR3CS = 1)

/* T3SYNC: Timer3 External Clock Input Synchronization Control bit ( When TMR3CS = 1 ) */
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC = 0)
#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()      (T3CONbits.T3SYNC = 1)

/* T3CKPS1:T3CKPS0: Timer3 Input Clock Prescale Select bits */
#define TIMER3_PRESCALER_SELECT(_PRESCALER_)    (T3CONbits.T3CKPS = _PRESCALER_)

/* RD16: 16-Bit Read/Write Mode Enable bit */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()        (T3CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()       (T3CONbits.RD16 = 1)

/* Data Types Declarations */
typedef struct {
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (*TIMER3_InterruptHandler)(void)     ;
    interrupt_priority_cfg priority           ;
#endif
    uint16 timer3_preload_value               ;
    uint8 timer3_prescaler_value          : 2 ;
    uint8 timer3_mode                     : 1 ;
    uint8 timer3_counter_mode             : 1 ;
    uint8 timer3_reg_rw_mode              : 1 ;
    uint8 timer3_reserved                 : 3 ;
}timer3_t ;

/* Functions Declarations */
Std_ReturnType Timer3_Initialize(const timer3_t *_timer);
Std_ReturnType Timer3_DeInitialize(const timer3_t *_timer);
Std_ReturnType Timer3_Write_value(const timer3_t *_timer , uint16 _value);
Std_ReturnType Timer3_Read_value(const timer3_t *_timer , uint16 *_value);

#endif	/* HAL_TIMER3_H */


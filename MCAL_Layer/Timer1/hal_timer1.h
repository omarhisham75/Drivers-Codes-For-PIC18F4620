/* 
 * File:   hal_timer1.h
 * Author: Omar Hisham
 *
 * Created on February 25, 2024, 5:40 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Includes Section */
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* Macros Section */
/* Timer1 clock source ( Counter or Timer ) */
#define TIMER1_COUNTER_MODE                     1
#define TIMER1_TIMER_MODE                       0

/* Timer1 External clock synchronization */
#define TIMER1_ASYNC_COUNTER_MODE               1
#define TIMER1_SYNC_COUNTER_MODE                0

/* Timer1 Oscillator */
#define TIMER1_OSC_ENABLE                       1
#define TIMER1_OSC_DISABLE                      0

/* Prescaler value */
#define TIMER1_PRESCALER_DIV_BY_1               0
#define TIMER1_PRESCALER_DIV_BY_2               1
#define TIMER1_PRESCALER_DIV_BY_4               2
#define TIMER1_PRESCALER_DIV_BY_8               3

/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_16BIT_MODE                1
#define TIMER1_RW_REG_8BIT_MODE                 1

/* Macro Functions Section */
/* TMR1ON: Timer1 On bit */
#define TIMER1_MODULE_ENABLE()                  (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                 (T1CONbits.TMR1ON = 0)

/* TMR1CS: Timer1 Clock Source Select bit */
#define TIMER1_TIMER_MODE_ENABLE()              (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()            (T1CONbits.TMR1CS = 1)

/* T1SYNC: Timer1 External Clock Input Synchronization Select bit ( When TMR1CS = 1 ) */
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()       (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()      (T1CONbits.T1SYNC = 1)

/* T1OSCEN: Timer1 Oscillator Enable bit */
#define TIMER1_OSC_ENABLE()                     (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_DISABLE()                    (T1CONbits.T1OSCEN = 0)

/* T1CKPS1:T1CKPS0: Timer1 Input Clock Prescale Select bits */
#define TIMER1_PRESCALER_SELECT(_PRESCALER_)    (T1CONbits.T1CKPS = _PRESCALER_)

/* 
 * T1RUN: Timer1 System Clock Status bit ( READ ONLY BIT )
 * 1 = Device clock is derived from Timer1 oscillator
 * 0 = Device clock is derived from another source
 */
#define TIMER1_SYSTEM_CLOCK_STATUS()            (T1CONbits.T1RUN)

/* RD16: 16-Bit Read/Write Mode Enable bit */
#define TIMER1_RW_REG_8BIT_MODE_ENABLE()        (T1CONbits.RD16 = 0)
#define TIMER1_RW_REG_16BIT_MODE_ENABLE()       (T1CONbits.RD16 = 1)

/* Data Types Declarations */
typedef struct {
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (*TIMER1_InterruptHandler)(void)     ;
    interrupt_priority_cfg priority           ;
#endif
    uint16 timer1_preload_value               ;
    uint8 timer1_prescaler_value          : 2 ;
    uint8 timer1_mode                     : 1 ;
    uint8 timer1_counter_mode             : 1 ;
    uint8 timer1_osc_cfg                  : 1 ;
    uint8 timer1_reg_rw_mode              : 1 ;
    uint8 timer1_reserved                 : 2 ;
}timer1_t ;

/* Functions Declarations */
Std_ReturnType Timer1_Initialize(const timer1_t *_timer);
Std_ReturnType Timer1_DeInitialize(const timer1_t *_timer);
Std_ReturnType Timer1_Write_value(const timer1_t *_timer , uint16 _value);
Std_ReturnType Timer1_Read_value(const timer1_t *_timer , uint16 *_value);

#endif	/* HAL_TIMER1_H */


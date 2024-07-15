/* 
 * File:   hal_timer3.c
 * Author: Omar Hisham
 *
 * Created on February 25, 2024, 11:44 PM
 */

#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (*TIMER3_InterruptHandler)(void) ;
#endif
    
static uint16 timer3_preload = 0 ;

static inline void Timer3_Mode_Select(const timer3_t *_timer) ;

Std_ReturnType Timer3_Initialize(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER3_MODULE_DISABLE() ;
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value) ;
        Timer3_Mode_Select(_timer) ;
        TMR3H = (uint8)((_timer->timer3_preload_value) >> 8) ;
        TMR3L = (uint8)(_timer->timer3_preload_value) ;
        timer3_preload = _timer->timer3_preload_value ;
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TIMER3_InterruptHandler = _timer->TIMER3_InterruptHandler ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptHighEnable() ;
            TIMER3_HighPrioritySet() ;
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptLowEnable() ;
            TIMER3_LowPrioritySet() ;
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER3_MODULE_ENABLE() ;
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType Timer3_DeInitialize(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER3_MODULE_DISABLE() ;
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER3_InterruptDisable() ;
#endif
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType Timer3_Write_value(const timer3_t *_timer , uint16 _value){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TMR3H = (uint8)((_value) >> 8) ;
        TMR3L = (uint8)(_value) ;
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType Timer3_Read_value(const timer3_t *_timer , uint16 *_value){
    Std_ReturnType ret = E_NOT_OK ;
    uint8 l_tmr3l = 0 , l_tmr3h = 0 ;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK ;
    }
    else{
        l_tmr3l = TMR3L ;
        l_tmr3h = TMR3H ;
        *_value = (uint16)((l_tmr3h << 8) +l_tmr3l) ;
        ret = E_OK ;
    }
    return ret ;
}

static inline void Timer3_Mode_Select(const timer3_t *_timer){
    if(TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE() ;
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE() ;
        if(TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE() ;
        }
        else if(TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE() ;
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

void TIMER3_ISR(void){
    TIMER3_InterruptFlagClear() ;
    TMR3H = (uint8)((timer3_preload) >> 8) ;
    TMR3L = (uint8)(timer3_preload) ;
    if(TIMER3_InterruptHandler){
        TIMER3_InterruptHandler() ;
    }
}

/* 
 * File:   hal_timer0.c
 * Author: Omar Hisham
 *
 * Created on February 18, 2024, 10:25 PM
 */

#include "hal_timer0.h" 

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (*TIMER0_InterruptHandler)(void) ;
#endif

static uint16 timer0_preload = 0 ; 

static inline void Timer0_prescaler_config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size_config(const timer0_t *_timer);

Std_ReturnType Timer0_Initialize(const timer0_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER0_MODULE_DISABLE() ;
        Timer0_prescaler_config(_timer) ;
        Timer0_Mode_Select(_timer) ;
        Timer0_Register_Size_config(_timer) ;
        TMR0H = (uint8)((_timer->timer0_preload_value) >> 8) ;
        TMR0L = (uint8)(_timer->timer0_preload_value) ;
        timer0_preload = _timer->timer0_preload_value ;
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        TIMER0_InterruptHandler = _timer->TIMER0_InterruptHandler ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptHighEnable() ;
            TIMER0_HighPrioritySet() ;
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptLowEnable() ;
            TIMER0_LowPrioritySet() ;
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER0_MODULE_ENABLE() ;
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType Timer0_DeInitialize(const timer0_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER0_MODULE_DISABLE() ;
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER0_InterruptDisable() ;
        #endif
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType Timer0_Write_value(const timer0_t *_timer , uint16 _value){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TMR0H = (uint8)((_value) >> 8) ;
        TMR0L = (uint8)(_value) ;
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType Timer0_Read_value(const timer0_t *_timer , uint16 *_value){
    Std_ReturnType ret = E_NOT_OK ;
    uint8 l_tmrl = 0 , l_tmrh = 0 ;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK ;
    }
    else{
        l_tmrl = TMR0L ;
        l_tmrh = TMR0H ;
        *_value = (uint16)((l_tmrh << 8) +l_tmrl) ;
        ret = E_OK ;
    }
    return ret ;
}

static inline void Timer0_prescaler_config(const timer0_t *_timer){
    if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_ENABLE() ;
        T0CONbits.T0PS = _timer->prescaler_value ;
    }
    else if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
        #define TIMER0_PRESCALER_DISABLE()() ;
    }
    else{ /* Nothing */ }
}

static inline void Timer0_Mode_Select(const timer0_t *_timer){
    if(TIMER0_TIMER_MODE == _timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE() ;
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode){
        TIMER0_COUNTER_MODE_ENABLE() ;
        if(TIMER0_RISING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_RISING_EDGE_ENABLE() ;
        }
        else if(TIMER0_FALLING_EDGE_CFG == _timer->timer0_counter_edge){
            TIMER0_FALLING_EDGE_ENABLE() ;
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static inline void Timer0_Register_Size_config(const timer0_t *_timer){
    if(TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_8BIT_REGIDTER_MODE_ENABLE() ;
    }
    else if(TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_16BIT_REGIDTER_MODE_ENABLE() ;
    }
    else{ /* Nothing */ }
}

void TIMER0_ISR(void){
    TIMER0_InterruptFlagClear() ;
    TMR0H = (uint8)((timer0_preload) >> 8) ;
    TMR0L = (uint8)(timer0_preload) ;
    if(TIMER0_InterruptHandler){
        TIMER0_InterruptHandler() ;
    }
}
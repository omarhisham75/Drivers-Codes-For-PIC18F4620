/* 
 * File:   hal_timer2.c
 * Author: Omar Hisham
 *
 * Created on February 25, 2024, 11:42 PM
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (*TIMER2_InterruptHandler)(void) ;
#endif
    
static uint8 timer2_preload = 0 ;


Std_ReturnType Timer2_Initialize(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER2_MODULE_DISABLE() ;
        TIMER2_PRESCALER_SELECT(_timer->prescaler_value) ;
        TIMER2_POSTSCALER_SELECT(_timer->postscaler_value) ;
        TMR2 = _timer->timer2_preload_value ;
        timer2_preload = _timer->timer2_preload_value ;
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TIMER2_InterruptHandler = _timer->TIMER2_InterruptHandler ;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable() ;
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptHighEnable() ;
            TIMER2_HighPrioritySet() ;
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptLowEnable() ;
            TIMER2_LowPrioritySet() ;
        }
        else{ /* Nothing */ }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        TIMER2_MODULE_ENABLE() ;
        ret = E_OK ;
    }
}

Std_ReturnType Timer2_DeInitialize(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TIMER2_MODULE_DISABLE() ;
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        TIMER2_InterruptDisable() ;
#endif
        ret = E_OK ;
    }
}

Std_ReturnType Timer2_Write_value(const timer2_t *_timer , uint8 _value){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _timer){
        ret = E_NOT_OK ;
    }
    else{
        TMR2 = _value ;
        ret = E_OK ;
    }
}

Std_ReturnType Timer2_Read_value(const timer2_t *_timer , uint8 *_value){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK ;
    }
    else{
        *_value = TMR2 ;
        ret = E_OK ;
    }
}

void TIMER2_ISR(void){
    TIMER2_InterruptFlagClear() ;
    TMR2 = timer2_preload ;
    if(TIMER2_InterruptHandler){
        TIMER2_InterruptHandler() ;
    }
}
/* 
 * File:   mcal_external_interrupt.c
 * Author: HP G3
 *
 * Created on February 5, 2024, 1:24 AM
 */

#include "mcal_external_interrupt.h"

static void (*INT0_InterruptHandler)(void) = NULL ;
static void (*INT1_InterruptHandler)(void) = NULL ;
static void (*INT2_InterruptHandler)(void) = NULL ;

static void (*RB4_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB4_InterruptHandler_LOW)(void) = NULL ;
static void (*RB5_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB5_InterruptHandler_LOW)(void) = NULL ;
static void (*RB6_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB6_InterruptHandler_LOW)(void) = NULL ;
static void (*RB7_InterruptHandler_HIGH)(void) = NULL ;
static void (*RB7_InterruptHandler_LOW)(void) = NULL ;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_NTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_NTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_NTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_NTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_NTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_NTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_NTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

Std_ReturnType Interrupt_NTx_Initialize(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        /* Disable the external interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear interrupt flag : External interrupt didn't occur */
        ret = Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure external interrupt edge */
        ret = Interrupt_INTx_Edge_Init(int_obj);
        /* Configure external interrupt priority */
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif
        /* Configure external interrupt I/O pin */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Configure default interrupt callback */
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the external interrupt */
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret ;
}

void INT0_ISR(void){
    /* Clear the flag */
    EXT_INT0_InterruptFlagClear();
    /* Code */
    
    /* Callback Function */
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
}

void INT1_ISR(void){
    /* Clear the flag */
    EXT_INT1_InterruptFlagClear();
    /* Code */
    
    /* Callback Function */
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
}

void INT2_ISR(void){
    /* Clear the flag */
    EXT_INT2_InterruptFlagClear();
    /* Code */
    
    /* Callback Function */
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
}

void RB4_ISR(uint8 RB_source){
    /* Clear the flag */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback Function */
    if(HIGH == RB_source){
        if(RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH(); }
    }
    else if(LOW == RB_source){
        if(RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW(); }
    }
    else{ /* Nothing */ }

}

void RB5_ISR(uint8 RB_source){
    /* Clear the flag */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback Function */
    if(HIGH == RB_source){
        if(RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH(); }
    }
    else if(LOW == RB_source){
        if(RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW(); }
    }
    else{ /* Nothing */ }

}

void RB6_ISR(uint8 RB_source){
    /* Clear the flag */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback Function */
    if(HIGH == RB_source){
        if(RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH(); }
    }
    else if(LOW == RB_source){
        if(RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW(); }
    }
    else{ /* Nothing */ }

}

void RB7_ISR(uint8 RB_source){
    /* Clear the flag */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    
    /* Callback Function */
    if(HIGH == RB_source){
        if(RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH(); }
    }
    else if(LOW == RB_source){
        if(RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW(); }
    }
    else{ /* Nothing */ }

}

Std_ReturnType Interrupt_NTx_DeInitialize(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret ;
}


Std_ReturnType Interrupt_RBx_Initialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        /* Disable the external interrupt */
        EXT_RBx_InterruptDisable();
        /* Clear interrupt flag : External interrupt didn't occur */
        EXT_RBx_InterruptFlagClear();
        /* Configure external interrupt priority */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_LowPrioritySet();
        }
        else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_HighPrioritySet();
        }
        else {ret = E_NOT_OK ;}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        /* Configure external interrupt I/O pin */
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
        /* Configure default interrupt callback */
        switch(int_obj->mcu_pin.pin){
            case PIN4 :
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH ; 
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW ;
                break ;
            case PIN5 : 
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH ; 
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW ;
                break ;
            case PIN6 : 
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH ; 
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW ;
                break ;
            case PIN7 : 
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH ; 
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW ;
                break ;
            default   : ret = E_NOT_OK ;
        }
        /* Enable the external interrupt */
        EXT_RBx_InterruptEnable();
    }
    return ret ;
}

Std_ReturnType Interrupt_RBx_DeInitialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        
    }
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = E_OK ;
        switch(int_obj->source){
                case INTERRUPT_EXTERNAL_INT0 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_GlobalInterruptHighEnable();
#else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
#endif
                    EXT_INT0_InterruptEnable() ; 
                    break ;
                case INTERRUPT_EXTERNAL_INT1 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(INTERRUPT_LOW_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptLowEnable();}
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptHighEnable();}
                    else {ret = E_NOT_OK ;}
#else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
#endif
                    EXT_INT1_InterruptEnable() ; 
                    break ;
                case INTERRUPT_EXTERNAL_INT2 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(INTERRUPT_LOW_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptLowEnable();}
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){INTERRUPT_GlobalInterruptHighEnable();}
                    else {ret = E_NOT_OK ;}
#else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
#endif
                    EXT_INT2_InterruptEnable() ; 
                    break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Disable(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = E_OK ;
        switch(int_obj->source){
                case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptDisable() ; break ;
                case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptDisable() ; break ;
                case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptDisable() ; break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = E_OK ;
        switch(int_obj->source){
                case INTERRUPT_EXTERNAL_INT1 : 
                    if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT1_LowPrioritySet();}
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_HighPrioritySet();}
                    else {ret = E_NOT_OK ;}
                    break ;
                case INTERRUPT_EXTERNAL_INT2 : 
                    if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INT2_LowPrioritySet();}
                    else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_HighPrioritySet();}
                    else {ret = E_NOT_OK ;}
                    break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}
#endif

static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = E_OK ;
        switch(int_obj->source){
                case INTERRUPT_EXTERNAL_INT0 :
                    if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT0_FallingEdgeSet();}
                    else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT0_RisingEdgeSet();}
                    else {ret = E_NOT_OK ;}
                    break ;
                case INTERRUPT_EXTERNAL_INT1 :
                    if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT1_FallingEdgeSet();}
                    else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT1_RisingEdgeSet();}
                    else {ret = E_NOT_OK ;}
                    break ;
                case INTERRUPT_EXTERNAL_INT2 :
                    if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INT2_FallingEdgeSet();}
                    else if(INTERRUPT_RISING_EDGE == int_obj->edge){EXT_INT2_RisingEdgeSet();}
                    else {ret = E_NOT_OK ;}
                    break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }
    return ret ;
}

static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = E_OK ;
        switch(int_obj->source){
                case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptFlagClear() ; break ;
                case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptFlagClear() ; break ;
                case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptFlagClear() ; break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK ;
    }
    else {
        INT0_InterruptHandler = InterruptHandler ;
        ret = E_OK ;
    }
    return ret ;
}

static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK ;
    }
    else {
        INT1_InterruptHandler = InterruptHandler ;
        ret = E_OK ;
    }
    return ret ;
}

static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == InterruptHandler){
        ret = E_NOT_OK ;
    }
    else {
        INT2_InterruptHandler = InterruptHandler ;
        ret = E_OK ;
    }
    return ret ;
}

static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_NTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == int_obj){
        ret = E_NOT_OK ;
    }
    else {
        ret = E_OK ;
        switch(int_obj->source){
                case INTERRUPT_EXTERNAL_INT0 :
                    ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                    break ;
                case INTERRUPT_EXTERNAL_INT1 :
                    ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                    break ;
                case INTERRUPT_EXTERNAL_INT2 :
                    ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                    break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret ;
}






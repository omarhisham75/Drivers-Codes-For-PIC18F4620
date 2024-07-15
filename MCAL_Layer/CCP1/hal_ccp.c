/* 
 * File:   hal_ccp1.c
 * Author: Omar Hisham
 *
 * Created on February 27, 2024, 8:38 PM
 */

#include "hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (*CCP1_InterruptHandler)(void) ;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    static void (*CCP2_InterruptHandler)(void) ;
#endif
    
static void CCP_Interrupt_Config(const ccp_t *_ccp_obj) ;
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj) ;
static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj) ;
static Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *_ccp_obj) ;
static Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *_ccp_obj) ;

Std_ReturnType CCP_Initialize(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK ;
    }
    else{
        /* CCP Module Disable */
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else { /* Nothing */ }
        
        /* CCP1 Module CAPTURE MODE Initialize */
        if(CCP_CFG_CAPTURE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret = CCP_Capture_Mode_Config(_ccp_obj) ;
        }
        
        /* CCP1 Module COMPARE MODE Initialize */
        else if(CCP_CFG_COMPARE_MODE_SELECTED == _ccp_obj->ccp_mode){
            ret = CCP_Compare_Mode_Config(_ccp_obj) ;
        }
        
        /* CCP1 Module PWM MODE Initialize */
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
        else if(CCP_CFG_PWM_MODE_SELECTED == _ccp_obj->ccp_mode){
            CCP_PWM_Mode_Config(_ccp_obj) ;
        }
        else { /* Nothing */ }
#endif
        /* Pin Configurations */
        ret = gpio_pin_initialize(&(_ccp_obj->ccp_pin));
        /* Interrupt Configurations */
        CCP_Interrupt_Config(_ccp_obj) ;
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType CCP_DeInitialize(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK ;
    }
    else{
        /* CCP1 Module Disable */
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        CCP1_InterruptDisable() ;
#endif
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        CCP2_InterruptDisable() ;
#endif
        }
        else { /* Nothing */ }


        ret = E_OK ;
    }
    return ret ;
}


#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE_SELECTED)
Std_ReturnType CCP_IsCapturedDataReady(uint8 *_capture_status){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _capture_status){
        ret = E_NOT_OK ;
    }
    else{
        if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
            *_capture_status = CCP_CAPTURE_READY ;
            CCP1_InterruptFlagClear();
        }
        else {
            *_capture_status = CCP_CAPTURE_NOT_READY ;
        }
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType CCP_Capture_Mode_Read_Value(uint16 *capture_value){
    Std_ReturnType ret = E_NOT_OK ;
    CCP_REG_T capture_temp_value = { .ccpr_low = 0 , .ccpr_high = 0 } ;
    if(NULL == capture_value){
        ret = E_NOT_OK ;
    }
    else{
        capture_temp_value.ccpr_low = CCPR1L ;
        capture_temp_value.ccpr_high = CCPR1H ;
        *capture_value = capture_temp_value.ccpr_16Bit ;
        ret = E_OK ;
    }
    return ret ;
}

#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE_SELECTED)
Std_ReturnType CCP_IsCompareComplete(uint8 *_compare_status){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _compare_status){
        ret = E_NOT_OK ;
    }
    else{
        if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
            *_compare_status = CCP_COMPARE_READY ;
            CCP1_InterruptFlagClear();
        }
        else {
            *_compare_status = CCP_COMPARE_NOT_READY ;
        }
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj , uint16 compare_value){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK ;
    }
    else{
        CCP_REG_T Compare_temp_value = { .ccpr_low = 0 , .ccpr_high = 0 } ;
        Compare_temp_value.ccpr_16Bit = compare_value ;
        if(CCP1_INST == _ccp_obj->ccp_inst){
                CCPR1L = Compare_temp_value.ccpr_low ;
                CCPR1H = Compare_temp_value.ccpr_high ;
            }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
                CCPR2L = Compare_temp_value.ccpr_low ;
                CCPR2H = Compare_temp_value.ccpr_high ;
        }
        else { /* Nothing */ }
        ret = E_OK ;
    }  
     
    return ret ;
}

#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj , const uint8 _duty){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK ;
    }
    else{
        uint16 l_duty = (uint16)(((float)PR2 + 1) * (float)4 * ((float)_duty / (float)100)) ;
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.DC1B = (uint8)(l_duty & 0x0003) ;
            CCPR1L = (uint8)(l_duty >> 2) ;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B = (uint8)(l_duty & 0x0003) ;
            CCPR2L = (uint8)(l_duty >> 2) ;
        }
        else { /* Nothing */ }
        ret = E_OK ;
    } 
    return ret ;
}

Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK ;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_PWM_MODE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
        else { /* Nothing */ }
    }
    ret = E_OK ; 
    return ret ;
}

Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _ccp_obj){
        ret = E_NOT_OK ;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1_SET_MODE(CCP_MODULE_DISABLE);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2_SET_MODE(CCP_MODULE_DISABLE);
        }
        else { /* Nothing */ }
    }
    ret = E_OK ; 
    return ret ;
}

#endif

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj){
/* CCP1 Interrupt Configurations */
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP1_InterruptEnable();
    CCP1_InterruptFlagClear();
    CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP1_priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        CCP1_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP1_priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        CCP1_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
#endif

/* CCP2 Interrupt Configurations */
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP2_InterruptEnable();
    CCP2_InterruptFlagClear();
    CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP2_priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        CCP2_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP2_priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        CCP2_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
}

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj){
    if(CCP1_INST == _ccp_obj->ccp_inst){
        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
            CCP1_SET_MODE(CCP_PWM_MODE);
        }
        else { /* Nothing */ }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
            CCP2_SET_MODE(CCP_PWM_MODE);
        }
        else { /* Nothing */ }
    }
    else { /* Nothing */ }
            
    /* PWM Frequency Initialization */
    PR2 = (uint8)(((float)_XTAL_FREQ / ((float)_ccp_obj->PWM_Frequency * 4.0 * 
           (float)_ccp_obj->postscaler_value * (float)_ccp_obj->prescaler_value)) - 1);
}
#endif

static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj){
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{ /* Nothing */ }
}

static Std_ReturnType CCP_Capture_Mode_Config(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_OK;

    if(CCP1_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        /* CCP2 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }

    CCP_Mode_Timer_Select(_ccp_obj);

    return ret;
}

static Std_ReturnType CCP_Compare_Mode_Config(const ccp_t *_ccp_obj){
    Std_ReturnType ret = E_OK;

    if(CCP1_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp_mode_variant){
            case CCP_COMPARE_MODE_SET_PIN_LOW      : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);      break;
            case CCP_COMPARE_MODE_SET_PIN_HIGH     : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);     break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH  : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);  break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
            case CCP_COMPARE_MODE_GEN_EVENT        : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
            default : ret = E_NOT_OK; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }

    CCP_Mode_Timer_Select(_ccp_obj);

    return ret;
}

void CCP1_ISR(void){
    CCP1_InterruptFlagClear();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
    else{ /* Nothing */ }
}

void CCP2_ISR(void){
    CCP2_InterruptFlagClear();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
    else{ /* Nothing */ }
}
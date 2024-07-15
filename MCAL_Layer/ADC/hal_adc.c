/* 
 * File:   hal_adc.c
 * Author: Omar Hisham
 *
 * Created on February 13, 2024, 2:15 AM
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*ADC_InterruptHandler)(void) = NULL ;
#endif

static inline void adc_input_channel_pin_configuration(adc_channel_select_t channel);
static inline void select_reselt_format(const adc_config_t *_adc);
static inline void configure_voltage_reference(const adc_config_t *_adc);

Std_ReturnType ADC_Initialize(const adc_config_t *_adc){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _adc){
        ret = E_NOT_OK ;
    }
    else {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE() ;
        /* Configure the acquisition time */
        ADCON2bits.ACQT = _adc->acquisition_time ;
        /* Configure the conversion clock */
        ADCON2bits.ADCS = _adc->conversion_clock ;
        /* Configure the default channel */
        ADCON0bits.CHS = _adc->adc_channel ;
        adc_input_channel_pin_configuration(_adc->adc_channel) ;
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == _adc->periority){ 
            INTERRUPT_GlobalInterruptHighEnable() ;
            ADC_HighPrioritySet(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == _adc->periority){ 
            INTERRUPT_GlobalInterruptLowEnable() ;
            ADC_LowPrioritySet(); 
        }
        else { /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ADC_InterruptHandler = _adc->ADC_InterruptHandler ;
#endif
        /* Configure the result format */
        select_reselt_format(_adc);
        /* Configure the voltage reference */
        configure_voltage_reference(_adc);
        /* Enable the ADC */
        ADC_CONVERTER_ENABLE() ;
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType ADC_DeInitialize(const adc_config_t *_adc){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _adc){
        ret = E_NOT_OK ;
    }
    else {
        /* Disable the ADC */
        ADC_CONVERTER_DISABLE() ;
        /* Disable the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
        ADC_InterruptDisable() ;
#endif
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType ADC_Select_Channel(const adc_config_t *_adc , adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _adc){
        ret = E_NOT_OK ;
    }
    else {
        /* Configure the default channel */
        ADCON0bits.CHS = channel ;
        adc_input_channel_pin_configuration(channel) ;
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType ADC_Start_Conversion(const adc_config_t *_adc){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _adc){
        ret = E_NOT_OK ;
    }
    else {
        ADC_START_CONVERSION();
        ret = E_OK ;
    }
    return ret ;
}
/**
 * 
 * @param _adc
 * @param conversion_status 
 *          true if conversion is complete 
 *          false if conversion is not complete 
 * @return 
 */
Std_ReturnType ADC_IS_Conversion_Done(const adc_config_t *_adc , uint8 *conversion_status){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL == _adc) || (NULL == conversion_status)){
        ret = E_NOT_OK ;
    }
    else {
        *conversion_status = (uint8)(!(ADC_CONVERSION_STATUS()));
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType ADC_Get_Conversion_Result(const adc_config_t *_adc , adc_result_t *conversion_result){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL == _adc) || (NULL == conversion_result)){
        ret = E_NOT_OK ;
    }
    else {
        if(ADC_RESULT_RIGHT == _adc->result_format){
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->result_format){
            *conversion_result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        ret = E_OK ;
    }
    return ret ;
}

Std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t *_adc , adc_channel_select_t channel , 
                                  adc_result_t *conversion_result){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL == _adc) || (NULL == conversion_result)){
        ret = E_NOT_OK ;
    }
    else {
        /* Select A/D channel */
        ret = ADC_Select_Channel(_adc , channel) ;
        /* Start the conversion */
        ret = ADC_Start_Conversion(_adc) ;
        /* Wait till conversion is completed */
        while(ADC_CONVERSION_STATUS());
        ret = ADC_Get_Conversion_Result(_adc , conversion_result);
    }
    return ret ;
}

Std_ReturnType ADC_Start_Conversion_Interrupt(const adc_config_t *_adc , adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == _adc){
        ret = E_NOT_OK ;
    }
    else {
        /* Select A/D channel */
        ret = ADC_Select_Channel(_adc , channel) ;
        /* Start the conversion */
        ret = ADC_Start_Conversion(_adc) ;
    }
    return ret ;
}

static inline void adc_input_channel_pin_configuration(adc_channel_select_t channel){
    switch (channel){
        case ADC_CHANNEL_AN0  : Set_Bit(TRISA , _TRISA_RA0_POSN) ; break ;
        case ADC_CHANNEL_AN1  : Set_Bit(TRISA , _TRISA_RA1_POSN) ; break ;
        case ADC_CHANNEL_AN2  : Set_Bit(TRISA , _TRISA_RA2_POSN) ; break ;
        case ADC_CHANNEL_AN3  : Set_Bit(TRISA , _TRISA_RA3_POSN) ; break ;
        case ADC_CHANNEL_AN4  : Set_Bit(TRISA , _TRISA_RA5_POSN) ; break ;
        case ADC_CHANNEL_AN5  : Set_Bit(TRISE , _TRISE_RE0_POSN) ; break ;
        case ADC_CHANNEL_AN6  : Set_Bit(TRISE , _TRISE_RE1_POSN) ; break ;
        case ADC_CHANNEL_AN7  : Set_Bit(TRISE , _TRISE_RE2_POSN) ; break ;
        case ADC_CHANNEL_AN8  : Set_Bit(TRISB , _TRISB_RB2_POSN) ; break ;
        case ADC_CHANNEL_AN9  : Set_Bit(TRISB , _TRISB_RB3_POSN) ; break ;
        case ADC_CHANNEL_AN10 : Set_Bit(TRISB , _TRISB_RB1_POSN) ; break ;
        case ADC_CHANNEL_AN11 : Set_Bit(TRISB , _TRISB_RB4_POSN) ; break ;
        case ADC_CHANNEL_AN12 : Set_Bit(TRISB , _TRISB_RB0_POSN) ; break ;
        default : /* Nothing */ ;
    }
}

static inline void select_reselt_format(const adc_config_t *_adc){
    if(ADC_RESULT_RIGHT == _adc->result_format){ ADC_RESULT_RIGHT_FORMAT(); }
    else if(ADC_RESULT_LEFT == _adc->result_format){ ADC_RESULT_LEFT_FORMAT(); }
    else{ ADC_RESULT_RIGHT_FORMAT(); }
}

static inline void configure_voltage_reference(const adc_config_t *_adc){
    if(ADC_VOLTAGE_REFERENCE_ENABLE == _adc->voltage_reference){ ADC_ENABLE_VOLTAGE_REFERENCE(); }
    else if(ADC_VOLTAGE_REFERENCE_DISABLE == _adc->voltage_reference){ ADC_DISABLE_VOLTAGE_REFERENCE(); }
    else{ ADC_DISABLE_VOLTAGE_REFERENCE(); }
}

void ADC_ISR(void){
    ADC_InterruptFlagClear() ;
    if(ADC_InterruptHandler){
        ADC_InterruptHandler() ;
    }
}
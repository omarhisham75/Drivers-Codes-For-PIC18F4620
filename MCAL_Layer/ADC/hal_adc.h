/* 
 * File:   hal_adc.h
 * Author: Omar Hisham
 *
 * Created on February 13, 2024, 2:15 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Includes Section */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "hal_adc_cfg.h"

/* Macros Section */
/* A/D Port Configuration Control bits
 * ADC_AN4_ANALOG_FUNCTIONALITY means AN4 , AN3 , AN2 , AN1 , AN0 @ALL are Analog
 */
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x01

#define ADC_RESULT_RIGHT                0x01U
#define ADC_RESULT_LEFT                 0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLE    0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLE   0x00U

#define ADC_CONVERSION_COMPLETED        0x01U
#define ADC_CONVERSION_INPROGRESS       0x00U

/* Macro Functions Section */
/* A/D Conversion Status bit : A/D conversion in progress -> 1 / A/D Idle -> 0 */
#define ADC_CONVERSION_STATUS()     (ADCON0bits.GODONE)
/* Start ADC conversion */
#define ADC_START_CONVERSION()      (ADCON0bits.GODONE = 1)

/* A/D Converter module is enabled */
#define ADC_CONVERTER_ENABLE()      (ADCON0bits.ADON = 1)
/* A/D Converter module is disabled */
#define ADC_CONVERTER_DISABLE()     (ADCON0bits.ADON = 0)

/* Voltage reference is Vref+ & Vref- */
#define ADC_ENABLE_VOLTAGE_REFERENCE() do{ ADCON1bits.VCFG1 = 1 ;\
                                           ADCON1bits.VCFG0 = 1 ;\
                                          }while(0)
/* Voltage reference is Vss & Vdd */
#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ ADCON1bits.VCFG1 = 0 ;\
                                            ADCON1bits.VCFG0 = 0 ;\
                                          }while(0)

/* A/D Port Configuration Control 
 * ADC_AN4_ANALOG_FUNCTIONALITY means AN4 , AN3 , AN2 , AN1 , AN0 @ALL are Analog
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)     (ADCON1bits.PCFG = _CONFIG)

/* ADFM: A/D Result Format Select bit */
#define ADC_RESULT_RIGHT_FORMAT()   (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON2bits.ADFM = 1)

/* Data Types Declarations */
/* CHS3:CHS0: Analog Channel Select bits */
typedef enum {
    ADC_CHANNEL_AN0 = 0 ,
    ADC_CHANNEL_AN1 ,
    ADC_CHANNEL_AN2 ,
    ADC_CHANNEL_AN3 ,
    ADC_CHANNEL_AN4 ,
    ADC_CHANNEL_AN5 ,
    ADC_CHANNEL_AN6 ,
    ADC_CHANNEL_AN7 ,
    ADC_CHANNEL_AN8 ,
    ADC_CHANNEL_AN9 ,
    ADC_CHANNEL_AN10 ,
    ADC_CHANNEL_AN11 ,
    ADC_CHANNEL_AN12 
}adc_channel_select_t;

/* ACQT2:ACQT0: A/D Acquisition Time Select bits */
typedef enum {
    ADC_0_TAD = 0 ,
    ADC_2_TAD ,
    ADC_4_TAD ,
    ADC_6_TAD ,
    ADC_8_TAD ,
    ADC_12_TAD ,
    ADC_16_TAD ,
    ADC_20_TAD 
}adc_acquisition_time_t ;

/* ADCS2:ADCS0: A/D Conversion Clock Select bits */
typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16 ,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64 ,
}adc_conversion_clock_t; 

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void (*ADC_InterruptHandler)(void) ;
    interrupt_priority_cfg periority ;
#endif
    adc_acquisition_time_t acquisition_time ; /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t conversion_clock ; /* @ref adc_conversion_clock_t */
    adc_channel_select_t adc_channel ;        /* @ref adc_channel_select_t */
    uint8 voltage_reference : 1 ;             /* @ref voltage reference configuration */
    uint8 result_format     : 1 ;             /* @ref A/D result format select */
    uint8 ADC_reserved      : 6 ;
}adc_config_t;

typedef uint16 adc_result_t ;

/* Functions Declarations */
Std_ReturnType ADC_Initialize(const adc_config_t *_adc);
Std_ReturnType ADC_DeInitialize(const adc_config_t *_adc);
Std_ReturnType ADC_Select_Channel(const adc_config_t *_adc , adc_channel_select_t channel);
Std_ReturnType ADC_Start_Conversion(const adc_config_t *_adc);
Std_ReturnType ADC_IS_Conversion_Done(const adc_config_t *_adc , uint8 *conversion_status);
Std_ReturnType ADC_Get_Conversion_Result(const adc_config_t *_adc , adc_result_t *conversion_result);
Std_ReturnType ADC_Get_Conversion_Blocking(const adc_config_t *_adc , adc_channel_select_t channel , 
                                  adc_result_t *conversion_result);
Std_ReturnType ADC_Start_Conversion_Interrupt(const adc_config_t *_adc , adc_channel_select_t channel);

#endif	/* HAL_ADC_H */


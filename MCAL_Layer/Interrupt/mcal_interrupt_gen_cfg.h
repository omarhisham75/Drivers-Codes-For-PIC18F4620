/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: HP G3
 *
 * Created on February 5, 2024, 2:11 AM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

/* Includes Section */

/* Macros Section */
#define INTERRUPT_FEATURE_ENABLE                    1U
//#define INTERRUPT_PRIORITY_LEVELS_ENABLE            INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_FEATURE_INTx_ENABLE      INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_FEATURE_OnChange_ENABLE  INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define EUSART_TX_INTERRUPT_FEATURE_ENABLE          INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_FEATURE_ENABLE          INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE               INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE

/* Macro Functions Section */

/* Data Types Declarations */

/* Functions Declarations */

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */


/* 
 * File:   mcal_interrupt_manager.h
 * Author: HP G3
 *
 * Created on February 5, 2024, 1:21 AM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Includes Section */
#include "mcal_interrupt_config.h"

/* Macros Section */

/* Macro Functions Section */

/* Data Types Declarations */

/* Functions Declarations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB_source);
void RB5_ISR(uint8 RB_source);
void RB6_ISR(uint8 RB_source);
void RB7_ISR(uint8 RB_source);

void ADC_ISR(void);

void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);

void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);


#endif	/* MCAL_INTERRUPT_MANAGER_H */


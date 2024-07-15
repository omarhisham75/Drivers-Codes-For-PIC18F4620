/* 
 * File:   mcal_interrupt_manager.c
 * Author: HP G3
 *
 * Created on February 5, 2024, 1:21 AM
 */

#include "mcal_interrupt_manager.h"

uint8 RB4_flag = 1 , RB5_flag = 1 , RB6_flag = 1 , RB7_flag = 1 ;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else { /* Nothing */ }
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else { /* Nothing */ }
}

#else
void __interrupt() InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (HIGH == PORTBbits.RB4) && (RB4_flag == 1)){
        RB4_flag = 0 ;
        RB4_ISR(HIGH);
    }
    else { /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (LOW == PORTBbits.RB4) && (RB4_flag == 0)){
        RB4_flag = 1 ;
        RB4_ISR(LOW);
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (HIGH == PORTBbits.RB5) && (RB5_flag == 1)){
        RB5_flag = 0 ;
        RB5_ISR(HIGH);
    }
    else { /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (LOW == PORTBbits.RB5) && (RB5_flag == 0)){
        RB5_flag = 1 ;
        RB5_ISR(LOW);
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (HIGH == PORTBbits.RB6) && (RB6_flag == 1)){
        RB6_flag = 0 ;
        RB6_ISR(HIGH);
    }
    else { /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (LOW == PORTBbits.RB6) && (RB6_flag == 0)){
        RB6_flag = 1 ;
        RB6_ISR(LOW);
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (HIGH == PORTBbits.RB7) && (RB7_flag == 1)){
        RB7_flag = 0 ;
        RB7_ISR(HIGH);
    }
    else { /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && 
       (LOW == PORTBbits.RB7) && (RB7_flag == 0)){
        RB7_flag = 1 ;
        RB7_ISR(LOW);
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        TIMER0_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
        TIMER1_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
        TIMER2_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
        TIMER3_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
        MSSP_I2C_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF)){
        MSSP_I2C_BC_ISR();
    }
    else { /* Nothing */ }
}

#endif
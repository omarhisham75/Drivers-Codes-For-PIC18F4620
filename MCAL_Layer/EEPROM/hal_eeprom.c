/* 
 * File:   hal_eeprom.c
 * Author: Omar Hisham
 *
 * Created on February 9, 2024, 2:13 AM
 */

#include "hal_eeprom.h"

Std_ReturnType Data_EEPROM_WriteByte(uint16 Address , uint8 Data ){
    Std_ReturnType ret = E_OK ; 
    
    /* Read the interrupt status "Enabled or Disabled" */
    uint8 General_Interrupt_Status = INTCONbits.GIE ;
    
    /* Update the address registers */
    EEADRH = (uint8)((Address >> 8) & 0x03) ;
    EEADR  = (uint8)(Address & 0xFF) ;
    
    /* Update the data register */
    EEDATA = Data ;
    
    /* Select access data EEPROM memory */
    EECON1bits.EEPGD = Access_data_EEPROM_memory ;
    EECON1bits.CFGS  = Access_Flash_program_or_data_EEPROM_memory ;
    
    /* Allows write cycles to flash program / data EEPROM */
    EECON1bits.WREN = Allows_write_cycles_to_Flash_program_data_EEPROM ;
    
    /* Disable all interrupts "general interrupts" */
    INTCONbits.GIE = 0 ;
    
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55 ;
    EECON2 = 0xAA ;
    
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = Initiates_a_data_EEPROM_erase_write_cycle ;
    
    /* wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to flash program / data EEPROM */
    EECON1bits.WREN = Access_Flash_program_or_data_EEPROM_memory ;
    
    /* Restore the interrupt status "Enabled or Disabled" */
    INTCONbits.GIE = General_Interrupt_Status ;
    
    return ret ;
}
Std_ReturnType Data_EEPROM_ReadByte(uint16 Address , uint8 *Data ){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == Data){
        ret = E_NOT_OK ;
    }
    else{
        /* Update the address register */
        EEADRH = (uint8)((Address >> 8) & 0x03) ;
        EEADR  = (uint8)(Address & 0xFF) ;
        
        /* Select access data EEPROM memory */
        EECON1bits.EEPGD = Access_data_EEPROM_memory ;
        EECON1bits.CFGS  = Access_Flash_program_or_data_EEPROM_memory ;
        
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = Initiates_an_EEPROM_read ;
        NOP();
        NOP();
        
        /* Return data */
        *Data = EEDATA ;
        
        ret = E_OK ; 
    }
    return ret ;
}
/* 
 * File:   hal_eeprom.h
 * Author: Omar Hisham
 *
 * Created on February 9, 2024, 2:13 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Includes Section */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Macros Section */
/* EEPGD: Flash Program or Data EEPROM Memory Select bit */
#define Access_data_EEPROM_memory                                           0 
#define Access_Flash_program_memory                                         1
/* CFGS: Flash Program/Data EEPROM or Configuration Select bit */
#define Access_Flash_program_or_data_EEPROM_memory                          0 
#define Access_Configuration_registers                                      1
/* WREN: Flash Program/Data EEPROM Write Enable bit */
#define Access_Flash_program_or_data_EEPROM_memory                          0 
#define Allows_write_cycles_to_Flash_program_data_EEPROM                    1
/* WR: Write Control bit */
/* (The operation is self-timed and the bit is cleared by hardware once write is complete. 
 * The WR bit can only be set (not cleared) in software.) */
#define Initiates_a_data_EEPROM_erase_write_cycle                           1
/* RD: Read Control bit */
/* (Read takes one cycle. RD is cleared in hardware. The RD bit can only
be set (not cleared) in software. RD bit cannot be set when EEPGD = 1 or CFGS = 1.) */
#define Does_not_initiate_an_EEPROM_read                                    0 
#define Initiates_an_EEPROM_read                                            1

/* Macro Functions Section */

/* Data Types Declarations */

/* Functions Declarations */
Std_ReturnType Data_EEPROM_WriteByte(uint16 Address , uint8 Data );
Std_ReturnType Data_EEPROM_ReadByte(uint16 Address , uint8 *Data );

#endif	/* HAL_EEPROM_H */


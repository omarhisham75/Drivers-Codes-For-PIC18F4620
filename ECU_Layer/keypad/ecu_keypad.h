/* 
 * File:   ecu_keypad.h
 * Author: Omar Hisham
 *
 * Created on January 25, 2024, 9:55 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Includes Section */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Macros Section */
#define ECU_KEYPAD_ROWS     4
#define ECU_KEYPAD_COLUMNS  4

/* Macro Functions Section */

/* Data Types Declarations */
typedef struct {
    pin_config_t keypad_rows_pin[ECU_KEYPAD_ROWS] ;
    pin_config_t keypad_columns_pin[ECU_KEYPAD_COLUMNS] ;
}keypad_t;

/* Functions Declarations */
Std_ReturnType keypad_initialize(const keypad_t *keypad);
Std_ReturnType keypad_get_value(const keypad_t *keypad , uint8 *value);

#endif	/* ECU_KEYPAD_H */


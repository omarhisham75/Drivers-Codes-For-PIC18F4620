/* 
 * File:   ecu_keypad.c
 * Author: Omar Hisham
 *
 * Created on January 25, 2024, 9:55 PM
 */

#include "ecu_keypad.h"

const static uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                                        {'7' , '8' , '9' , '/'},
                                                                        {'4' , '5' , '6' , '*'},
                                                                        {'1' , '2' , '3' , '-'},
                                                                        {'#' , '0' , '=' , '+'}
                                                                      };

Std_ReturnType keypad_initialize(const keypad_t *keypad){
    Std_ReturnType ret = E_NOT_OK ;
    uint8 Rows_counter = 0 , Columns_counter = 0 ;
    if(NULL == keypad){
        ret = E_NOT_OK ;
    }
    else{
        for(Rows_counter = 0 ; Rows_counter < ECU_KEYPAD_ROWS ; Rows_counter++){
            ret = gpio_pin_initialize(&(keypad->keypad_rows_pin[Rows_counter]));
        }
        for(Columns_counter = 0 ; Columns_counter < ECU_KEYPAD_COLUMNS ; Columns_counter++){
            ret = gpio_pin_direction_initialize(&(keypad->keypad_columns_pin[Columns_counter]));
        }
    }
    return ret;
}
Std_ReturnType keypad_get_value(const keypad_t *keypad , uint8 *value){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL == keypad) || (NULL == value)){
        ret = E_NOT_OK ;
    }
    else{
        uint8 Rows_counter = 0 , Columns_counter = 0 , R_counter = 0 ;
        uint8 Column_logic = 0 ; 
        for(Rows_counter = 0 ; Rows_counter < ECU_KEYPAD_ROWS ; Rows_counter++){
            for(R_counter = 0 ; R_counter < ECU_KEYPAD_ROWS ; R_counter++){
                ret = gpio_pin_write_logic(&(keypad->keypad_rows_pin[R_counter]) , LOW);
            }
            ret = gpio_pin_write_logic(&(keypad->keypad_rows_pin[Rows_counter]) , HIGH);
            for(Columns_counter = 0 ; Columns_counter < ECU_KEYPAD_COLUMNS ; Columns_counter++){
                ret = gpio_pin_read_logic(&(keypad->keypad_columns_pin[Columns_counter]) , &Column_logic);
                if(HIGH == Column_logic){
                    *value = btn_values[Rows_counter][Columns_counter];
                }
            }
        }
    }
    return ret;
}


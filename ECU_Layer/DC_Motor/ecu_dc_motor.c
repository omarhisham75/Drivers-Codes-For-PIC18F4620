/* 
 * File:   ecu_dc_motor.c
 * Author: Omar Hisham
 *
 * Created on January 24, 2024, 9:09 PM
 */

#include "ecu_dc_motor.h"

Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == dc_motor){
        ret = E_OK ;
    }
    else{
        ret = gpio_pin_initialize(&(dc_motor->dc_motor_pin[0]));
        ret = gpio_pin_initialize(&(dc_motor->dc_motor_pin[1]));
        }
    return ret;
}
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == dc_motor){
        ret = E_OK ;
    }
    else{
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]) , HIGH);
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]) , LOW);
    }
    return ret;
}

Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == dc_motor){
        ret = E_OK ;
    }
    else{
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]) , LOW);
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]) , HIGH);
    }
    return ret;
}

Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == dc_motor){
        ret = E_OK ;
    }
    else{
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor_pin[0]) , LOW);
        ret = gpio_pin_write_logic(&(dc_motor->dc_motor_pin[1]) , LOW);
    }
    return ret;
}


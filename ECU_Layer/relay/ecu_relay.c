/* 
 * File:   ecu_relay.c
 * Author: Omar Hisham
 *
 * Created on January 24, 2024, 6:56 PM
 */

#include "ecu_relay.h"

Std_ReturnType relay_initialize(const relay_t* relay){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == relay){
        ret = E_NOT_OK ;
    }
    else {
        pin_config_t pin = {.port = relay->port ,.pin = relay->pin ,
                            .direction = OUTPUT ,.logic = relay->relay_status };
        ret = gpio_pin_initialize(&pin);
    }
    return ret;
}

Std_ReturnType relay_turn_on(const relay_t* relay){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == relay){
        ret = E_NOT_OK ;
    }
    else {
        pin_config_t pin = {.port = relay->port ,.pin = relay->pin ,
                            .direction = OUTPUT ,.logic = relay->relay_status };
        ret = gpio_pin_write_logic(&pin , HIGH);
    }
    return ret;
}

Std_ReturnType relay_turn_off(const relay_t* relay){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == relay){
        ret = E_NOT_OK ;
    }
    else {
        pin_config_t pin = {.port = relay->port ,.pin = relay->pin ,
                            .direction = OUTPUT ,.logic = relay->relay_status };
        ret = gpio_pin_write_logic(&pin , LOW);
    }
    return ret;
}
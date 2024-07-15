/* 
 * File:   ecu_led.c
 * Author: Omar Hisham
 *
 * Created on January 20, 2024, 3:57 AM
 */

#include "ecu_led.h"

Std_ReturnType led_initialize(led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led){
        ret = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {.port = led->port , .pin = led->pin , 
                                .direction = OUTPUT , .logic = led->led_status };
        ret = gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

Std_ReturnType led_turn_off(led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led){
        ret = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {.port = led->port , .pin = led->pin , 
                                .direction = OUTPUT , .logic = led->led_status };
        ret = gpio_pin_write_logic(&pin_obj , LOW);  
    }
    return ret;
}

Std_ReturnType led_turn_on(led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led){
        ret = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {.port = led->port , .pin = led->pin , 
                                .direction = OUTPUT , .logic = led->led_status };
        ret = gpio_pin_write_logic(&pin_obj , HIGH); 
    }
    return ret;
}

Std_ReturnType led_toggle(led_t *led){
    Std_ReturnType ret = E_OK ;
    if(NULL == led){
        ret = E_NOT_OK ;
    }
    else{
        pin_config_t pin_obj = {.port = led->port , .pin = led->pin , 
                                .direction = OUTPUT , .logic = led->led_status };
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}

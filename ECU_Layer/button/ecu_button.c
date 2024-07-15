/* 
 * File:   ecu_button.c
 * Author: Omar Hisham
 *
 * Created on January 24, 2024, 1:16 AM
 */

#include "ecu_button.h"

Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret ;
    if(NULL == btn){
        ret = E_NOT_OK ;
    }
    else{
        ret = gpio_pin_direction_initialize(&btn->button);
    }
    return ret ;
}
Std_ReturnType button_read_state(const button_t *btn,button_state_t *btn_state){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL == btn) || (NULL == btn_state)){
        ret = E_NOT_OK ;
    }
    else{
        logic_t logic = LOW ;
        ret = gpio_pin_read_logic(&(btn->button) , &logic);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(HIGH == logic){
                *btn_state = BUTTON_PRESSED ;
            }
            else{
                *btn_state = BUTTON_RELEASED ;
            }
        }
        else if ((BUTTON_ACTIVE_LOW == btn->button_connection)){
            if(HIGH == logic){
                *btn_state = BUTTON_RELEASED ;
            }
            else{
                *btn_state = BUTTON_PRESSED ;
            }
        }
        else {
            ret = E_NOT_OK ;
        }
        ret = E_OK ;
    }
    return ret ;
}
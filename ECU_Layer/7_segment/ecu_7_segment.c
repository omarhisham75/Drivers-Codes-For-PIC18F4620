/* 
 * File:   ecu_7_segment.c
 * Author: Omar Hisham
 *
 * Created on January 25, 2024, 5:26 PM
 */

#include "ecu_7_segment.h"

Std_ReturnType seven_segment_initialze(const segment_t *seg){
    Std_ReturnType ret = E_NOT_OK ;
    if(NULL == seg){
        ret = E_NOT_OK ;
    }
    else {
        ret = gpio_pin_initialize(&(seg->segment_pins[0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[3]));
    }
    return ret ;
}

Std_ReturnType seven_segment_write_number(const segment_t *seg , uint8 number){
    Std_ReturnType ret = E_NOT_OK ;
    if((NULL == seg) || (9 < number)){
        ret = E_NOT_OK ;
    }
    else {
        ret = gpio_pin_write_logic(&(seg->segment_pins[0]) , number & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[1]) , (number >> 1 ) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[2]) , (number >> 2 ) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[3]) , (number >> 3 ) & 0x01);
    }
    return ret ;
}

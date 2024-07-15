/* 
 * File:   ecu_led.h
 * Author: Omar Hisham
 *
 * Created on January 20, 2024, 3:57 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Includes Section */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Macros Section */

/* Macro Functions Section */

/* Data Types Declarations */
typedef enum {
    LED_OFF = 0,
    LED_ON
}led_status;

typedef struct {
    uint8 port       : 4 ;
    uint8 pin        : 3 ;
    uint8 led_status : 1 ;
}led_t;

/* Functions Declarations */
Std_ReturnType led_initialize(led_t *led);
Std_ReturnType led_turn_off(led_t *led);
Std_ReturnType led_turn_on(led_t *led);
Std_ReturnType led_toggle(led_t *led);

#endif	/* ECU_LED_H */


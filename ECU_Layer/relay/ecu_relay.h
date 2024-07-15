/* 
 * File:   ecu_relay.h
 * Author: Omar Hisham
 *
 * Created on January 24, 2024, 6:56 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Includes Section */
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Macros Section */

/* Macro Functions Section */

/* Data Types Declarations */
typedef enum {
    RELAY_OFF =0 ,
    RELAY_ON 
}relay_status_t;

typedef struct {
    uint8 port                  : 4 ;
    uint8 pin                   : 3 ;
    uint8 relay_status          : 1 ; 
}relay_t ;


/* Functions Declarations */
Std_ReturnType relay_initialize(const relay_t* relay);
Std_ReturnType relay_turn_on(const relay_t* relay);
Std_ReturnType relay_turn_off(const relay_t* relay);

#endif	/* ECU_RELAY_H */


/* 
 * File:   ecu_dc_motor.h
 * Author: Omar Hisham
 *
 * Created on January 24, 2024, 9:09 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Includes Section */
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Macros Section */

/* Macro Functions Section */

/* Data Types Declarations */
typedef enum {
    DC_MOTOR_OFF =0 ,
    DC_MOTOR_ON 
}dc_motor_status_t;

typedef struct {
    pin_config_t dc_motor_pin[2];
}dc_motor_t ;

/* Functions Declarations */
Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor);


#endif	/* ECU_DC_MOTOR_H */


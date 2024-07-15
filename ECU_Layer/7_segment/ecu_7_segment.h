/* 
 * File:   ecu_7_segment.h
 * Author: Omar Hisham
 *
 * Created on January 25, 2024, 5:26 PM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/* Includes Section */
#include "ecu_7_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Macros Section */

/* Macro Functions Section */

/* Data Types Declarations */
typedef enum {
    SEGMENT_COMMON_ANODE ,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct {
    pin_config_t segment_pins[4] ;
    segment_type_t segment_type ;
}segment_t ;

/* Functions Declarations */
Std_ReturnType seven_segment_initialze(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg , uint8 number);

#endif	/* ECU_7_SEGMENT_H */


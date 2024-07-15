/* 
 * File:   hal_gpio.h
 * Author: Omar Hisham
 *
 * Created on January 20, 2024, 3:38 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Includes Section */
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/* Macros Section */
#define BIT_MASK (uint8)1
#define PORT_PIN_MAX_NUMBER             8
#define PORT_MAX_NUMBER                 5
#define PORT_MASK                       0xFF


/* Macro Functions Section */
#define HWREG8(_x)                      (*((volatile unsigned char *)(_x)))

#define Set_Bit(REG,Bit_Position)       (REG|=(BIT_MASK<<Bit_Position))
#define Clear_Bit(REG,Bit_Position)     (REG&=~(BIT_MASK<<Bit_Position))
#define Toggle_Bit(REG,Bit_Position)    (REG^=(BIT_MASK<<Bit_Position))
#define READ_BIT(REG,Bit_Position)      ((REG>>Bit_Position)&BIT_MASK)

/* Data Types Declarations */
typedef enum {
    LOW=0,
    HIGH        
}logic_t;

typedef enum {
    OUTPUT=0,
    INPUT        
}direction_t;

typedef enum {
    PIN0=0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}pin_index_t;

typedef enum {
    PORTA_INDEEX = 0,
    PORTB_INDEEX,
    PORTC_INDEEX,
    PORTD_INDEEX,
    PORTE_INDEEX
}port_index_t;

typedef struct {
    uint8 port       :3 ;
    uint8 pin        :3 ;
    uint8 direction  :1 ;
    uint8 logic      :1 ;
}pin_config_t;

/* Functions Declarations */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config , direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config , logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config , logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config);

Std_ReturnType gpio_port_direction_initialize(const port_index_t port , direction_t direction);
Std_ReturnType gpio_port_get_direction_status(const port_index_t port , direction_t *direction_status);
Std_ReturnType gpio_port_write_logic(const port_index_t port , logic_t logic);
Std_ReturnType gpio_port_read_logic(const port_index_t port , logic_t *logic);
Std_ReturnType gpio_port_toggle_logic(const port_index_t port);


#endif	/* HAL_GPIO_H */


/* 
 * File:   hal_gpio.c
 * Author: Omar Hisham
 *
 * Created on January 20, 2024, 3:25 AM
 */
#include "hal_gpio.h"

volatile uint8 *tris_register[] = {&TRISA , &TRISB , &TRISC , &TRISD , &TRISE};
volatile uint8 *lat_register[]  = {&LATA , &LATB , &LATC , &LATD , &LATE};
volatile uint8 *port_register[] = {&PORTA , &PORTB , &PORTC , &PORTD , &PORTE};
/**
 * 
 * @param pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config ){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > (PORT_PIN_MAX_NUMBER-1)){
        ret = E_NOT_OK ;
    }
    else {
        switch(pin_config->direction){
                case OUTPUT :
                    Clear_Bit(*tris_register[pin_config->port],pin_config->pin);
                    break ;
                case INPUT  :
                    Set_Bit(*tris_register[pin_config->port],pin_config->pin);
                    break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *pin_config , direction_t *direction_status){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || NULL == direction_status || pin_config->pin > (PORT_PIN_MAX_NUMBER-1)){
         ret = E_NOT_OK ;
    }
    else {
        *direction_status = READ_BIT(*tris_register[pin_config->port],pin_config->pin);
    }
    return ret;  
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config , logic_t logic){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > (PORT_PIN_MAX_NUMBER-1)){
         ret = E_NOT_OK ;
    }
    else {
        switch(logic){
                case LOW :
                    Clear_Bit(*lat_register[pin_config->port],pin_config->pin);
                    break ;
                case HIGH  :
                    Set_Bit(*lat_register[pin_config->port],pin_config->pin);
                    break ;
                default : ret = E_NOT_OK ;
        }
    }
    return ret;  
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config , logic_t *logic){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || NULL == logic || pin_config->pin > (PORT_PIN_MAX_NUMBER-1)){
         ret = E_NOT_OK ;
    }
    else {
        *logic = READ_BIT(*port_register[pin_config->port],pin_config->pin);
    }
    return ret;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > (PORT_PIN_MAX_NUMBER-1)){
        ret = E_NOT_OK ;
    }
    else {
        Toggle_Bit(*lat_register[pin_config->port] , pin_config->pin);
    }
    return ret;
}
#endif

#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config){
    Std_ReturnType ret = E_OK ;
    if(NULL == pin_config || pin_config->pin > (PORT_PIN_MAX_NUMBER-1)){
        ret = E_NOT_OK ;
    }
    else {
        ret = gpio_pin_direction_initialize(pin_config);
        ret = gpio_pin_write_logic(pin_config , pin_config->logic);
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_port_direction_initialize(const port_index_t port , direction_t direction){
    Std_ReturnType ret = E_OK ;
    if(port > (PORT_MAX_NUMBER-1)){
        ret = E_NOT_OK ;
    }
    else{
        *tris_register[port] = direction ;
    }
    return ret;
}
#endif 

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_port_get_direction_status(const port_index_t port , direction_t *direction_status){
    Std_ReturnType ret = E_OK ;
    if((port > (PORT_MAX_NUMBER-1)) || (NULL == direction_status)){
        ret = E_NOT_OK ;
    }
    else{
        *direction_status = *tris_register[port];
    }
    
    return ret;
}
#endif 

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_port_write_logic(const port_index_t port , logic_t logic){
    Std_ReturnType ret = E_OK ;
    if(port > (PORT_MAX_NUMBER-1)){
        ret = E_NOT_OK ;
    }
    else{
        *lat_register[port] = logic ;
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_port_read_logic(const port_index_t port , logic_t *logic){
    Std_ReturnType ret = E_OK ;
    if((port > (PORT_MAX_NUMBER-1)) || (NULL == logic)){
        ret = E_NOT_OK ;
    }
    else{
        *logic = *lat_register[port];
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLED
Std_ReturnType gpio_port_toggle_logic(const port_index_t port){
    Std_ReturnType ret = E_OK ;
    if(port > (PORT_MAX_NUMBER-1)){
        ret = E_NOT_OK ;
    }
    else{
        (*lat_register[port])^= PORT_MASK ;
    }
    
    return ret;
}
#endif
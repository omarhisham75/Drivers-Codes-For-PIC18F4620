/* 
 * File:   Application.c
 * Author: Omar Hisham
 *
 * Created on January 20, 2024, 3:25 AM
 */

#include "Application.h"

/* 
pin_config_t led_1 = {
    .port = PORTC_INDEEX ,
    .pin  = PIN0 ,
    .direction = OUTPUT ,
    .logic = LOW 
};

pin_config_t led_2 = {
    .port = PORTC_INDEEX ,
    .pin  = PIN1 ,
    .direction = OUTPUT ,
    .logic = LOW 
};

pin_config_t led_3 = {
    .port = PORTC_INDEEX ,
    .pin  = PIN2 ,
    .direction = OUTPUT ,
    .logic = LOW 
};

pin_config_t btn_1 = {
    .port = PORTD_INDEEX ,
    .pin  = PIN0 ,
    .direction = INPUT ,
    .logic = LOW 
};



direction_t led_1_status ;
direction_t btn_1_status ;


led_t led_1 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN0 ,
  .led_status = LOW 
};

led_t led_2 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN1 ,
  .led_status = LOW 
};

Std_ReturnType ret = E_OK ;
button_t btn_high = {
    .button.port = PORTC_INDEEX ,
    .button.pin = PIN2 ,
    .button.direction = INPUT ,
    .button.logic = LOW ,
    .button_connection = BUTTON_ACTIVE_HIGH ,
    .button_state = BUTTON_RELEASED
};

button_t btn_low = {
    .button.port = PORTD_INDEEX ,
    .button.pin = PIN0 ,
    .button.direction = INPUT ,
    .button.logic = HIGH ,
    .button_connection = BUTTON_ACTIVE_LOW ,
    .button_state = BUTTON_RELEASED
};
button_state_t btn_high_state = BUTTON_RELEASED ;
button_state_t btn_low_state = BUTTON_RELEASED ;
uint32 btn_high_valid = 0 ;
button_state_t btn_high_state_valid = BUTTON_RELEASED ;
button_state_t btn_high_state_valid_last = BUTTON_RELEASED ;
led_status LedStatus = LED_OFF ;
uint8 btn_high_flag = 0 ;


relay_t relay_1 = {
    .port = PORTC_INDEEX ,
    .pin = PIN0 ,
    .relay_status = RELAY_OFF
};
relay_t relay_2 = {
    .port = PORTC_INDEEX ,
    .pin = PIN1 ,
    .relay_status = RELAY_OFF
};


dc_motor_t dec_motor_1 = {
    .dc_motor_pin[0].port = PORTC_INDEEX ,
    .dc_motor_pin[0].pin = PIN0 ,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[0].direction = OUTPUT ,
    .dc_motor_pin[1].port = PORTC_INDEEX ,
    .dc_motor_pin[1].pin = PIN1 ,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[1].direction = OUTPUT 
};

dc_motor_t dec_motor_2 = {
    .dc_motor_pin[0].port = PORTC_INDEEX ,
    .dc_motor_pin[0].pin = PIN2 ,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[0].direction = OUTPUT ,
    .dc_motor_pin[1].port = PORTC_INDEEX ,
    .dc_motor_pin[1].pin = PIN3 ,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[1].direction = OUTPUT 
};

uint8 seg_common_anode_values[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8 seg_common_cathode_values[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

uint8 hr = 23 , min = 59 , sec = 55 , counter = 0 ;


uint8 count = 48 ;
segment_t seg_1 = {
    .segment_pins[0].port = PORTC_INDEEX ,
    .segment_pins[0].pin = PIN0 ,
    .segment_pins[0].logic = LOW ,
    .segment_pins[0].direction = OUTPUT ,
    .segment_pins[1].port = PORTC_INDEEX ,
    .segment_pins[1].pin = PIN1 ,
    .segment_pins[1].logic = LOW ,
    .segment_pins[1].direction = OUTPUT ,
    .segment_pins[2].port = PORTC_INDEEX ,
    .segment_pins[2].pin = PIN2 ,
    .segment_pins[2].logic = LOW ,
    .segment_pins[2].direction = OUTPUT ,
    .segment_pins[3].port = PORTC_INDEEX ,
    .segment_pins[3].pin = PIN3 ,
    .segment_pins[3].logic = LOW ,
    .segment_pins[3].direction = OUTPUT ,
    .segment_type = SEGMENT_COMMON_ANODE 
};

pin_config_t seg1_pin = {
    .port = PORTD_INDEEX ,
    .pin = PIN0 ,
    .logic = LOW ,
    .direction = OUTPUT
};

pin_config_t seg2_pin = {
    .port = PORTD_INDEEX ,
    .pin = PIN1 ,
    .logic = LOW ,
    .direction = OUTPUT
};


keypad_t keypad_1 = {
  .keypad_rows_pin[0].port = PORTC_INDEEX ,
  .keypad_rows_pin[0].pin = PIN0 ,
  .keypad_rows_pin[0].direction = OUTPUT , 
  .keypad_rows_pin[0].logic = LOW ,
  .keypad_rows_pin[1].port = PORTC_INDEEX ,
  .keypad_rows_pin[1].pin = PIN1 ,
  .keypad_rows_pin[1].direction = OUTPUT , 
  .keypad_rows_pin[1].logic = LOW ,
  .keypad_rows_pin[2].port = PORTC_INDEEX ,
  .keypad_rows_pin[2].pin = PIN2 ,
  .keypad_rows_pin[2].direction = OUTPUT , 
  .keypad_rows_pin[2].logic = LOW ,
  .keypad_rows_pin[3].port = PORTC_INDEEX ,
  .keypad_rows_pin[3].pin = PIN3 ,
  .keypad_rows_pin[3].direction = OUTPUT , 
  .keypad_rows_pin[3].logic = LOW ,
  .keypad_columns_pin[0].port = PORTC_INDEEX ,
  .keypad_columns_pin[0].pin = PIN4 ,
  .keypad_columns_pin[0].direction = INPUT , 
  .keypad_columns_pin[0].logic = LOW ,
  .keypad_columns_pin[1].port = PORTC_INDEEX ,
  .keypad_columns_pin[1].pin = PIN5 ,
  .keypad_columns_pin[1].direction = INPUT , 
  .keypad_columns_pin[1].logic = LOW ,
  .keypad_columns_pin[2].port = PORTC_INDEEX ,
  .keypad_columns_pin[2].pin = PIN6 ,
  .keypad_columns_pin[2].direction = INPUT , 
  .keypad_columns_pin[2].logic = LOW ,
  .keypad_columns_pin[3].port = PORTC_INDEEX ,
  .keypad_columns_pin[3].pin = PIN7 ,
  .keypad_columns_pin[3].direction = INPUT , 
  .keypad_columns_pin[3].logic = LOW ,
};


chr_lcd_4bit_t lcd_1 = {
    .RS.port = PORTC_INDEEX ,
    .RS.pin = PIN0 , 
    .RS.direction = OUTPUT , 
    .RS.logic = LOW ,
    .Enable.port = PORTC_INDEEX ,
    .Enable.pin = PIN1 , 
    .Enable.direction = OUTPUT , 
    .Enable.logic = LOW ,
    .lcd_data[0].port = PORTC_INDEEX , 
    .lcd_data[0].pin = PIN2 ,
    .lcd_data[0].direction = OUTPUT ,
    .lcd_data[0].logic = LOW ,
    .lcd_data[1].port = PORTC_INDEEX , 
    .lcd_data[1].pin = PIN3 ,
    .lcd_data[1].direction = OUTPUT ,
    .lcd_data[1].logic = LOW ,
    .lcd_data[2].port = PORTC_INDEEX , 
    .lcd_data[2].pin = PIN4 ,
    .lcd_data[2].direction = OUTPUT ,
    .lcd_data[2].logic = LOW ,
    .lcd_data[3].port = PORTC_INDEEX , 
    .lcd_data[3].pin = PIN5 ,
    .lcd_data[3].direction = OUTPUT ,
    .lcd_data[3].logic = LOW ,
};

chr_lcd_8bit_t lcd_2 = {
    .RS.port = PORTC_INDEEX ,
    .RS.pin = PIN6 , 
    .RS.direction = OUTPUT , 
    .RS.logic = LOW ,
    .Enable.port = PORTC_INDEEX ,
    .Enable.pin = PIN7 , 
    .Enable.direction = OUTPUT , 
    .Enable.logic = LOW ,
    .lcd_data[0].port = PORTD_INDEEX , 
    .lcd_data[0].pin = PIN0 ,
    .lcd_data[0].direction = OUTPUT ,
    .lcd_data[0].logic = LOW ,
    .lcd_data[1].port = PORTD_INDEEX , 
    .lcd_data[1].pin = PIN1 ,
    .lcd_data[1].direction = OUTPUT ,
    .lcd_data[1].logic = LOW ,
    .lcd_data[2].port = PORTD_INDEEX , 
    .lcd_data[2].pin = PIN2 ,
    .lcd_data[2].direction = OUTPUT ,
    .lcd_data[2].logic = LOW ,
    .lcd_data[3].port = PORTD_INDEEX , 
    .lcd_data[3].pin = PIN3 ,
    .lcd_data[3].direction = OUTPUT ,
    .lcd_data[3].logic = LOW ,
    .lcd_data[4].port = PORTD_INDEEX , 
    .lcd_data[4].pin = PIN4 ,
    .lcd_data[4].direction = OUTPUT ,
    .lcd_data[4].logic = LOW ,
    .lcd_data[5].port = PORTD_INDEEX , 
    .lcd_data[5].pin = PIN5 ,
    .lcd_data[5].direction = OUTPUT ,
    .lcd_data[5].logic = LOW ,
    .lcd_data[6].port = PORTD_INDEEX , 
    .lcd_data[6].pin = PIN6 ,
    .lcd_data[6].direction = OUTPUT ,
    .lcd_data[6].logic = LOW ,
    .lcd_data[7].port = PORTD_INDEEX , 
    .lcd_data[7].pin = PIN7 ,
    .lcd_data[7].direction = OUTPUT ,
    .lcd_data[7].logic = LOW ,
};
uint8 lcd_counter = 0 ;
uint8 lcd_text[4];
const uint8 customChar[] = {0x0E,0x1B,0x11,0x11,0x11,0x11,0x1F,0x00};


void INT0_App_ISR(void){
    led_toggle(&led_1);
}

void INT1_App_ISR(void){
    led_toggle(&led_2);
}

void INT2_App_ISR(void){
    led_toggle(&led_3);
}


interrupt_NTx_t int0_obj = {
    .EXT_InterruptHandler = INT0_App_ISR ,
    .edge = INTERRUPT_RISING_EDGE ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .source = INTERRUPT_EXTERNAL_INT0 ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN0 ,
    .mcu_pin.direction = INPUT ,
};

interrupt_NTx_t int1_obj = {
    .EXT_InterruptHandler = INT1_App_ISR ,
    .edge = INTERRUPT_RISING_EDGE ,
    .priority = INTERRUPT_LOW_PRIORITY ,
    .source = INTERRUPT_EXTERNAL_INT1 ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN1 ,
    .mcu_pin.direction = INPUT ,
};

interrupt_NTx_t int2_obj = {
    .EXT_InterruptHandler = INT2_App_ISR ,
    .edge = INTERRUPT_RISING_EDGE ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .source = INTERRUPT_EXTERNAL_INT2 ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN2 ,
    .mcu_pin.direction = INPUT ,
};

led_t led_1 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN0 ,
  .led_status = LOW 
};

led_t led_2 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN1 ,
  .led_status = LOW 
};

led_t led_3 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN2 ,
  .led_status = LOW 
};

led_t led_4 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN3 ,
  .led_status = LOW 
};

void RB4_HIGH_INT_App_ISR(void) {
    led_turn_on(&led_1);
}
void RB4_LOW_INT_App_ISR(void) {
    led_turn_off(&led_1);
}

void RB5_HIGH_INT_App_ISR(void) {
    led_turn_on(&led_1);
}
void RB5_LOW_INT_App_ISR(void) {
    led_turn_off(&led_1);
}

void RB6_HIGH_INT_App_ISR(void) {
    led_turn_on(&led_1);
}
void RB6_LOW_INT_App_ISR(void) {
    led_turn_off(&led_1);
}

void RB7_HIGH_INT_App_ISR(void) {
    led_turn_on(&led_1);
}
void RB7_LOW_INT_App_ISR(void) {
    led_turn_off(&led_1);
}

interrupt_RBx_t int4_obj = {
    .EXT_InterruptHandler_HIGH = RB4_HIGH_INT_App_ISR ,
    .EXT_InterruptHandler_LOW = RB4_LOW_INT_App_ISR ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN4 ,
    .mcu_pin.direction = INPUT ,
};

interrupt_RBx_t int5_obj = {
    .EXT_InterruptHandler_HIGH = RB5_HIGH_INT_App_ISR ,
    .EXT_InterruptHandler_LOW = RB5_LOW_INT_App_ISR ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN5 ,
    .mcu_pin.direction = INPUT ,
};

interrupt_RBx_t int6_obj = {
    .EXT_InterruptHandler_HIGH = RB6_HIGH_INT_App_ISR ,
    .EXT_InterruptHandler_LOW = RB6_LOW_INT_App_ISR ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN6 ,
    .mcu_pin.direction = INPUT ,
};

interrupt_RBx_t int7_obj = {
    .EXT_InterruptHandler_HIGH = RB7_HIGH_INT_App_ISR ,
    .EXT_InterruptHandler_LOW = RB7_LOW_INT_App_ISR ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN7 ,
    .mcu_pin.direction = INPUT ,
};
volatile uint8 program_selected = 0 ;
void INT0_App_ISR(void){
    program_selected++ ;
     if(3 == program_selected){
        program_selected = 0 ;
    }
    Std_ReturnType ret = Data_EEPROM_WriteByte(0x3FF ,program_selected);
}

interrupt_NTx_t int0_obj = {
    .EXT_InterruptHandler = INT0_App_ISR ,
    .edge = INTERRUPT_RISING_EDGE ,
    .priority = INTERRUPT_HIGH_PRIORITY ,
    .source = INTERRUPT_EXTERNAL_INT0 ,
    .mcu_pin.port = PORTB_INDEEX ,
    .mcu_pin.pin = PIN0 ,
    .mcu_pin.direction = INPUT ,
};

led_t led_1 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN0 ,
  .led_status = LOW 
};
led_t led_2 = {
  .port = PORTC_INDEEX ,  
  .pin = PIN1 ,
  .led_status = LOW 
};


void program_1 (void){
    led_turn_on(&led_1);
    __delay_ms(250);
    led_turn_off(&led_1);
    __delay_ms(250);
}
uint8 eeprom_val = 0 , eeprom_read_val = 0 ;
void program_2 (void){
    led_turn_on(&led_2);
    __delay_ms(250);
    led_turn_off(&led_2);
    __delay_ms(250);
}

uint16 Lm35_result_1 = 0 , Lm35_result_2 = 0 , Lm35_celsius_1_mv = 0 , Lm35_celsius_2_mv = 0  ; 
uint8 Lm35_result_1_txt[6] , Lm35_result_2_txt[6] ; 
uint8 ADC_req = 0 ;

void ADC_DefaultInterruptHandler(void);

chr_lcd_4bit_t lcd_1 = {
    .RS.port = PORTC_INDEEX ,
    .RS.pin = PIN0 , 
    .RS.direction = OUTPUT , 
    .RS.logic = LOW ,
    .Enable.port = PORTC_INDEEX ,
    .Enable.pin = PIN1 , 
    .Enable.direction = OUTPUT , 
    .Enable.logic = LOW ,
    .lcd_data[0].port = PORTC_INDEEX , 
    .lcd_data[0].pin = PIN2 ,
    .lcd_data[0].direction = OUTPUT ,
    .lcd_data[0].logic = LOW ,
    .lcd_data[1].port = PORTC_INDEEX , 
    .lcd_data[1].pin = PIN3 ,
    .lcd_data[1].direction = OUTPUT ,
    .lcd_data[1].logic = LOW ,
    .lcd_data[2].port = PORTC_INDEEX , 
    .lcd_data[2].pin = PIN4 ,
    .lcd_data[2].direction = OUTPUT ,
    .lcd_data[2].logic = LOW ,
    .lcd_data[3].port = PORTC_INDEEX , 
    .lcd_data[3].pin = PIN5 ,
    .lcd_data[3].direction = OUTPUT ,
    .lcd_data[3].logic = LOW ,
};

dc_motor_t dec_motor_1 = {
    .dc_motor_pin[0].port = PORTD_INDEEX ,
    .dc_motor_pin[0].pin = PIN0 ,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[0].direction = OUTPUT ,
    .dc_motor_pin[1].port = PORTD_INDEEX ,
    .dc_motor_pin[1].pin = PIN1 ,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[1].direction = OUTPUT 
};

dc_motor_t dec_motor_2 = {
    .dc_motor_pin[0].port = PORTD_INDEEX ,
    .dc_motor_pin[0].pin = PIN2 ,
    .dc_motor_pin[0].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[0].direction = OUTPUT ,
    .dc_motor_pin[1].port = PORTD_INDEEX ,
    .dc_motor_pin[1].pin = PIN3 ,
    .dc_motor_pin[1].logic = DC_MOTOR_OFF ,
    .dc_motor_pin[1].direction = OUTPUT 
};

adc_config_t adc_1 = {
    .ADC_InterruptHandler = ADC_DefaultInterruptHandler ,
    .acquisition_time = ADC_12_TAD , // As per Data sheet 
    .adc_channel = ADC_CHANNEL_AN1 ,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16 ,
    .result_format = ADC_RESULT_RIGHT ,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLE 
};

void ADC_DefaultInterruptHandler(void){
    Std_ReturnType ret = E_OK ;
    if(0 == ADC_req){
        ret = ADC_Get_Conversion_Result(&adc_1 , &Lm35_result_1);
        ADC_req = 1 ;
    }
    else if(1 == ADC_req){
        ret = ADC_Get_Conversion_Result(&adc_1 , &Lm35_result_2);
        ADC_req = 0 ;
    }

}


led_t led_1 = {
  .port = PORTD_INDEEX ,  
  .pin = PIN0 ,
  .led_status = LOW 
};

led_t led_2 = {
  .port = PORTD_INDEEX ,  
  .pin = PIN1 ,
  .led_status = LOW 
};

volatile uint16 timer0_count_val = 0 ;

void Timer0_InterruptDefaultHandler(void){
    led_toggle(&led_1) ;
}

timer0_t timer0_timer_obj = {
    .TIMER0_InterruptHandler = Timer0_InterruptDefaultHandler ,
    .timer0_mode = TIMER0_TIMER_MODE ,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE ,
    .prescaler_enable = TIMER0_PRESCALER_ENABLE_CFG ,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_8 ,
    .timer0_preload_value = 3036 
} ;

timer0_t timer0_counter_obj = {
    .TIMER0_InterruptHandler = Timer0_InterruptDefaultHandler ,
    .timer0_mode = TIMER0_COUNTER_MODE ,
    .timer0_counter_edge = TIMER0_RISING_EDGE_CFG ,
    .timer0_register_size = TIMER0_16BIT_REGISTER_MODE ,
    .prescaler_enable = TIMER0_PRESCALER_DISABLE_CFG ,
    .timer0_preload_value = 0 
} ;

led_t led_1 = {
  .port = PORTD_INDEEX ,  
  .pin = PIN0 ,
  .led_status = LOW 
};
volatile uint32 timer1_on = 0 ;
volatile uint16 timer_counter_val = 0 ;
void Timer1_InterruptDefaultHandler(void){
    timer1_on++ ;
    led_toggle(&led_1) ;
}

timer1_t timer1_timer_obj = {
    .TIMER1_InterruptHandler = Timer1_InterruptDefaultHandler ,
    .priority = INTERRUPT_LOW_PRIORITY ,
    .timer1_mode = TIMER1_TIMER_MODE ,
    .timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_8 ,
    .timer1_preload_value = 15536 ,
    .timer1_reg_rw_mode = TIMER1_RW_REG_16BIT_MODE 
} ;

timer1_t timer1_counter_obj = {
    .TIMER1_InterruptHandler = NULL ,
    .priority = INTERRUPT_LOW_PRIORITY ,
    .timer1_mode = TIMER1_COUNTER_MODE ,
    .timer1_prescaler_value = TIMER1_PRESCALER_DIV_BY_1 ,
    .timer1_preload_value = 0 ,
    .timer1_reg_rw_mode = TIMER1_RW_REG_16BIT_MODE ,
    .timer1_counter_mode = TIMER1_SYNC_COUNTER_MODE
} ;

volatile uint32 timer2_flag = 0 ;
void Timer2_InterruptDefaultHandler(void){
    timer2_flag++ ;
}

timer2_t timer2_obj = {
    .TIMER2_InterruptHandler = Timer2_InterruptDefaultHandler ,
    .postscaler_value = TIMER2_POSTSCALER_DIV_BY_16 ,
    .prescaler_value = TIMER2_PRESCALER_DIV_BY_1 ,
    .timer2_preload_value = 249 ,
    .priority = INTERRUPT_LOW_PRIORITY 
};


led_t led_1 = {
  .port = PORTD_INDEEX ,  
  .pin = PIN0 ,
  .led_status = LOW 
};
volatile uint32 timer3_on = 0 ;
volatile uint16 timer3_counter_val = 0 ;

void Timer3_InterruptDefaultHandler(void){
    timer3_on++ ;
    led_toggle(&led_1) ;
}

timer3_t timer3_counter_obj = {
    .TIMER3_InterruptHandler = NULL ,
    .priority = INTERRUPT_LOW_PRIORITY ,
    .timer3_mode = TIMER3_COUNTER_MODE ,
    .timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1 ,
    .timer3_preload_value = 0 ,
    .timer3_reg_rw_mode = TIMER3_RW_REG_16BIT_MODE ,
    .timer3_counter_mode = TIMER3_SYNC_COUNTER_MODE
} ;

uint8 PWM_duty = 0 ;
timer2_t timer2_obj = {
    .TIMER2_InterruptHandler = NULL ,
    .postscaler_value = TIMER2_POSTSCALER_DIV_BY_1 ,
    .prescaler_value = TIMER2_PRESCALER_DIV_BY_1 ,
    .timer2_preload_value = 0 ,
};



ccp_t ccp2_obj = {
    .CCP2_InterruptHandler = NULL ,
    .ccp_inst = CCP2_INST ,
    .PWM_Frequency = 20000 ,
    .ccp_mode = CCP_PWM_MODE_SELECTED ,
    .ccp_mode_variant = CCP_PWM_MODE ,
    .ccp_pin.port = PORTC_INDEEX ,
    .ccp_pin.pin = PIN1 ,
    .ccp_pin.direction = OUTPUT ,
    .postscaler_value = CCP_TIMER2_POSTSCALER_DIV_BY_1 ,
    .prescaler_value = CCP_TIMER2_PRESCALER_DIV_BY_1
};

volatile uint32 Timer3_OverFlow = 0 , Total_Period_MS = 0 , Freq = 0 ;
volatile uint8 CCP1_SecondCapture_Flag = 0 ;

void CCP1_InterruptDefaultHandler(void) ;
void Timer3_InterruptDefaultHandler(void){
    Timer3_OverFlow++ ;
}


ccp_t ccp1_obj = {
    .CCP1_InterruptHandler = CCP1_InterruptDefaultHandler ,
    .ccp_inst = CCP1_INST ,
    .ccp_mode = CCP_CAPTURE_MODE_SELECTED ,
    .ccp_mode_variant = CCP_CAPTURE_MODE_1_RISING_EDGE ,
    .ccp_capture_timer = CCP1_CCP2_TIMER3 ,
    .ccp_pin.port = PORTC_INDEEX ,
    .ccp_pin.pin = PIN2 ,
    .ccp_pin.direction = INPUT , 
};


volatile uint16 Second_capture = 0 , timer3_test = 0 ;

void CCP1_InterruptDefaultHandler(void){
    static uint8 CCP1_Interrupt_flag = 0 ;
    CCP1_Interrupt_flag++ ;
    CCP1_SecondCapture_Flag++ ;
    
    if(1 == CCP1_Interrupt_flag){
        Timer3_Write_value(&Timer3_obj , 0) ;
    }
    else if (2 == CCP1_Interrupt_flag){
        Timer3_OverFlow = 0 ;
        CCP1_Interrupt_flag = 0 ;
        CCP_Capture_Mode_Read_Value(&Second_capture) ;
    }
}

void CCP1_InterruptDefaultHandler(void);

ccp_t ccp1_obj = {
    .CCP1_InterruptHandler = CCP1_InterruptDefaultHandler ,
    .ccp_inst = CCP1_INST ,
    .ccp_mode = CCP_COMPARE_MODE_SELECTED ,
    .ccp_mode_variant = CCP_COMPARE_MODE_SET_PIN_LOW ,
    .ccp_capture_timer = CCP1_CCP2_TIMER3 ,
    .ccp_pin.port = PORTC_INDEEX ,
    .ccp_pin.pin = PIN2 ,
    .ccp_pin.direction = OUTPUT , 
};

timer3_t Timer3_obj = {
  .TIMER3_InterruptHandler =   NULL ,
  .timer3_mode = TIMER3_TIMER_MODE ,
  .timer3_prescaler_value = TIMER3_PRESCALER_DIV_BY_1 , 
  .timer3_preload_value = 0 ,
  .timer3_reg_rw_mode = TIMER3_RW_REG_16BIT_MODE 
};

volatile uint8 CCP1_callback_flag = 0 ;

void CCP1_InterruptDefaultHandler(void){
    CCP1_callback_flag++ ;
    Timer3_Write_value(&Timer3_obj , 0) ;
    if ( 1 == CCP1_callback_flag){
        CCP_Compare_Mode_Set_Value(&ccp1_obj , 12500) ;
        CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
    }
    else if ( 2 == CCP1_callback_flag){
        CCP1_callback_flag = 0 ;
        CCP_Compare_Mode_Set_Value(&ccp1_obj , 37500) ;
        CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
    }
}




led_t led_1 = {
  .port = PORTD_INDEEX ,  
  .pin = PIN0 ,
  .led_status = LOW 
};
led_t led_2 = {
  .port = PORTD_INDEEX ,  
  .pin = PIN1 ,
  .led_status = LOW 
};
volatile uint32 usart_tx_tester = 0 ;
volatile uint8 usart_data_rx = 0 ;
void EUSART_TXDefaultInterruptHandler(void){
    usart_tx_tester++ ;
}

void EUSART_FramingDefaultErrorHandler(void){
    uint8 _data_frE = 0 ;
    EUSART_ASYNC_ReadByteNonBlocking(&_data_frE) ;
}

void EUSART_OverrunDefaultErrorHandler(void){
    EUSART_ASYNC_RX_Restart();
}

volatile uint32 usart_rx_tester = 0 ;
void EUSART_RXDefaultInterruptHandler(void){
    Std_ReturnType ret = E_OK ;
    usart_rx_tester++ ;
    ret = EUSART_ASYNC_ReadByteNonBlocking(&usart_data_rx) ;
    switch(usart_data_rx){
        case 'a' : led_turn_on(&led_1) ; ret = EUSART_ASYNC_WriteStringNonBlocking("Led1 On\r" , 8); break ;
        case 'b' : led_turn_off(&led_1) ; ret = EUSART_ASYNC_WriteStringNonBlocking("Led1 Off\r" , 9); break ;
        case 'c' : led_turn_on(&led_2) ; ret = EUSART_ASYNC_WriteStringNonBlocking("Led2 On\r" , 8); break ;
        case 'd' : led_turn_off(&led_2) ; ret = EUSART_ASYNC_WriteStringNonBlocking("Led1 Off\r" , 9); break ;
        default : led_turn_off(&led_1) ; led_turn_off(&led_2) ;
    }
}

uint8 rec_uart_data = 0 ;
usart_t usart_obj = {
   .baudrate = 9600 ,
   .baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED ,
   .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE ,
   .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE ,
   .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE ,
   .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE ,
   .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE ,
   .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE ,
   .EUSART_FramingErrorHandler = EUSART_FramingDefaultErrorHandler ,
   .EUSART_OverrunErrorHandler = EUSART_OverrunDefaultErrorHandler , 
   .EUSART_RxDefaultInterruptHandler = EUSART_RXDefaultInterruptHandler ,
   .EUSART_TxDefaultInterruptHandler = EUSART_TXDefaultInterruptHandler
} ;
*/

/* Address = 0x30 + W bit (0) = 0x60 */
#define SLAVE_1 0x60 
/* Address = 0x31 + W bit (0) = 0x62 */
#define SLAVE_2 0x62 

uint8 slave_ack = 0 ;

mssp_i2c_t i2c_obj = {
    .i2c_cfg.i2c_mode = I2C_MSSP_MASTER_MODE ,
    .i2c_cfg.i2c_mode_cfg = I2C_MASTER_MODE_DEFINED_CLOCK ,
    .i2c_clock = 100000 ,
    .i2c_cfg.i2c_SMBus_control = I2C_SMBus_DISABLE ,
    .i2c_cfg.i2c_slew_rate = I2C_SLEW_RATE_DISABLE ,
    .I2C_DefaultInterruptHandler = NULL ,
    .I2C_Report_Receive_Overflow = NULL ,
    .I2C_Report_Write_Collision = NULL 
};

void MSSP_I2C_Send_1_Byte(uint8 Slave_add , uint8 _data){
    Std_ReturnType ret = E_OK ;
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj) ;
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj , Slave_add , &slave_ack) ;
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj , _data , &slave_ack) ;
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj) ;
}

Std_ReturnType ret = E_OK ;
int main() {
    
    ret = MSSP_I2C_Init(&i2c_obj) ;
        
    /*
    
    
    ret = EUSART_ASYNC_Init(&usart_obj) ;
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = CCP_Compare_Mode_Set_Value(&ccp1_obj , 37500) ;
    ret = CCP_Initialize(&ccp1_obj) ;
    ret = Timer3_Initialize(&Timer3_obj) ;
    ret = Timer2_Initialize(&timer2_obj) ;
    
    
    ret = CCP_Initialize(&ccp2_obj) ;
    
    ret = CCP_PWM_Set_Duty(&ccp1_obj , 50) ;
    ret = CCP_PWM_Set_Duty(&ccp2_obj , 75) ;
    ret = CCP_PWM_Start(&ccp1_obj) ;
    ret = CCP_PWM_Start(&ccp2_obj) ;
    
    
    
    ret = Timer1_Initialize(&timer1_timer_obj);
    
    ret = Timer1_Initialize(&timer1_counter_obj);
    
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = Timer0_Initialize(&timer0_timer_obj);
    ret = Timer0_Initialize(&timer0_counter_obj);
    
    ret = ADC_Initialize(&adc_1);
    ret = lcd_4bit_initialize(&lcd_1);
    ret = dc_motor_initialize(&dec_motor_1);
    ret = dc_motor_initialize(&dec_motor_2);
    
    ret = lcd_4bit_send_string_data_position(&lcd_1 , 1 , 7 , "LM35 TEST");
    
    ret = lcd_4bit_send_string_data_position(&lcd_1 , 2 , 1 , "Temp1:");
    ret = lcd_4bit_send_string_data_position(&lcd_1 , 3 , 1 , "Temp2:");
    
    
    
    ret = led_initialize(&led_2);
    //ret = Data_EEPROM_WriteByte(0x3FF , 0);
    ret = Interrupt_NTx_Initialize(&int0_obj);
    
    
    ret = Interrupt_RBx_Initialize(&int4_obj);
    ret = Interrupt_RBx_Initialize(&int5_obj);
    ret = Interrupt_RBx_Initialize(&int6_obj);
    ret = Interrupt_RBx_Initialize(&int7_obj);
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    ret = led_initialize(&led_3);
    ret = led_initialize(&led_4);
    
   
    ret = Interrupt_NTx_Initialize(&int0_obj);
    ret = Interrupt_NTx_Initialize(&int1_obj);
    ret = Interrupt_NTx_Initialize(&int2_obj);
    ret = lcd_4bit_initialize(&lcd_1);
    ret = lcd_8bit_initialize(&lcd_2);
    ret = lcd_8bit_send_custom_char(&lcd_2 , 1 , 1 , customChar , 0);
    ret = lcd_4bit_send_custom_char(&lcd_1 , 1 , 1 , customChar , 0);
    
    ret = lcd_4bit_send_string_data_position(&lcd_1 , 2 , 2 , "Omar"); 
    ret = lcd_8bit_send_string_data(&lcd_2 , "Omar");

    
    ret = keypad_initialize(&keypad_1);,
    
    ret = gpio_pin_initialize(&seg1_pin);
    ret = gpio_pin_initialize(&seg2_pin);
    ret = seven_segment_initialze(&seg_1);
    
    
    ret = gpio_port_direction_initialize(PORTC_INDEEX , 0xF0);  
    ret = gpio_port_direction_initialize(PORTD_INDEEX , 0xC0); 
    
    ret = dc_motor_initialize(&dec_motor_1);
    ret = dc_motor_initialize(&dec_motor_2);
    
    ret = relay_initialize(&relay_1);
    ret = relay_initialize(&relay_2);

    ret = button_initialize(&btn_high);
    ret = button_initialize(&btn_low);
    
    
    //ret = gpio_pin_initialize(&btn_1);
    
    ret = led_initialize(&led_1);
    ret = led_initialize(&led_2);
    
    ret = gpio_pin_initialize(&led_3);

    
    ret = gpio_pin_get_direction_status(&led_1,&led_1_status);
    ret = gpio_pin_direction_initialize(&led_2);
    ret = gpio_pin_direction_initialize(&led_3);
    

    ret = gpio_port_direction_initialize(PORTC_INDEEX , 0x00);
    ret = gpio_port_write_logic(PORTC_INDEEX , 0xAA);
    */
    
    //ret = led_initialize(&led1);
     //ret = Data_EEPROM_ReadByte(0x3FF , &program_selected);
    while(1){
        MSSP_I2C_Send_1_Byte(SLAVE_1 , 'a') ;
        __delay_ms(2000);
        MSSP_I2C_Send_1_Byte(SLAVE_2 , 'b') ;
        __delay_ms(2000);
        MSSP_I2C_Send_1_Byte(SLAVE_1 , 'c') ;
        __delay_ms(2000);
        MSSP_I2C_Send_1_Byte(SLAVE_2 , 'd') ;
        __delay_ms(2000);
    }
    /*
        ret = EUSART_ASYNC_WriteStringBlocking("Hello\r" , 6) ;
           
            ret = EUSART_ASYNC_ReadByteNonBlocking(&rec_uart_data) ;   
        if(E_OK == ret ){
            if('a' == rec_uart_data){
                led_turn_on(&led_1) ;
                ret = EUSART_ASYNC_WriteStringBlocking("Led on\r" , 7) ;
            }
            else if('b' == rec_uart_data){
                led_turn_off(&led_1) ;
                ret = EUSART_ASYNC_WriteStringBlocking("Led off\r" , 8) ;
            }
            else{}
        }
        else {}
            }
            
            else {} 
        }
        else {}
     ret = EUSART_ASYNC_WriteByteBlocking('a') ;
        __delay_ms(1000) ;
        ret = EUSART_ASYNC_WriteByteBlocking('b') ;
        __delay_ms(1000) ;
      ret = EUSART_ASYNC_WriteStringBlocking("Omar\r" , 5) ;
        __delay_ms(1000) ;
        ret = EUSART_ASYNC_WriteStringBlocking("Hisham\r" , 7) ;
        __delay_ms(1000) ;
     if(2 == CCP1_SecondCapture_Flag){
            Total_Period_MS = (Timer3_OverFlow * 65536) + Second_capture ;
            Freq = 1/(Total_Period_MS / 1000000.0) ;
            CCP1_SecondCapture_Flag = 0 ;
        }
         for(PWM_duty = 0 ; PWM_duty < 100 ; PWM_duty+=5){
            ret = CCP_PWM_Set_Duty(&ccp1_obj , PWM_duty) ;
        }
        ret = Timer3_Read_value(&timer3_counter_obj , &timer3_counter_val);
        ret = Timer1_Read_value(&timer1_counter_obj , &timer_counter_val) ;
        ret = Timer0_Read_value(&timer0_counter_obj , &timer0_count_val) ;
        if(0 == ADC_req){
            ret = ADC_Start_Conversion_Interrupt(&adc_1 , ADC_CHANNEL_AN0);
        }
        else if(1 == ADC_req){
            ret = ADC_Start_Conversion_Interrupt(&adc_1 , ADC_CHANNEL_AN1);
        }
        
        Lm35_celsius_1_mv = Lm35_result_1 * 4.8828125f ;
        Lm35_celsius_1_mv /= 10 ;
        
        Lm35_celsius_2_mv = Lm35_result_2 * 4.8828125f ;
        Lm35_celsius_2_mv /= 10 ;
        
        ret = convert_short_to_string(Lm35_celsius_1_mv , Lm35_result_1_txt);
        ret = convert_short_to_string(Lm35_celsius_2_mv , Lm35_result_2_txt);
        
        ret = lcd_4bit_send_string_data_position(&lcd_1 , 2 , 8 , Lm35_result_1_txt);
        ret = lcd_4bit_send_string_data_position(&lcd_1 , 3 , 8 , Lm35_result_2_txt);
        
        if(Lm35_celsius_1_mv > 20){
            ret = dc_motor_move_right(&dec_motor_1);
        }
        else{
            ret = dc_motor_stop(&dec_motor_1);
        }
        
        if(Lm35_celsius_2_mv > 25){
            ret = dc_motor_move_right(&dec_motor_2);
        }
        else{
            ret = dc_motor_stop(&dec_motor_2);
        }
        
    }
        
        
        ret = ADC_Get_Conversion_Blocking(&adc_1 , ADC_CHANNEL_AN1 , &adc_result_2);
        ret = ADC_Get_Conversion_Blocking(&adc_1 , ADC_CHANNEL_AN2 , &adc_result_3);
        ret = ADC_Get_Conversion_Blocking(&adc_1 , ADC_CHANNEL_AN3 , &adc_result_4);
        ret = Data_EEPROM_WriteByte(0x3FF , eeprom_val++);
        __delay_ms(1000);
        ret = Data_EEPROM_ReadByte(0x3FF , &eeprom_read_val);
        
        
        if(1 == program_selected){
            program_1();
        }
        else if(2 == program_selected){
            program_2();
        }
        else{
            led_turn_off(&led_1);
            led_turn_off(&led_2);
        }
        }
         */
        /*
        ret = convert_byte_to_string(lcd_counter , lcd_text);
        ret = ret = lcd_8bit_send_string_data_position(&lcd_2 , 1 , 11 , lcd_text);
        lcd_counter++;
        __delay_ms(200);

    
   
    
        ret = keypad_get_value(&keypad_1 , &val);

            ret = seven_segment_write_number(&seg_1 , ((uint8)(count/10)));
            ret = gpio_pin_write_logic(&seg1_pin , HIGH);
            __delay_ms(5);
            ret = gpio_pin_write_logic(&seg1_pin , LOW);
            ret = seven_segment_write_number(&seg_1 , ((uint8)(count%10)));
            ret = gpio_pin_write_logic(&seg2_pin , HIGH);
            __delay_ms(5);
            ret = gpio_pin_write_logic(&seg2_pin , LOW);

        
        
        
        for(counter = 0 ; counter < 50 ; counter++){
        ret = gpio_port_write_logic(PORTD_INDEEX , 0x3E);
        ret = gpio_port_write_logic(PORTC_INDEEX , ((uint8)hr/10));
        __delay_us(3333);
        ret = gpio_port_write_logic(PORTD_INDEEX , 0x3D);
        ret = gpio_port_write_logic(PORTC_INDEEX , ((uint8)hr%10));
        __delay_us(3333);
        ret = gpio_port_write_logic(PORTD_INDEEX , 0x3B);
        ret = gpio_port_write_logic(PORTC_INDEEX , ((uint8)min/10));
        __delay_us(3333);
        ret = gpio_port_write_logic(PORTD_INDEEX , 0x37);
        ret = gpio_port_write_logic(PORTC_INDEEX , ((uint8)min%10));
        __delay_us(3333);
        ret = gpio_port_write_logic(PORTD_INDEEX , 0x2F);
        ret = gpio_port_write_logic(PORTC_INDEEX , ((uint8)sec/10));
        __delay_us(3333);
        ret = gpio_port_write_logic(PORTD_INDEEX , 0x1F);
        ret = gpio_port_write_logic(PORTC_INDEEX , ((uint8)sec%10));
        __delay_us(3333);
        }
        sec++;
        if(60 == sec){
            min++;
            sec = 0 ;
        }
        if(60 == min){
            hr++;
            min = 0 ;
        }
        if(24 == hr){
            hr = 0 ;
        }
        
    number_DCB = (number%10) | (((uint8)number/10)<<4);
    ret = gpio_port_direction_initialize(PORTC_INDEEX , number_DCB);
    number++;
    __delay_ms(200);
    if(99 == number){
        number = 0;
    }
        
        for(tens=0; tens<10; tens++){
            ret = gpio_port_write_logic(PORTD_INDEEX, tens);
            for(ones=0; ones<10; ones++){
                ret = gpio_port_write_logic(PORTC_INDEEX, ones);
                __delay_ms(1000);
            }
        }
        
        ret = dc_motor_move_right(&dec_motor_1);
        ret = dc_motor_move_right(&dec_motor_2);
        __delay_ms(2000);
        ret = dc_motor_move_left(&dec_motor_1);
        ret = dc_motor_move_left(&dec_motor_2);
        __delay_ms(2000);
        ret = dc_motor_stop(&dec_motor_1);
        ret = dc_motor_stop(&dec_motor_2);
        __delay_ms(2000);
        ret = dc_motor_move_right(&dec_motor_1);
        ret = dc_motor_move_left(&dec_motor_2);
        __delay_ms(2000);
        ret = dc_motor_move_left(&dec_motor_1);
        ret = dc_motor_move_right(&dec_motor_2);
        __delay_ms(2000);
        
        ret = relay_turn_on(&relay_1);
        ret = relay_turn_off(&relay_2);
        __delay_ms(1000);
        ret = relay_turn_on(&relay_2);
        ret = relay_turn_off(&relay_1);
        __delay_ms(1000);
        
        ret = button_read_state(&btn_high , &btn_high_state);
        ret = button_read_state(&btn_low , &btn_low_state);
        if (BUTTON_PRESSED == btn_high_state){
            btn_high_valid++;
            if(btn_high_valid>500){
                btn_high_state_valid = BUTTON_PRESSED;
            }
        }
        else{
            btn_high_valid = 0;
            btn_high_state_valid = BUTTON_RELEASED ;
        }

        if(btn_high_state_valid_last != btn_high_state_valid){
            btn_high_state_valid_last = btn_high_state_valid ;
            if(BUTTON_PRESSED == btn_high_state_valid){
                if(LED_OFF == LedStatus){
                    ret = led_turn_on(&led_1);
                    LedStatus = LED_ON ;
                }
                else{
                    ret = led_turn_off(&led_1);
                    LedStatus = LED_OFF ;
                }
            }
        }
 */

               
     /*   
        ret = gpio_pin_read_logic(&btn_1 , &btn_1_status);
        if (btn_1_status == HIGH){
             ret = gpio_pin_write_logic(&led_1,HIGH);
             ret = gpio_pin_write_logic(&led_2,HIGH);
             ret = gpio_pin_write_logic(&led_3,HIGH);
        }
        else {
            ret = gpio_pin_write_logic(&led_1,LOW);
            ret = gpio_pin_write_logic(&led_2,LOW);
            ret = gpio_pin_write_logic(&led_3,LOW);
        }
 
        ret = gpio_port_toggle_logic(PORTC_INDEEX);
        __delay_ms(1000);
       ret = gpio_port_toggle_logic(PORTC_INDEEX);
        __delay_ms(2000);
        

    ret = led_turn_on(&led1);
    __delay_ms(500);
    ret = led_turn_off(&led1);
     __delay_ms(500);
    
    ret = led_toggle(&led1);
     __delay_ms(500);
     */
    return (EXIT_SUCCESS);
}


/* 
 * File:   ecu_chr_LCD.c
 * Author: Omar Hisham
 *
 * Created on January 28, 2024, 5:48 PM
 */

#include "ecu_chr_LCD.h"



Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        uint8 l_counter = 0 ;
        ret = gpio_pin_initialize(&(lcd->RS));
        ret = gpio_pin_initialize(&(lcd->Enable));
        for(l_counter= 0 ; l_counter < 4 ; l_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE); 
        ret = lcd_4bit_send_command(lcd , _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd , _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd , _LCD_CURSOR_OFE_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd , 0x80);
    }
    return ret ;
}

Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd , uint8 command){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->RS) , LOW);
        ret = lcd_send_4bit(lcd , command >> 4);
        ret = lcd_4bit_send_Enable(lcd);
        ret = lcd_send_4bit(lcd , command );
        ret = lcd_4bit_send_Enable(lcd);
    }
    return ret ;
}

Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd , uint8 data){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->RS) , HIGH);
        ret = lcd_send_4bit(lcd , data >> 4);
        ret = lcd_4bit_send_Enable(lcd);
        ret = lcd_send_4bit(lcd , data );
        ret = lcd_4bit_send_Enable(lcd);
    }
    return ret ;
}

Std_ReturnType lcd_4bit_send_char_data_position(const chr_lcd_4bit_t *lcd  , uint8 row , uint8 column , uint8 data){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        ret = lcd_4bit_get_cursor(lcd , row , column);
        ret = lcd_4bit_send_char_data(lcd , data);
    }
    return ret ;
}

Std_ReturnType lcd_4bit_send_string_data(const chr_lcd_4bit_t *lcd , uint8 *str){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK ;
    }
    else {
        while(*str){
        ret = lcd_4bit_send_char_data(lcd , *str++);
        }
    }
    return ret ;
}

Std_ReturnType lcd_4bit_send_string_data_position(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column , uint8 *str){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK ;
    }
    else {
        ret = lcd_4bit_get_cursor(lcd , row , column);
        ret = lcd_4bit_send_string_data(lcd , str);
    }
    return ret ;
}

Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column , 
                                         const uint8 chr[] , uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        uint8 l_counter ;
        ret = lcd_4bit_send_command(lcd , (_LCD_CGRAM_START + (mem_pos*8)));
        for(l_counter = 0 ; l_counter <= 7 ; l_counter++){
            ret = lcd_4bit_send_char_data(lcd , chr[l_counter]);
        }
        ret = lcd_4bit_send_char_data_position(lcd , row , column , mem_pos);
    }
    return ret ;
}


Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        uint8 l_counter = 0 ;
        ret = gpio_pin_initialize(&(lcd->RS));
        ret = gpio_pin_initialize(&(lcd->Enable));
        for(l_counter= 0 ; l_counter < 8 ; l_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE); 
        /*ret = lcd_8bit_send_command(lcd , _LCD_CLEAR);*/
        ret = lcd_8bit_send_command(lcd , _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd , _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd , _LCD_CURSOR_OFE_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd , 0x80);

    }
    return ret ;
}

Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd , uint8 command){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        uint8 l_counter = 0 ;
        ret = gpio_pin_write_logic(&(lcd->RS) , LOW);
        for(l_counter = 0 ; l_counter < 8 ; l_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_counter]) , (command >> l_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_Enable(lcd);
    }
    return ret ;
}

Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd , uint8 data){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        uint8 l_counter = 0 ;
        ret = gpio_pin_write_logic(&(lcd->RS) , HIGH);
        for(l_counter = 0 ; l_counter < 8 ; l_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_counter]) , (data >> l_counter) & (uint8)0x01);
        }
        ret = lcd_8bit_send_Enable(lcd);
    }
    return ret ;
}

Std_ReturnType lcd_8bit_send_char_data_position(const chr_lcd_8bit_t *lcd  , uint8 row , uint8 column , uint8 data){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        ret = lcd_8bit_get_cursor(lcd , row , column);
        ret = lcd_8bit_send_char_data(lcd , data);
    }
    return ret ;
}

Std_ReturnType lcd_8bit_send_string_data(const chr_lcd_8bit_t *lcd , uint8 *str){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK ;
    }
    else {
        while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str++);
        }
    }
    return ret ;
}

Std_ReturnType lcd_8bit_send_string_data_position(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column , uint8 *str){
    Std_ReturnType ret = E_NOT_OK ; 
    if((NULL == lcd) || (NULL == str)){
        ret = E_NOT_OK ;
    }
    else {
        ret = lcd_8bit_get_cursor(lcd , row , column);
        ret = lcd_8bit_send_string_data(lcd , str);
    }
    return ret ;
}

Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column , 
                                         const uint8 chr[] , uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == lcd){
        ret = E_NOT_OK ;
    }
    else {
        uint8 l_counter ;
        ret = lcd_8bit_send_command(lcd , (_LCD_CGRAM_START + (mem_pos*8)));
        for(l_counter = 0 ; l_counter <= 7 ; l_counter++){
            ret = lcd_8bit_send_char_data(lcd , chr[l_counter]);
        }
        ret = lcd_8bit_send_char_data_position(lcd , row , column , mem_pos);
    }
    return ret ;
}


Std_ReturnType convert_byte_to_string(uint8 value , uint8 *str){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == str){
        ret = E_NOT_OK ;
    }
    else {
        memset(str , '\0' , 4);
        sprintf(str , "%i" , value);
    }
    return ret ;
}

Std_ReturnType convert_short_to_string(uint16 value , uint8 *str){
    Std_ReturnType ret = E_NOT_OK ; 
    uint8 Temp_string[6] = {0} ;
    uint8 DataCounter = 0 ;
    if(NULL == str){
        ret = E_NOT_OK ;
    }
    else {
        memset(str , ' ' , 5);
        str[5] = '\0' ;
        sprintf(Temp_string , "%i" , value);
        while('\0' != Temp_string[DataCounter]){
            str[DataCounter] = Temp_string[DataCounter] ;
            DataCounter++ ;
        }
    }
    return ret ;
}

Std_ReturnType convert_int_to_string(uint32 value , uint8 *str){
    Std_ReturnType ret = E_NOT_OK ; 
    if(NULL == str){
        ret = E_NOT_OK ;
    }
    else {
        memset(str , '\0' , 11);
        sprintf(str , "%i" , value);
    }
    return ret ;
}

static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd , uint8 Data_OR_command){
    Std_ReturnType ret = E_NOT_OK ;
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , (Data_OR_command >> 0) & (uint8)0x01 );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , (Data_OR_command >> 1) & (uint8)0x01 );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]) , (Data_OR_command >> 2) & (uint8)0x01 );
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]) , (Data_OR_command >> 3) & (uint8)0x01 );
            
    return ret ;
}

static Std_ReturnType lcd_4bit_send_Enable(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK ;
    ret = gpio_pin_write_logic(&(lcd->Enable) , HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->Enable) , LOW);
    return ret ;
}

static Std_ReturnType lcd_8bit_send_Enable(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK ;
    ret = gpio_pin_write_logic(&(lcd->Enable) , HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->Enable) , LOW);
    return ret ;
}

static Std_ReturnType lcd_8bit_get_cursor(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column){
    Std_ReturnType ret = E_NOT_OK ;
    column--;
    switch(row){
        case ROW1 : ret = lcd_8bit_send_command(lcd , (0x80 + column )); break ;
        case ROW2 : ret = lcd_8bit_send_command(lcd , (0xC0 + column )); break ;
        case ROW3 : ret = lcd_8bit_send_command(lcd , (0x94 + column )); break ;
        case ROW4 : ret = lcd_8bit_send_command(lcd , (0xD4 + column )); break ;
        default : ;
    }
    return ret ;
}

static Std_ReturnType lcd_4bit_get_cursor(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column){
    Std_ReturnType ret = E_NOT_OK ;
    column--;
    switch(row){
        case ROW1 : ret = lcd_4bit_send_command(lcd , (0x80 + column )); break ;
        case ROW2 : ret = lcd_4bit_send_command(lcd , (0xC0 + column )); break ;
        case ROW3 : ret = lcd_4bit_send_command(lcd , (0x94 + column )); break ;
        case ROW4 : ret = lcd_4bit_send_command(lcd , (0xD4 + column )); break ;
        default : ;
    }
    return ret ;
}
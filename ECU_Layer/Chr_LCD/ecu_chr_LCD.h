/* 
 * File:   ecu_chr_LCD.h
 * Author: Omar Hisham
 *
 * Created on January 28, 2024, 5:48 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* Includes Section */
#include "ecu_chr_LCD_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Macros Section */

#define _LCD_CLEAR                          0x01
#define _LCD_RETURN_HOME                    0x02
#define _LCD_ENTRY_MODE                     0x06
#define _LCD_CURSOR_OFE_DISPLAY_ON          0x0C
#define _LCD_CURSOR_OFE_DISPLAY_OFF         0x08
#define _LCD_CURSOR_ON_BLINK_ON             0x0F
#define _LCD_CURSOR_ON_BIINK_OEF            0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT            0x1C
#define _LCD_DISPLAY_SHIFT_LEET             0x18
#define _LCD_8BIT_MODE_2_LINE               0x38
#define _LCD_4BIT_MODE_2_LINE               0x28
#define _LCD_CGRAM_START                    0x40
#define _LCD_DDRAM_START                    0x80


/* Macro Functions Section */

/* Data Types Declarations */
typedef enum {
    ROW1 = 1 ,
    ROW2 ,
    ROW3 ,
    ROW4 
}row_number_t ;

typedef struct {
    pin_config_t RS;
    pin_config_t Enable ;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct {
    pin_config_t RS;
    pin_config_t Enable ;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/* Functions Declarations */

Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd , uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd , uint8 data);
Std_ReturnType lcd_4bit_send_char_data_position(const chr_lcd_4bit_t *lcd  , uint8 row , uint8 column , uint8 data);
Std_ReturnType lcd_4bit_send_string_data(const chr_lcd_4bit_t *lcd , uint8 *str);
Std_ReturnType lcd_4bit_send_string_data_position(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column , uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column , 
                                         const uint8 chr[] , uint8 mem_pos);

Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd , uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd , uint8 data);
Std_ReturnType lcd_8bit_send_char_data_position(const chr_lcd_8bit_t *lcd  , uint8 row , uint8 column , uint8 data);
Std_ReturnType lcd_8bit_send_string_data(const chr_lcd_8bit_t *lcd , uint8 *str);
Std_ReturnType lcd_8bit_send_string_data_position(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column , uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column ,
                                         const uint8 chr[] , uint8 mem_pos);

Std_ReturnType convert_byte_to_string(uint8 value , uint8 *str);
Std_ReturnType convert_short_to_string(uint16 value , uint8 *str);
Std_ReturnType convert_int_to_string(uint32 value , uint8 *str);

static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd , uint8 Data_OR_command);
static Std_ReturnType lcd_4bit_send_Enable(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_send_Enable(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_get_cursor(const chr_lcd_8bit_t *lcd , uint8 row , uint8 column);
static Std_ReturnType lcd_4bit_get_cursor(const chr_lcd_4bit_t *lcd , uint8 row , uint8 column);

#endif	/* ECU_CHR_LCD_H */


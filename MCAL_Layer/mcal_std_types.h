/* 
 * File:   mcal_std_types.h
 * Author: HP G3
 *
 * Created on January 20, 2024, 3:48 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H



/* Includes Section */
#include "std_libiraries.h"
#include "Compiler.h"

/* Macro Functions Section */

/* Data Types Declarations */
typedef unsigned char boolean;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef float float32;

typedef uint8 Std_ReturnType;

/* Macros Section */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00

#define CONFIG_ENABLED  0x01
#define CONFIG_DISABLED 0x00

/* Functions Declarations */


#endif	/* MCAL_STD_TYPES_H */


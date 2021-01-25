/*
────────────────────────── PORTABLE SALUTRON READER ───────────────────────────

    This document contains confidential information and privileged material
    for the sole use of those authorized by True Fitness.  Any review, use,
    retention, distribution, or disclosure by anyone not authorized by True Fitness
    is strictly prohibited.  If you have a copy of this program/document
    and have not been authorized by True Fitness to possess it, please contact
    and return document(s) to True Fitness immediately.
    Copyright: True Fitness 2020-2021  All Rights Reserved.

───────────────────────────────────────────────────────────────────────────────

    Project:    Salutron Reader
    Author:     Mark Doane
    Date:       11/26/20
    File:       Constants.h           -Contains system constants used through the entire program.
    Software:   1120400               -Software number.
    Board:      D-STIKE               -OLED Display, Three position switch, Neopixel LED, Various I/O.
       
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 1120400-REV-X.X.X MAIN.C FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     Constants_h
#define     Constants_h

#include    <Arduino.h>
#include    "Generic.h"

//──────────────────── UNIT-TEST DEFINITIONS ────────────────────────

#define     VCP_STATE       (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) to control console communications.
#define     NEO_LED         (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) to control NeoPixel functions.
#define     _OLED_DSP       (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) to control OLED-Display functions.
#define     DEBUG_IO        (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) to control DEBUG-test-point-Inputs/Outputs.
#define     SD_LOGGER       (_ENABLED)                     // Change the valve to (_ENABLED or _DISABLED) to control of the SD Data-LOGGER.
#define     RTC_MODULE      (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) to control of the RTC-Module.
#define     BIT_MACROS      (_DISABLED)                     // Change the valve to (_ENABLED or _DISABLED) to control of the BIT-MACROS.

//──────────────────── PORT PIN DEFINITIONS ─────────────────────────

#define     GPIO_0           (0u)                           // GPIO-0, Pin#25.
#define     GPIO_2           (2u)                           // GPIO-2, Pin#24.
#define     GPIO_4           (4u)                           // GPIO-4, Pin#26.      (USED)
#define     GPIO_5           (5u)                           // GPIO-5, Pin#29.      (USED)
#define     GPIO_14          (14u)                          // GPIO-14, Pin#13.
#define     GPIO_16          (16u)                          // GPIO-16, Pin#27.     (USED)
#define     GPIO_17          (17u)                          // GPIO-17, Pin#28.     (USED)
#define     GPIO_18          (18u)                          // GPIO-18, Pin#30.     (USED)
#define     GPIO_19          (19u)                          // GPIO-19, Pin#31.     (USED)
#define     GPIO_21          (21u)                          // GPIO-21, Pin#33.     (USED)
#define     GPIO_22          (22u)                          // GPIO-22, Pin#36.     (USED)
#define     GPIO_23          (23u)                          // GPIO-23, Pin#37.     
#define     GPIO_25          (25u)                          // GPIO-25, Pin#10.
#define     GPIO_26          (26u)                          // GPIO-26, Pin#11.     (USED)
#define     GPIO_27          (27u)                          // GPIO-27, Pin#12.     (USED)
#define     GPIO_32          (32u)                          // GPIO-32, Pin#8.
#define     GPIO_33          (33u)                          // GPIO-33, Pin#9.
#define     GPIO_34          (34u)                          // GPIO-34, Pin#6.
#define     GPIO_35          (35u)                          // GPIO-35, Pin#7.

//─────────────────── USED PORT PIN DEFINITIONS ─────────────────────

#define     SDA_0            (GPIO_4)                       // SDA-0, I²C Serial DAta Line I/O.
#define     SCL_0            (GPIO_5)                       // SCL-0, I²C Serial CLock OUTPUT.

#define     NAV_SW_RGT       (GPIO_19)                      // Thumb-SW1-RiGhT direction.
#define     NAV_SW_CTR       (GPIO_22)                      // Thumb-SW1-CenTeR Press.
#define     NAV_SW_LFT       (GPIO_18)                      // Thumb-SW1-LeFT direction.

#define     SAL_PULSE        (GPIO_27)                      // SALutron-PULSE-Input.
#define     SAL_MODE         (GPIO_26)                      // SALutron-MODE-Input.     

#define     LED_PXL_DO       (GPIO_21)                      // LED-PiXeL-Data-Output line.

#define     TXO_TO_LGR       (GPIO_17)                      // TX-Out to SD-LoGgeR.
#define     RXI_FROM_LGR     (GPIO_16)                      // RX-Input from SD-LoGgeR.

#endif

/* END OF FILE. */
/*
───────────────────────── M5 Salutron-Phantom-Detector ────────────────────────

    This document contains confidential information and privileged material
    for the sole use of those authorized by True Fitness.  Any review, use,
    retention, distribution, or disclosure by anyone not authorized by True Fitness
    is strictly prohibited.  If you have a copy of this program/document
    and have not been authorized by True Fitness to possess it, please contact
    and return document(s) to True Fitness immediately.
    Copyright: True Fitness 2020-2021  All Rights Reserved.

───────────────────────────────────────────────────────────────────────────────

    Project:    M5 Salutron-Phantom-Detector (M5-SPD)
    Author:     Mark Doane
    Date:       12/30/20
    File:       ISR.cpp               -Interrupt-Service-Routine functions.
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     _ISR_h_
#define     _ISR_h_

#include    "Constants.h"                                                   // Include Gloabal constants.

//────────────────────────────── ISR VARIABLES ────────────────────────────────

    extern  volatile    uint32_t        SAL_START_TME;                      // 32-Bit, Current micros START-TiME in µS.         (Default=0)
    extern  volatile    uint32_t        SAL_STOP_TME;                       // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
    extern  volatile    uint32_t        SAL_ELAPSED_TME;                    // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
    extern  volatile    uint32_t        PRV_PULSE_CNT;                      // PReVious-PULSE-CouNT.
    extern  volatile    uint32_t        PULSE_CNT;
    extern  volatile    _Bool           SAL_SIG_DET;
    
    extern  volatile    uint8_t         PBTN_DB_TMR;                        // Push-BuTtoN-De-Bounce-TiMeR, 1mS intervals.      (Default=0)
    extern  volatile    uint8_t         LED_ON_TMR;                         // LED-ON-TiMeR, 1mS intervals.                     (Default=0)
    extern  volatile    uint16_t        LCD_ON_TMR;                         // LCD-ON-TiMeR, 1mS intervals.                     (Default=0)

    extern  volatile    uint32_t        UnitControl;

    extern              I2C_AXP192      PMIC;    
    extern              M5Display       LCD;
    extern              portMUX_TYPE    GPIO_SYNC;
    extern              portMUX_TYPE    HW_TMR;

//────────────────────────────── ISR FUNCTIONS ────────────────────────────────

    void IRAM_ATTR SAL_CHK_ISR(void);  
//    void IRAM_ATTR SYS_CHK_ISR(void);
    void IRAM_ATTR TMR_CHK_ISR(void);  

#endif
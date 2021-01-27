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
    File:       Unit.h                -Header files needed for Unit.cpp.
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/    

#ifndef     _Unit_h_
#define     _Unit_

#include    "Constants.h"                                                   // Include Gloabal constants.

//───────────────────────────── UNIT VARIABLES ────────────────────────────────

extern  volatile    _Bool       INIT_PWR_UP_FLAG;
extern  volatile    _Bool       UNIT_WUP_FLAG;
extern  volatile    _Bool       LCD_BL_PWR_FLAG;
extern  volatile    _Bool       LCD_CTRL_PWR_FLAG;
extern  volatile    _Bool       LED_EN_FLAG;
extern  volatile    _Bool       LCD_DSP_SCR_1;
extern  volatile    _Bool       LCD_DSP_SCR_2;
extern  volatile    _Bool       LCD_DSP_SCR_3;

extern  volatile    uint32_t    PRVS_PULSE_CNT;                             // PReVious-PULSE-CouNT.
extern  volatile    uint32_t    CRNT_PULSE_CNT;                             // CuRreNT-PULSE-CouNT.
extern  volatile    uint32_t    SAL_ELAPSED_TME;                            // 32-Bit, ELAPSED-TiME in µS.                      
extern  volatile    _Bool       SAL_sPULSE_DET;                             // SALutron sPULSE-DETection.                       (NOTE: 1=When Signal is Present, 0=If no Signal.)
extern              _Bool       SAL_CHR_MODE;                               // SALutron-Contact-HR-MODE.
extern              _Bool       SAL_WHR_MODE;                               // SALutron-Wireless-HR-MODE.
extern              float       HR_Value;                                   // Calculated Heart-Rate.

extern  volatile    uint16_t    LCD_ON_TMR;                                 // LCD-DiSPlay-TiMeR, 1mS intervals.                (Default=0)


//────────────────────────────── UNIT CLASSES ─────────────────────────────────

extern      M5Display           LCD;
extern      RTC_TimeTypeDef     RTC_Time;
extern      RTC_DateTypeDef     RTC_Date;
extern      I2C_AXP192          PMIC;

//───────────────────────────── UNIT FUNCTIONS ────────────────────────────────

//extern  void    SAL_CHK_ISR(void);
extern  void    Logger_Init(void);                                          // INITialize SD-Logger.
extern  void    Log_Data(void);                                             // Write data to the SD-LOGger.
extern  float   Calculate_HR(void);                                         // Calculate the current Heat-Rate in BPM.
extern  void    WiFi_BT_ShutDown(void);                                     // Turns both WiFi & BlueTooth radio's off.
extern  void    Unit_ULP_WakeUp(void);                                      // Prepare Unit after DeepSleep to run.
extern  void    Unit_ULP_DeepSleep(void);                                   // Prepare Unit to enter DeepSleep.

extern  void    DisplaySplash(void);
extern  void    DisplayDefault(void);

#endif
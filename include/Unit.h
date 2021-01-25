/*
───────────────────────── M5 Salutron-Phantom-Detecter ────────────────────────

    This document contains confidential information and privileged material
    for the sole use of those authorized by True Fitness.  Any review, use,
    retention, distribution, or disclosure by anyone not authorized by True Fitness
    is strictly prohibited.  If you have a copy of this program/document
    and have not been authorized by True Fitness to possess it, please contact
    and return document(s) to True Fitness immediately.
    Copyright: True Fitness 2020-2021  All Rights Reserved.

───────────────────────────────────────────────────────────────────────────────

    Project:    M5 Salutron-Phantom-Detecter (M5-SPD)
    Author:     Mark Doane
    Date:       12/30/20
    File:       Device.h              -Header files needed for Device.cpp.
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

//──────────────────────────── DEVICE VARIABLES ───────────────────────────────

extern  volatile    uint32_t    UnitControl;                                
extern  volatile    uint32_t    PRV_PULSE_CNT;                              // PReVious-PULSE-CouNT.
extern  volatile    uint32_t    PULSE_CNT;                                  // Accumulated PULSE-CouNT.
extern  volatile    uint32_t    SAL_ELAPSED_TME;                            // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
extern              float       HR_Value;                                   // Calculated Heart-Rate.

extern              M5Display           LCD;
extern              RTC_TimeTypeDef     RTC_Time;
extern              RTC_DateTypeDef     RTC_Date;
extern              I2C_AXP192          PMIC;

//──────────────────────────── DEVICE FUNCTIONS ───────────────────────────────

extern  void    SAL_CHK_ISR(void);
extern  void    Logger_Init(void);                                      // INITialize SD-Logger.
extern  void    Log_Data(void);                                         // Write data to the SD-LOGger.
extern  float   Calculate_HR(void);                                     // Calculate the current Heat-Rate in BPM.
extern  void    WiFi_BT_ShutDown(void);                                 // Turns both WiFi & BlueTooth radio's off.
extern  void    Unit_ULP_WakeUp(void);                                  // Prepare Unit after DeepSleep to run.
extern  void    Unit_ULP_DeepSleep(void);                               // Prepare Unit to enter DeepSleep.

//extern    void    DisplaySplash(void);
//extern    void    DisplayDefault(void);

#endif
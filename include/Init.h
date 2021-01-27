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
    File:       Init.h                -Runs Setup for unit opperation.
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     _Init_h_
#define     _Init_h_

#include    "Constants.h"                                                   // Include Gloabal constants.

//─────────────────────────── UNIT-WAKEUP SERVICE ─────────────────────────────

#if(DEEPSLEEP_T)
void    UnitWakeUp(void)
{
    esp_sleep_wakeup_cause_t WAKEUP_SOURCE;
    WAKEUP_SOURCE=esp_sleep_get_wakeup_cause();
    switch(WAKEUP_SOURCE)
    {
        case ESP_SLEEP_WAKEUP_EXT0: 
        {
            
            break;
        }

        case ESP_SLEEP_WAKEUP_EXT1:
        {

            break;
        }

        case ESP_SLEEP_WAKEUP_ULP: 
        {

            break;
        }
        default:
        {
//            Serial.printf("Wakeup was not caused by deep sleep: %d\n",WAKEUP_SOURCE);
            break;
        }
    }
}
#endif



#endif
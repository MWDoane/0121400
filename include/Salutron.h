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
    File:       Salutron.h            -Headers associated with the Salutorn hardware.
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     _Salutron_h_
#define     _Salutron_h_
#include    "Constants.h"                                           // Include Gloabal constants.

//─────────────────────────── SALUTRON-CONSTANTS ──────────────────────────────


//─────────────────────────── SALUTRON-VARIABLES ──────────────────────────────

extern  float       HR_Value;


//──────────────────────── SALUTRON-FUNCTION PROTOTYPES ───────────────────────

bool    SalutronModeCheck(void);
bool    SalutronGetHR(void);


//────────────────────────── Salutron-DEFINITIONS ─────────────────────────────


//───────────────────────────── Salutron-MACROS ───────────────────────────────

#define     NoSalutronInput     ((digitalRead(SAL_PULSE))&&(digitalRead(SAL_MODE)))
#define     SalutronContact     ((!digitalRead(SAL_PULSE))&&(!digitalRead(SAL_MODE)))
#define     SalutronWireless     ((!digitalRead(SAL_PULSE))&&(digitalRead(SAL_MODE)))

//─────────────────────────────────────────────────────────────────────────────

/*
───────────────────────────────────────────────────────────────────────────────
CLEAR-CouNTs    If the CenTeR of the NAVigation-SWitch is pressed, the current 
                accumulated number of pulses counted and the previous counts
                are cleared.

Arguments:      None.

Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/
/*
void    ClearAcculatedCounts(void)
{
if(!digitalRead(PBTN_F))
    {   
      PULSE_CNT=CLEAR;  
      PRV_PULSE_CNT=CLEAR;  
    }
    return;
}   
*/
#endif

/* END OF FILE */
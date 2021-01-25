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
    File:       Salutron.h            -Constants, variables, prototypes needed for Salutron.cpp.
    Software:   1120400               -Software number.
    Board:      D-STIKE               -OLED Display, Three position switch, Neopixel LED, Various I/O.
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 1120400-REV-X.X.X MAIN.C FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     Salutron_h
#define     Salutron_h

#include    "Constants.h"

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

#endif

/* END OF FILE */
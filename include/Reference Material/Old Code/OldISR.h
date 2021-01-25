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
    File:       ISR.h                 
    Software:   1120400               -Software number.
    Board:      D-STIKE               -OLED Display, Three position switch, Neopixel LED, Various I/O.
       
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 1120400-REV-X.X.X MAIN.C FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     ISR_h
#define     ISR_h
#include    "Constants.h"

//────────────────────── FUNCTION PROTOTYPES ────────────────────────

extern  void    IRAM_ATTR NAV_CHK_ISR(void);

#endif
/* END OF FILE */
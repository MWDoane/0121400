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
    Date:       11/26/20
    File:       Generic.h
    Software:   1120400               -Software number.
    Board:      D-STIKE               -OLED Display, Three position switch, Neopixel LED, Various I/O.
    
    Software Supplement: 1120802 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 1120400-REV-X.X.X MAIN.C FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/
#ifndef     _Generic_h_
#define     _Generic_h_

//─────────────────────── GENERIC CONSTANTS ─────────────────────────

#define     DONE          (1u)         // Generic constant description
#define     YES           (1u)         // Generic constant description
#define     NO            (0u)         // Generic constant description
#define     TRUE          (1u)         // Generic constant description
#define     FALSE         (0u)         // Generic constant description
#define     ENABLE        (1u)         // Generic constant description
#define     DISABLE       (0u)         // Generic constant description
#define     _ENABLED      (1u)         // Generic constant description
#define     _DISABLED     (0u)         // Generic constant description
#define     READY         (1u)         // Generic constant description
#define     _WAIT         (0u)         // Generic constant description
#define     GO            (1u)         // Generic constant description
#define     START         (1u)         // Generic constant description
#define     _STOP         (0u)         // Generic constant description
#define     ON            (1u)         // Generic constant description
#define     OFF           (0u)         // Generic constant description 
#define     SET           (1u)         // Generic constant description
#define     CLEAR         (0u)         // Generic constant description
#define     RESET         (0u)         // Generic constant description
#define     VALID         (1u)         // Generic constant description
#define     INVALID       (0u)         // Generic constant description
#define     OPEN          (1u)         // Generic constant description
#define     CLOSE         (0u)         // Generic constant description
#define     PRESSED       (0)          // Generic constant description.
#define     RELEASED      (1)          // Generic constant description.
#define     ASCII_OFST    (0x30)       // ASCII-OFfSeT to subtract to get decimal number. 

//───────────────────────────────────────────────────────────────────

#endif
/* END OF FILE */

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

#include    "ISR.h"

/*
───────────────────────────────────────────────────────────────────────────────
SALutron-ChecK-ISR  Rising edge has been detected on the SAL_PULSE line.
                    Set the STOP-TiME to current time in µS. Set the ELAPSED-
                    TiME to the STOP-TiME - START-TiME.  Set the START-TiME
                    to current time.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR SAL_CHK_ISR(void)
{
    portENTER_CRITICAL(&GPIO_SYNC);
    SAL_STOP_TME=micros();
    SAL_ELAPSED_TME=(SAL_STOP_TME-SAL_START_TME);    
    SAL_START_TME=micros();
    pinMode(RED_LED,OUTPUT);
    digitalWrite(RED_LED,LOW);
    LED_ON_TMR=LED_ON_TME;
    PULSE_CNT++;
    SAL_SIG_DET=SET;
    portEXIT_CRITICAL(&GPIO_SYNC);    
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
BuTtoN-ChecK-ISR    CHecKs for when the M5 push BuTtoN is pressed, then CLEAR's
                    out the current and previous count registers.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR BTN_CHK_ISR(void)
{   
    portENTER_CRITICAL(&GPIO_SYNC);

//    if(PBTN_DB_TMR!=CLEAR)
//    {
        if(!digitalRead(PBTN_F))
        {
            if(!LCD_BL_PWR_FLAG)
            {
                LCD_ON_TMR=LCD_ON_TME;                
                portEXIT_CRITICAL(&GPIO_SYNC);        
                return;
            }
            if(PULSE_CNT)
            {
                PULSE_CNT=CLEAR;  
                PRV_PULSE_CNT=CLEAR;         
                LCD_ON_TMR=LCD_ON_TME;
                String EventCount=String(PULSE_CNT);            
                LCD.drawString(EventCount+"        ",55,25,2);   
//                PBTN_DB_TMR=PBTN_DB_TME;
            }
        }
        
        if(!digitalRead(PBTN_T))
        {   LCD_ON_TMR=LCD_ON_TME;  }
        
//    }

    portEXIT_CRITICAL(&GPIO_SYNC);        
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
SYStem-ChecK-ISR    A Falling edge has been detected on the SYS_INT line.
                    Determine the cause of the INTerrupt and take appropriate
                    actions.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR SYS_CHK_ISR(void)
{   
    portENTER_CRITICAL(&GPIO_SYNC);
    portEXIT_CRITICAL(&GPIO_SYNC);
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
TiMeR-ChecK-ISR     When the hardare timer fire an interrupt, the 1mS TiMeRs
                    are serviced.  All timers are count down.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR TMR_CHK_ISR(void)
{   
    portENTER_CRITICAL(&HW_TMR);

//────────────────────────── SERVICE PUSH-BUTTON-DE-BOUNCE-TIMER ─────────────────────────────

    if(PBTN_DB_TMR!=CLEAR)                          // Is the TiMeR CLEAR?
    {   LED_ON_TMR--;   }                           // If not, service the TiMeR.


//─────────────────────────────────────────────────────────────────────────────

//────────────────────────── SERVICE LED-ON-TIMER ─────────────────────────────

    if(LED_ON_TMR==CLEAR)                           // Is the LED-ON-TiMeR CLEAR?
    {                                               // If so,
        if(!digitalRead(RED_LED))                   // Is the LED already ON?
        {   
            digitalWrite(RED_LED,HIGH);             // If so, Turn the RED-LED OFF.
            pinMode(RED_LED,INPUT);                 // Set RED-LED pin back to an INPUT.
        }
    }
    else
    {   LED_ON_TMR--;   }                           // Else, service the TiMeR.


//─────────────────────────────────────────────────────────────────────────────


//────────────────────── SERVICE LCD-DISPLAY-ON-TIMER ─────────────────────────


    if(LCD_ON_TMR!=CLEAR)
    {   LCD_ON_TMR--;   }                                   // Else, service the TiMeR.

    portEXIT_CRITICAL(&HW_TMR);
    return;
}

//─────────────────────────────────────────────────────────────────────────────

/* END OF FILE */
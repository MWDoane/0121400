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
    File:       Constants.h           -Contains system constants used through the entire program.
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#ifndef     _Constants_h_
#define     _Constants_h_

#include    <esp_wifi.h>
#include    <esp_bt.h>
#include    <Arduino.h>
#include    <M5StickC.h>
#include    <M5Display.h>
#include    <I2C_AXP192.h>
#include    <IMU.h>
#include    <Wire.h>
#include    <RTC.h>
#include    "Generic.h"
#include    "stdio.h"
#include    "time.h"
#include    "TF_LOGO_3.h"                                       // True Fitness LOGO-3 table.

//──────────────────── UNIT-TEST DEFINITIONS ────────────────────────

#define     VCP_SD_LOG_T        (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control console communications-Testing of the SD card.
#define     VCP_STATE_T         (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control console communications-Testing.
#define     LCD_DSP_T           (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control LCD-Display-Test functions.
#define     DSP_SPLASH_T        (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control to Display the Splash Screen.
#define     DSP_MAIN_SCR        (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control to Display the Main SCReen.
#define     DEBUG_IO_T          (_DISABLED)                     // Change the valve to (_ENABLED or _DISABLED) for control DEBUG-Test-point-Inputs/Outputs.
#define     SD_LOGGER_T         (_DISABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control of the SD Data-LOGGER-Testing.
#define     RTC_T               (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control of the RTC-Testing.
#define     SET_RTC_T           (_DISABLED)                     // Change the valve to (_ENABLED or _DISABLED) for control of Setting-RTC-Testing.
#define     IMU_T               (_DISABLED)                     // Change the valve to (_ENABLED or _DISABLED) for control of IMU-Testing.
#define     DEEPSLEEP_T         (_DISABLED)                     // Change the valve to (_ENABLED or _DISABLED) for control of DEEP-SLEEP-Testing.
#define     PMIC_STATE_T        (_ENABLED)                      // Change the valve to (_ENABLED or _DISABLED) for control of PMIC-Testing.
#define     LCD_BL_T            (_DISABLED)                     // Change the valve to (_ENABLED or _DISABLED) for control of the LCD-BackLight-Testing.
#define     BIT_MACROS          (_DISABLED)                     // Change the valve to (_ENABLED or _DISABLED) for control of the BIT-MACROS.

//──────────────────────────── UNIT-MODULE NAMES ──────────────────────────────

#define     RTC                 M5.Rtc                          // Define the Real-Time-Clock.
#define     I2C                 Wire1                           // Define Wire-1 as I²C bus.
#define     VCP                 Serial                          // Define Serial port as Virtual-Communications-Port(VCP).
#define     SD_LGR              Serial2                         // Define Serial-2 port as SD-data-LoGgeR.

//──────────────────── PORT PIN DEFINITIONS ─────────────────────────

#define     GPIO_0              (0u)                            // GPIO-0       (USED)
#define     GPIO_1              (1u)                            // GPIO-1            
#define     GPIO_3              (3u)                            // GPIO-3            
#define     GPIO_5              (5u)                            // GPIO-5       (USED)
#define     GPIO_9              (9u)                            // GPIO-9       (USED)     
#define     GPIO_10             (10u)                           // GPIO-10      (USED)
#define     GPIO_13             (13u)                           // GPIO-13            
#define     GPIO_15             (15u)                           // GPIO-15      (USED)
#define     GPIO_18             (18u)                           // GPIO-18      (USED)
#define     GPIO_21             (21u)                           // GPIO-21      (USED)
#define     GPIO_22             (22u)                           // GPIO-22      (USED)
#define     GPIO_23             (23u)                           // GPIO-23            
#define     GPIO_26             (26u)                           // GPIO-26      (USED)
#define     GPIO_27             (27u)                           // GPIO-27
#define     GPIO_32             (32u)                           // GPIO-32      (USED)
#define     GPIO_33             (33u)                           // GPIO-33      (USED)      
#define     GPIO_34             (34u)                           // GPIO-34            
#define     GPIO_35             (35u)                           // GPIO-35      (USED)      
#define     GPIO_36             (36u)                           // GPIO-36
#define     GPIO_37             (37u)                           // GPIO-37      (USED)      
#define     GPIO_39             (39u)                           // GPIO-39      (USED)

//─────────────────── USED PORT PIN DEFINITIONS ─────────────────────

#define     TXO_TO_LGR          (GPIO_0)                        // TX-Out to SD-LoGgeR.                 (Hat Expansion Port)
#define     IR_LED              (GPIO_9)                        // Internal InfraRed-LED.
#define     RED_LED             (GPIO_10)                       // Internal RED-LED.
#define     SDA                 (GPIO_21)                       // SDA, I²C Serial DAta Line I/O.
#define     SCL                 (GPIO_22)                       // SCL, I²C Serial CLock OUTPUT.
#define     RXI_FROM_LGR        (GPIO_26)                       // RX-Input from SD-LoGgeR.             (Hat Expansion Port)
#define     SAL_PULSE           (GPIO_32)                       // SALutron-PULSE-Input.                (GROVE PORT)     (0x100000000)
#define     SAL_MODE            (GPIO_33)                       // SALutron-MODE-Input.                 (GROVE PORT)     (0x200000000)
#define     PBTN_F              (GPIO_37)                       // Front-Push-BuTtoN.                   (BUTTON_A)      (0x2000000000)
#define     PBTN_T              (GPIO_39)                       // Top--Push-BuTtoN.                    (BUTTON_B)      (0x8000000000)
#define     SYS_INT             (GPIO_35)                       // SYStemwide shared INTerrput input.                    (0x800000000)

//───────────────────── ISR-TIMER DEFINITIONS ───────────────────────

#define     AUTO_SLP_TME        (60000u)                    // AUOT-SLeeP-TiME in mS.
#define     PBTN_DB_TME         (100u)                      // Push-BuTtoN-De-Bouce-TiME in mS.
#define     LED_ON_TME          (15u)                       // LED-ON-TiME in mS.
#define     LCD_ON_INIT_TME     (15000u)                    // LCD-DiSPlay-TiME in mS.
#define     LCD_ON_TME          (7000u)                     // LCD-DiSPlay-TiME in mS.
#define     SD_LGR_TME          (250u)                      // SD-LOGger-Time-Out-TiME in mS. 

//──────────────────── VCP-Command DEFINITIONS ──────────────────────

#define     HOME_CURSOR         ("\e[1;1H")                 // HOME the CURSOR in the terminal.
#define     CLEAR_SCREEN        ("\e[2J\e[1;1H")            // CLEAR the SCREEN in the terminal.    

//─────────────────────── LCD DEFINITIONS ───────────────────────────

#define     LCD_BL_DIM          (2700u)                     // 2.700V for a DIM-LCD-Back-Light.
#define     LCD_BL_BRT          (2950u)                     // 2.950V for a BRighT-LCD-Back-Light.
#define     LCD_BL_OFF          (OFF)                       // Turn the LCD-Back-Light-OFF.
#define     LCD_CTRL_ON         (2700u)                     // 2.700V to turn ON the LCD-ConTRoLler.
#define     LCD_CTRL_OFF        (OFF)                       // Turn the LCD-ConTRoLler-OFF.

//─────────────────────── PMU DEFINITIONS ───────────────────────────

#define     SYS_PWR_ON          (3000u)                     // Turn ON SYStem-PoWeR.                                (DO NOT SET LOWER THAN 2.800V)
#define     SYS_LPWR_DS         (2800u)                     // Set SYStem-to-Low-PoWeR-Deep-Sleep voltage.          (DO NOT SET LOWER THAN 2.800V)
#define     EXT_5V_ON           (ON)                        // Turn ON the EXTernal 5V step-up supply.
#define     EXT_5V_OFF          (OFF)                       // Turn OFF the EXTernal 5V step-up supply.
#define     RTC_BCKUP_ON        (ON)                        // Turn ON the RTC-BaCK-UP battery.
#define     RTC_BCKUP_OFF       (OFF)                       // Turn OFF the RTC-BaCK-UP battery.
#define     GPIO_0_ON           (2800u)                     // Turn ON GPIO-0 and set to 2.800V.
#define     GPIO_0_OFF          (OFF)                       // Turn OFF GPIO-0.

//─────────────────────── IMU DEFINITIONS ───────────────────────────


//──────────────────── LCD-DiSPlay DEFINITIONS ──────────────────────

#define     SCREEN_WIDTH        (80u)                       // LCD DiSPlay width, in pixels.
#define     SCREEN_HEIGHT       (160u)                      // LCD DiSPlay height, in pixels.

//───────────────────── SALUTRON DEFINITIONS ────────────────────────

#define     MAX_SAL_SIG_TME     (25u)                       // SALutron-SIGnal-TiME to determine if Salutron is active in mS.

//─────────────────── UNIT-CONTROL DEFINITIONS ──────────────────────

/*
#define     SAL_sPULSE_DET      (8u)
#define     SAL_WHR_MODE        (9u)
#define     SAL_CHR_MODE        (10u)
#define     PRVS_PULSE_CNT      (8u)
#define     CRNT_PULSE_CNT      (8u)
*/


//──────────────────── DEEP-SLEEP DEFINITIONS ───────────────────────

#define     SAL_PULSE_WAKEUP    (2^SAL_PULSE)              // Position of the GPIO pin.
#define     SAL_MODE_WAKEUP     (2^SAL_MODE)               // Position of the GPIO pin.
#define     PBTN_F_WAKEUP       (2^PBTN_F)                 // Position of the GPIO pin.
#define     PBTN_T_WAKEUP       (2^PBTN_T)                 // Position of the GPIO pin.
#define     SYS_INT_WAKEUP      (2^SYS_INT)                // Position of the GPIO pin.
#endif

/* END OF FILE. */
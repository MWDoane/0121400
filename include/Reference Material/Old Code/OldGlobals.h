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
    File:       Globals.h
    Software:   1120400               -Software number.
    Board:      D-STIKE               -OLED Display, Three position switch, Neopixel LED, Various I/O.
    
    Software Supplement: 1120802 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 1120400-REV-X.X.X MAIN.C FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

//────────────────────────────── UNIT-INCLUDES ────────────────────────────────

#include    "Constants.h"
#include    <Wire.h>
#include    <Adafruit_NeoPixel.h>
#include    <OLEDDisplay.h>
#include    <SH1106Wire.h>
#include    <RTClib.h>
#include    "Salutron.h"
#include    "ESP32Ticker.h"


//──────────────────────────── GLOBAL VARIABLES ───────────────────────────────

// Timing related variables, used with millis().
                uint32_t    START_TME=CLEAR;                        // 32-Bit, Current micros START-TiME in µS.         (Default=0)
                uint32_t    STOP_TME=CLEAR;                         // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
                uint32_t    ELAPSED_TME=CLEAR;                      // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
                uint32_t    PULSE_HIGH_TME=CLEAR;                   // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
    volatile    uint8_t     NAV_DB_TMR=CLEAR;
    volatile    uint8_t     DSP_TMR=CLEAR;

// UNiT-MODE, may not need it.
/*
   struct
    {
        bool    Flag_0:     1;
        bool    Flag_1:     1;
        bool    Flag_2:     1;
    }_UNIT_MODE;
*/

// Salutron/HR related variables.
                float  PR_DSP_CNTR=CLEAR;                           // Pulse-Rate-DiSPlay-CouNTeR.
                float  PRV_PULSE_CNT=CLEAR;                         // PReVious-PULSE-CouNT.
                float  PULSE_CNT=CLEAR;                             // Accumulated PULSE-CouNT.
                float  HR_Value=CLEAR;                              // Calculated Heart-Rate.
                bool   SAL_SIG_DET=CLEAR;                           // SALutron SIGnal-DETection.                       (1=When a Signal is Present.)
                bool   CHR=CLEAR;                                   // State of the SALutron-MODE line.
                bool   WHR=CLEAR;                                   // State of the SALutron-MODE line.
        
// Data-Logger related variables.
                char        LOG_BFR[64]={CLEAR};                    // 64 byte RAM LOGging-BuFfeR.
                uint32_t    SD_LGR_TMR=CLEAR;                       // 8-Bit 1mS OPEN-LOG-TiMeR.    (Temp. uint32_t)
                bool        SD_LGR_STATE=CLEAR;                     // SD-LoGgeR-STATE bit.
                uint32_t    RTC_CHK_TMR=CLEAR;                      // 8-Bit 1mS OPEN-LOG-TiMeR.    (Temp. uint32_t)
                bool        RTC_STATE=CLEAR;                        // RTC-LoGgeR-STATE bit.
                uint8_t     PrevSecond=CLEAR;
                uint8_t     PrevDay=CLEAR;

    volatile    uint32_t    SAL_START_TME=CLEAR;                    // 32-Bit, Current micros START-TiME in µS.         (Default=0)
    volatile    uint32_t    SAL_STOP_TME=CLEAR;                     // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
    volatile    uint32_t    SAL_ELAPSED_TME=CLEAR;                       // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
    volatile    uint32_t    SAL_HIGH_TME=CLEAR;                     // 32-Bit, ELAPSED-TiME in µS.                      (Default=0)
    volatile    float       SAL_INT_HR=CLEAR;

//───────────────────── OLED-DiDPlay DEFINITIONS ─────────────────────────

#define     SCREEN_WIDTH        (128u)                       // OLED display width, in pixels.
#define     SCREEN_HEIGHT       (64u)                        // OLED display height, in pixels.
#define     OLED_DSP_SADDR      (0x3C)                       // OLED-DiSPlay Sub-ADDress.

//─────────────────────────── RGB-LED DEFINITIONS ─────────────────────────────

#define     LED_ON_TME          (125u)                       // LED-pixel-ON-TiME before changing color in init.
#define     LED_BLNK_TME        (50u)                        // LED-pixel-ON-BLiNK-TiME.
#define     LED_PXL_CNT         (1u)                         // LED-PiXeL-CouNT for the Adafruits NeoPixel Library.
#define     LED_PXL_NBR         (0u)                         // LED-PiXeL-NumBeR.
#define     RED_LED_ON          (128u)                       // RED-LED-ON Value.        (50% Intensity.)
#define     GRN_LED_ON          (128u)                       // GReeN-LED-ON Value.      (50% Intensity.)
#define     BLU_LED_ON          (128u)                       // BLUe-LED-ON Value.       (50% Intensity.)

//─────────────────── SALUTRON DEFINITIONS ────────────────────


#define     SAL_SIG_TME         (75000u)                     // SALutron-SIGnal-TiME to determine if Salutron is active.    (75mS)

//─────────────────── GENERAL UNIT DEFINITIONS ──────────────────────

#define     RTC_RPLY_TME        (250u)

//──────────────── UNIT-COMMUNICATION DEFINITIONS ───────────────────
#if(VCP_STATE)
    #define     VCP     Serial                               // Define Serial port as Virtual-Communications-Port(VCP).
#endif

#if(SD_LOGGER)
    #define     SD_LGR  Serial2                             // Define Serial2 port as SD-data-LoGgeR.
#endif

//────────────────── UNIT-PERIPHIAL DEFINITIONS ─────────────────────

#if(NEO_LED)
    // NeoPixel-RGB-LED, LED.  Adafruits NeoPixel Library.
    Adafruit_NeoPixel LED = Adafruit_NeoPixel(LED_PXL_CNT, LED_PXL_DO, NEO_GRB + NEO_KHZ800);
#endif

#if(_OLED_DSP)
    // SH1106 128x32 OLED, OLED_DSP.
    SH1106Wire OLED_DSP(OLED_DSP_SADDR, SCL, SDA);
#endif

#if(RTC_MODULE)
    // PCF8523 RTC-Module.
    RTC_PCF8523 RTC;
#endif

//────────────────────────── ISR SETUPS ─────────────────────────────

//portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;

Ticker  TMR_INT;
Ticker  DSP_INT;


//────────────────────── FUNCTION PROTOTYPES ────────────────────────

void    IRAM_ATTR SAL_CHK_ISR(void);  
void    IRAM_ATTR NAV_CHK_ISR(void);
void    TMR_CHK_ISR(void);
void    DSP_UPDATE(void);
void    WriteLOG(void);
void    ClearAcculatedCounts(void);
void    SET_LED(uint8_t,uint8_t,uint8_t,uint8_t);
void    SalutronStatusUpdate(void);
void    setup(void)                                       // setup Function Declaration.
{

//──────────────────── PORT PIN INITIALIZATION ──────────────────────

    pinMode (NAV_SW_RGT,INPUT_PULLUP);                    // Thumb-SWitch-1-RiGhT direction INPUT-PULLED-UP.  (Initialize as a HIGH to turn the Pull-Up ON)
    pinMode (NAV_SW_CTR,INPUT_PULLUP);                    // Thumb-SWitch-1-CenTeR press INPUT-PULLED-UP.     (Initialize as a HIGH to turn the Pull-Up ON)
    pinMode (NAV_SW_LFT,INPUT_PULLUP);                    // Thumb-SWitch-1-LeFT-direction INPUT-PULLED-UP.   (Initialize as a HIGH to turn the Pull-Up ON)    
    pinMode (LED_PXL_DO,OUTPUT);
    pinMode (GPIO_14,OUTPUT);
    pinMode (SAL_PULSE,INPUT_PULLUP);
    pinMode (SAL_MODE,INPUT_PULLUP);

//────────────────────── ISR INITIALIZATION ─────────────────────────

//    attachInterrupt(SAL_MODE,SAL_CHK_ISR,FALLING);
    attachInterrupt(SAL_PULSE,SAL_CHK_ISR,RISING);
    attachInterrupt(NAV_SW_CTR,NAV_CHK_ISR,FALLING);
    attachInterrupt(NAV_SW_LFT,NAV_CHK_ISR,FALLING);
    attachInterrupt(NAV_SW_RGT,NAV_CHK_ISR,FALLING);        

    TMR_INT.attach_ms(1,TMR_CHK_ISR);
    DSP_INT.attach_ms(250,DSP_UPDATE);

//────────────────────── LED INITIALIZATION ─────────────────────────

    LED.begin();
    SET_LED(RED_LED_ON,OFF,OFF,LED_ON_TME);
    SET_LED(OFF,GRN_LED_ON,OFF,LED_ON_TME);
    SET_LED(OFF,OFF,BLU_LED_ON,LED_ON_TME);
    SET_LED(RED_LED_ON,GRN_LED_ON,BLU_LED_ON,LED_ON_TME);
    SET_LED(OFF,OFF,OFF,OFF);
    LED.clear();

//─────────────── Virtual-Comm-Port INITIALIZATION ──────────────────

#if(VCP_STATE)
    VCP.begin(115200);
    #define   CRS_HOME          ("\e[1;1H")
    #define   CLR_SCR           ("\e[2J\e[1;1H")
#endif    

//───────────────────────── I²C Bus INITIALIZATION ────────────────────────────

    Wire.begin(SDA_0,SCL_0);

//──────────────────────── SD-LOGGER INITIALIZATION ───────────────────────────

#if(SD_LOGGER)

    SD_LGR.begin(115200); 
    SD_LGR_TMR=(millis()+250);
    while(millis()<SD_LGR_TMR)                            // Wait until OPENLOG response with a '<' character.
    {
        if(SD_LGR.available())                            // Wait for the OPENLOG to be ready.
        {                                                 // If it's ready,
            if(SD_LGR.read()=='<')                        // Did we get a ready response?
            {   break;  }                                 // If so, exit the Initialization.
        }
    }
    SD_LGR_STATE=SET;
    SD_LGR.write(26);                                     // This is the escape sequence to enter
    SD_LGR.write(26);                                     // into command mode to set file names,
    SD_LGR.write(26);                                     // directors, etc...

    SD_LGR_TMR=(millis()+250);
    while(millis()<SD_LGR_TMR)                             // Wait until OPENLOG response with a '>' character.
    {
        if(SD_LGR.available())                             // Wait for the OPENLOG to be ready.
        {                                                  // If it's ready,
            if(SD_LGR.read()=='>')                         // Did we get a Command ready response?
            {   break;  }                                  // If so, exit the Initialization.
        }
    }
    SD_LGR.print("append SLOG001.csv\r");

    SD_LGR_TMR=(millis()+250);
    while(millis()<SD_LGR_TMR)                             // Wait until OPENLOG response with a '<' character.
    {
        if(SD_LGR.available())                             // Wait for the OPENLOG to be ready.
        {                                                  // If it's ready,
            if(SD_LGR.read()=='<')                         // Did we get a Data ready response?
            {   break;  }                                  // If so, exit the Initialization.
        }
    }

#endif
//───────────────────── Real-Time-Clock INITIALIZATION ────────────────────────

#if(RTC_MODULE)
    PrevSecond=-1;
    RTC.begin();
//    if(!RTC.isrunning() || RTC.lostPower())
//    {   RTC.adjust(DateTime(F(__DATE__), F(__TIME__))); }
//    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    RTC.start();
    RTC.writeSqwPinMode(PCF8523_OFF);    
#endif              
//─────────────────────────────────────────────────────────────────────────────

//─────────────────────── OLED DiSPlay INITIALIZATION ─────────────────────────

    OLED_DSP.init();
    OLED_DSP.flipScreenVertically();
    OLED_DSP.setFont(ArialMT_Plain_10);
    delay(10);
    OLED_DSP.displayOn();
    OLED_DSP.drawString(0,20,"TRUE FITNESS");
    OLED_DSP.drawString(0,30,"Salutron Phantom Sniffer");
    
    DateTime CurrentTime=RTC.now();
    OLED_DSP.drawString(0,50,String(CurrentTime.month())+"-");                        // Print month.
    OLED_DSP.drawString(15,50,String(CurrentTime.day())+"-");                          // Print date (day of month).
    OLED_DSP.drawString(31,50,String(CurrentTime.year()));                           // Print Year.

    OLED_DSP.display();
    delay(2000);
    OLED_DSP.clear();
    OLED_DSP.drawString(0,0,"Pulse Rate:");  
    OLED_DSP.drawString(57,0,"--");
    OLED_DSP.drawString(0,10,"Count:");
    OLED_DSP.drawString(35,10,"--");
    OLED_DSP.drawString(0,20,"Mode:");
    OLED_DSP.drawString(32,20,"--");
    OLED_DSP.display();

//───────────────────────── BIT MANIPULATION MACROS ───────────────────────────

#if(BIT_MACROS)    
    #define     BIT_SET(a,b)        ((a) |= (1ULL<<(b)))             // SET-BIT b in register a.                         (Type=_Bool)
    #define     BIT_CLEAR(a,b)      ((a) &= ~(1ULL<<(b)))            // CLEAR-BIT b in register a.                       (Type=_Bool)
    #define     BIT_FLIP(a,b)       ((a) ^= (1ULL<<(b)))             // FLIP-BIT b in register a.                        (Type=_Bool)
    #define     BIT_CHECK(a,b)      ((a) & (1ULL<<(b)))              // CHECK BIT b in register a.                       (Type=_Bool)
#endif    
//─────────────────────────────────────────────────────────────────────────────
}

/*
───────────────────────────────────────────────────────────────────────────────
CLEAR-CouNTs    If the CenTeR of the NAVigation-SWitch is pressed, the current 
                accumulated number of pulses counted and the previous counts
                are cleared.

Arguments:      None.

Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/
void    ClearAcculatedCounts(void)
{
if(!digitalRead(NAV_SW_CTR))
    {   
      PULSE_CNT=CLEAR;  
      PRV_PULSE_CNT=CLEAR;  
    }
    return;
}   

/*
───────────────────────────────────────────────────────────────────────────────
SET-LED         SETs the LED to the RGB combination sent to it as an intensity
                level. (OFF=0, 100%=255)

Arguments:      RED- Reg LED die intensity.
                GRN- Green LED die intensity.
                BLU- BLUe LED die intensity.
             OnTime- Time in mS to keep the LED On
                     before it's next action.

Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/
void    SET_LED(uint8_t RED,uint8_t GRN, uint8_t BLU, uint8_t OnTime)
{
    LED.setPixelColor(LED_PXL_NBR,RED,GRN,BLU);
    LED.show();        
    delay(OnTime);
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
SALutron-ChecK-ISR  Rising edge has been detected on the SAL_PULSE line.
                    Set the STOP-TiME to current time in µS. Set the ELAPSED-
                    TiME to the STOP-TiME - START-TiME.  Set the START-TiME
                    to current time.

Arguments:      None.
Returns:        Nothing.

This may use a bit to determine if it should be run.
This will wake the unit up from sleep.
───────────────────────────────────────────────────────────────────────────────
*/

void    IRAM_ATTR SAL_CHK_ISR(void)
{
    SAL_STOP_TME=micros();
    SAL_ELAPSED=(SAL_STOP_TME-SAL_START_TME);
    SAL_START_TME=micros();
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
NAV-CHecK-ISR       A falling edge has been detected on one of the three input
                    from the NAVigate switch.

Arguments:      None.
Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/
/*
void    IRAM_ATTR NAV_CHK_ISR(void)
{
    digitalWrite(GPIO_14,HIGH);
    digitalWrite(GPIO_14,LOW);
    return;
}
*/
/*
───────────────────────────────────────────────────────────────────────────────
TiMeR-CHecK-ISR     CHecKs the 1mS based TiMeRs.  If they are not CLEAR, then
                    the TiMeR is decremented.

Arguments:      None.
Returns:        Nothing.

*** IMPORTANT TO KEEP ROUTINES SHORT ***
───────────────────────────────────────────────────────────────────────────────
*/

void    TMR_CHK_ISR(void)
{
    if(NAV_DB_TMR!=CLEAR)
    {   NAV_DB_TMR--;   }
    if(DSP_TMR!=CLEAR)        
    {   DSP_TMR--;   }    
    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
DiSPlay-UPDATE      UPDATEs the DiSPlay with the current information if the 
                    display is on.

Arguments:      None.
Returns:        Nothing.

───────────────────────────────────────────────────────────────────────────────
*/

void    DSP_UPDATE(void)
{
    digitalWrite(GPIO_14,HIGH);
    delay(15);
    digitalWrite(GPIO_14,LOW);
    return;
}

/*END OF FILE*/

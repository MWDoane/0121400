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
    File:       Globals.h             -Contains system variables and function prototypes used in the entire program.
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

//────────────────────────────── UNIT-INCLUDES ────────────────────────────────

#include    "Constants.h"                                       // Include Gloabal constants.

//──────────────────────── RTC-DEEP-SLEEP VARIABLES ───────────────────────────

RTC_DATA_ATTR   uint32_t    DS_PULSE_CNT;
RTC_DATA_ATTR   uint32_t    DS_PRV_PULSE_CNT;
RTC_DATA_ATTR   uint8_t     DS_OP_MODE;

//─────────────────────────────────────────────────────────────────────────────  

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

//──────────────────── UNIT-PERIPHIAL CLASS DEFINITIONS ───────────────────────

        RTC_TimeTypeDef     RTC_Time;
        RTC_DateTypeDef     RTC_Date;
        M5Display           LCD;
        TFT_eSprite         DSP_BFR=TFT_eSprite(&LCD);          // Setup the DSP_BFR for the LCD.
        extern const unsigned char TF_logo[9280];               // Spalsh Screen.
        
        I2C_AXP192          PMIC(I2C_AXP192_DEFAULT_ADDRESS, I2C);
//─────────────────────────────────────────────────────────────────────────────  

//─────────────────────────── ISR TIMER VARIABLES ─────────────────────────────

        portMUX_TYPE GPIO_SYNC=portMUX_INITIALIZER_UNLOCKED;    // Port-I/O interrupt synchronozation initialzer.
        portMUX_TYPE HW_TMR=portMUX_INITIALIZER_UNLOCKED;       // HW-TiMeR interrupt synchronozation initialzer.
        hw_timer_t * HW_TMR_0=NULL;                             // Setup the HW-TiMeR-0.


        volatile    uint8_t     PBTN_DB_TMR=CLEAR;              // Push-BuTtoN-De-Bounce-TiMeR, 1mS intervals.      (Default=0)
        volatile    uint8_t     LED_ON_TMR=CLEAR;               // LED-ON-TiMeR 1mS intervals.                      (Default=0)
        volatile    uint16_t    LCD_ON_TMR=CLEAR;               // LCD-DiSPlay-TiMeR, 1mS intervals.                (Default=0)

//─────────────────────────────────────────────────────────────────────────────  

//──────────────────────────── SALUTRON VARIABLES ─────────────────────────────

        volatile    uint16_t    SALUTRON_MODE=CLEAR;            // SALUTRON-MODE register.                          (Default=0)
        volatile    uint32_t    SAL_START_TME=CLEAR;            // SALutron-sPulse START-TiME.                      (Default=0)
        volatile    uint32_t    SAL_STOP_TME=CLEAR;             // SALutron-sPulse STOP-TiME.                       (Default=0)
        volatile    uint32_t    SAL_ELAPSED_TME=CLEAR;          // SALutron-sPulse ELAPSED-TiME.                    (Default=0)
        volatile    uint32_t    SAL_HIGH_TME=CLEAR;             // SALutron-sPulse START-TiME.                      (Default=0)
        volatile    _Bool       SAL_SIG_DET=CLEAR;              // SALutron SIGnal-DETection.                       (NOTE: 1=When a Signal is Present, Default=0)
                    _Bool       CHR=CLEAR;                      // State of the SALutron-MODE line.                 (Default=0)
                    _Bool       WHR=CLEAR;                      // State of the SALutron-MODE line.                 (Default=0)
                    float       HR_Value=CLEAR;                 // Calculated Heart-Rate.                           (Default=0)

        volatile    uint32_t    PRV_PULSE_CNT=CLEAR;            // PReVious-PULSE-CouNT.                            (Default=0)
        volatile    uint32_t    PULSE_CNT=CLEAR;                // Accumulated PULSE-CouNT.                         (Default=0)

//─────────────────────────────────────────────────────────────────────────────  

//─────────────────────────── SD-LOGGER VARIABLES ─────────────────────────────
                    
                    _Bool       SD_LGR_FLAG=CLEAR;              // SD-LoGgeR-FLAG bit.                              (Default=0)  
                    _Bool       SD_LGR_STATE=CLEAR;             // SD-LoGgeR-STATE bit.                             (Default=0)
                    char        LOG_BFR[512]={CLEAR};           // 512 byte RAM LOGging-BuFfeR.                     (Default=0)
                    uint32_t    SD_LGR_TMR=CLEAR;               // 32-Bit 1mS OPEN-LOG-TiMeR.                       (Temp. uint32_t, Default=0)

//─────────────────────────────────────────────────────────────────────────────  

//────────────────────────────── RTC VARIABLES ────────────────────────────────

                    uint8_t     PrevSecond=CLEAR;               // Previous Second byte.                            (Default=0)
                    uint8_t     PrevDay=CLEAR;                  // Previous Day byte.                               (Default=0)
                    uint32_t    RTC_CHK_TMR=CLEAR;              // 32-Bit 1mS OPEN-LOG-TiMeR.                       (Temp. uint32_t, Default=0)

//─────────────────────────────────────────────────────────────────────────────  

//────────────────────────────── IMU VARIABLES ────────────────────────────────

//─────────────────────────────────────────────────────────────────────────────  

//──────────────────────── GENERAL UNIT DEFINITIONS ───────────────────────────

        volatile    uint32_t    UnitControl;                    // Unit-Status control & status.

//─────────────────────────────────────────────────────────────────────────────

//─────────────────────────────────────────────────────────────────────────────  
//───────────────────────────── RTC DEFINITIONS ───────────────────────────────
//─────────────────────────────────────────────────────────────────────────────  
//───────────────────── UNIT-COMMUNICATION DEFINITIONS ────────────────────────
//─────────────────────────────────────────────────────────────────────────────  


//───────────────────────── ISR FUNCTION PROTOTYPES ───────────────────────────

void    IRAM_ATTR   SAL_CHK_ISR(void);                          // CHecK-SALutron-Interrupt-Service-Routine.  
void    IRAM_ATTR   SYS_CHK_ISR(void);                          // CHecK SYStem-Interrupt-Service Routine.
void    IRAM_ATTR   BTN_CHK_ISR(void);                          // CHecK BuTtoN-Interrupt-Service-Routine.
void    IRAM_ATTR   TMR_CHK_ISR(void);                          // CHecK TiMeR-Interrupt-Service-Routine.

//─────────────────────────────────────────────────────────────────────────────  

//────────────────────────── FUNCTION PROTOTYPES ──────────────────────────────

void    Logger_Init(void);                                      // INITialize SD-Logger.
void    Log_Data(void);                                         // Write data to the SD-LOGger.
float   Calculate_HR(void);                                     // Calculate the current Heat-Rate in BPM.
void    WiFi_BT_ShutDown(void);                                 // Turns both WiFi & BlueTooth radio's off.
void    Unit_ULP_WakeUp(void);                                  // Prepare Unit after DeepSleep to run.
void    Unit_ULP_DeepSleep(void);                               // Prepare Unit to enter DeepSleep.
void    setup(void)                                             // Setup Function Declaration.
{

//──────────────────────── M5STICK-C INITIALIZATION ───────────────────────────

    M5.begin(CLEAR,CLEAR,CLEAR);    

//─────────────────────────────────────────────────────────────────────────────  

//──────────────────────── PORT PIN INITIALIZATION ────────────────────────────

    pinMode(TXO_TO_LGR,OUTPUT);
    pinMode(RXI_FROM_LGR,INPUT);
    pinMode(RED_LED,OUTPUT);
    pinMode(PBTN_F,INPUT_PULLUP);
    pinMode(PBTN_T,INPUT_PULLUP);
    pinMode(SYS_INT,INPUT_PULLUP);
    pinMode(SAL_PULSE,INPUT);
    pinMode(SAL_MODE,INPUT);
        
//─────────────────────────────────────────────────────────────────────────────

//──────────────────── INTERRUPT SET-UP INITIALIZATION ────────────────────────

    if(bitRead(UnitControl,INIT_PWR_UP)==SET)
    {   attachInterrupt(SAL_PULSE,SAL_CHK_ISR,RISING);  }       // CHeck SALutron-sPULSE Interrupt input.
    attachInterrupt(SYS_INT,SYS_CHK_ISR,FALLING);               // CHeck SYStem shared Interrupt input.
    attachInterrupt(PBTN_F,BTN_CHK_ISR,FALLING);                // CHeck Push BuTtoN-Front Interrupt input.
    attachInterrupt(PBTN_T,BTN_CHK_ISR,FALLING);                // CHecK Push BuTtoN-Top Interrupt input.

    HW_TMR_0=timerBegin(0, 80, true);
    timerAttachInterrupt(HW_TMR_0,&TMR_CHK_ISR,true);
    timerAlarmWrite(HW_TMR_0,1000,true);
    timerAlarmEnable(HW_TMR_0);

//─────────────────────────────────────────────────────────────────────────────  


//──────────────────── Virtual-Comm-Port INITIALIZATION ───────────────────────


#if(VCP_STATE_T)
    VCP.begin(115200);
    VCP.flush();
    VCP.println("VCP Communications Enabled.");

#endif    

//─────────────────────────────────────────────────────────────────────────────  


//─────────────────── Power-Management-IC INITIALIZATION ──────────────────────

#if(PMIC_STATE_T)    
    I2C_AXP192_InitDef  PMU_INIT= 
    {   
        .EXTEN=EXT_5V_OFF,                                      // Turn the EXTeral-5V ENable OFF.
        .BACKUP=RTC_BCKUP_ON,                                   // Turn the RTC-Battery-BaCK-UP-ON.
        .DCDC1=3000,                                            // Set ESP32 primary valtage to 3.000Vdc.
        .DCDC2=0,                                               // Set DC-DC-2 to 0Vdc. 
        .DCDC3=0,                                               // Set DC-DC-3 to 0Vdc. 
        .LDO2=LCD_BL_OFF,                                       // Turn the LCD-Back-Light-OFF.
        .LDO3=2700,                                             // Set the LCD-Module voltage to 2.700Vdc.
        .GPIO0=MIC_PWR_OFF,                                     // Turn the MIC-PoWeR-OFF.
        .GPIO1=-1,                                              // GPIO-1, not used.    
        .GPIO2=-1,                                              // GPIO-2, not used.    
        .GPIO3=-1,                                              // GPIO-3, not used.    
        .GPIO4=-1,                                              // GPIO-4, not used.    
    };

    PMIC.begin(PMU_INIT);
    delay(500);
    #if(VCP_STATE_T)    
        VCP.println("PMU Enabled.");
    #endif    
#endif

//─────────────────────────────────────────────────────────────────────────────  

//───────────────────────── I²C Bus INITIALIZATION ────────────────────────────

#if((LCD_DSP_T || RTC_T))
    I2C.begin(SDA,SCL);
    #if(VCP_STATE_T)    
        VCP.println("I2C Bus Enabled.");
    #endif    
    delay(500);
#endif    

//─────────────────────────────────────────────────────────────────────────────    

//───────────────────── Real-Time-Clock INITIALIZATION ────────────────────────

#if(RTC_T)
    PrevSecond=-1;

#if(SET_RTC_T)
    hh = conv2d(__TIME__), 
    mm = conv2d(__TIME__ + 3), 
    ss = conv2d(__TIME__ + 6);                                              // Get H, M, S from compile time
    RTC_Time.Hours   = hh;
    RTC_Time.Minutes = mm;
    RTC_Time.Seconds = ss;
//    RTC_Time.Hours   = 17;
//    RTC_Time.Minutes = 47;
//    RTC_Time.Seconds = 30;
    M5.Rtc.SetTime(&RTC_Time);
    RTC_Date.Month=01;
    RTC_Date.Date=24;
    RTC_Date.Year=2021;
    M5.Rtc.SetData(&RTC_Date);
#endif

    RTC.GetTime(&RTC_Time);                                                 // Read the current Time.
    RTC.GetData(&RTC_Date);                                                 // Read the current Date.
    #if(VCP_STAT_T)
    VCP.printf("RTC Set & Enabled.\r\n");                                   // Print this to the VCP.
    VCP.print(String(RTC_Date.Month)+"-"+                                   // Print the Month '-'.
              String(RTC_Date.Date)+"-"+                                    // Print the Date '-'.
              String(RTC_Date.Year)+",");                                   // Print the Year ','.
    VCP.print(String(RTC_Time.Hours)+":");                                  // Print hour ':'.
    if (RTC_Time.Minutes<10)                                                // Are the minutes are < 10?
      { VCP.print('0'); }                                                   // If so, print leading '0' for minutes.
    VCP.print(String(RTC_Time.Minutes)+":");                                // Else, print minutes ':'.
    if (RTC_Time.Seconds<10)                                                // Are the seconds are < 10?
      { VCP.print('0'); }                                                   // Print leading '0' for seconds.
    VCP.print(String(RTC_Time.Seconds)+"\r\n");                             // Else, print seconds.
    #endif    
#endif              

//─────────────────────────────────────────────────────────────────────────────

//─────────────────────── LCD DISPlAY INITIALIZATION ──────────────────────────

//    DisplaySplash();

#if(DSP_LOGO_T)
    LCD.begin();
    #if(VCP_STAT_T)
        VCP.println("Display Enabled.");
    #endif    
    delay(500);
    LCD.setRotation(1);
    LCD.fillScreen(BLUE);
    PMIC.setLDO2(LCD_BL_BRT);
    LCD.pushImage(0, 12, logoWidth, logoHeight, (uint16_t *)TF_logo);
    LCD.setTextColor(YELLOW);
    delay(3000); 
    LCD.drawString("M5-SPD   0121400-1.0.0",10,45,2);  
    LCD.drawString(String(RTC_Date.Month)+"-"+ 
                   String(RTC_Date.Date)+"-" + 
                   String(RTC_Date.Year),10,60,2);
    PMIC.setEXTEN(EXT_5V_ON);
    delay(2000);
    PMIC.setLDO2(LCD_BL_DIM);       
    LCD.fillScreen(BLACK);
    LCD.setTextColor(WHITE,BLACK);
#endif

#if(LCD_TXT_DSP_T)
    LCD.begin();
    VCP.println("Display Enabled.");
    delay(500);
    LCD.setRotation(1);
    LCD.fillScreen(BLUE);
    LCD.setTextColor(CYAN);
    PMIC.setLDO2(LCD_BL_DIM);
    LCD.drawString("TRUE FITNESS",4,5,4);
    LCD.setTextColor(YELLOW);
    LCD.drawString("M5-STS   REV-1.0.0",10,45,2);  
    LCD.drawString(String(RTC_Date.Month)+"-"+ 
                   String(RTC_Date.Date)+"-" + 
                   String(RTC_Date.Year),10,60,2);
    PMIC.setEXTEN(EXT_5V_ON);
    delay(3000);
    LCD.fillScreen(BLACK);
    LCD.setTextColor(WHITE,BLACK);

#endif    

//─────────────────────────────────────────────────────────────────────────────

//──────────────────────── SD-LOGGER INITIALIZATION ───────────────────────────

#if(SD_LOGGER_T)
    SD_LGR.begin(115200,SERIAL_8N1,RXI_FROM_LGR,TXO_TO_LGR);
    delay(250);
    VCP.print("Logger Enabled.\r\n");
    SD_LGR_STATE=CLEAR;                                         // CLEAR the SD-LoGgeR-STATE.
    SD_LGR_TMR=(millis()+SD_LGR_TME);
    while(millis()<SD_LGR_TMR)                                  // Wait until OPENLOG response with a '<' character.
    {
        if(SD_LGR.available())
        {
            if(SD_LGR.read()=='<')                              // Did we get a ready response?
            {   
                SD_LGR_STATE=SET;                               // If so, SET the SD-LoGgeR-STATE.
                VCP.print("SD Ready.\r\n");                
                break;                                          // and exit.
            }
        }      
    }

    if(SD_LGR_STATE)
    {
        SD_LGR.write(26);                                       // This is the escape sequence to enter
        SD_LGR.write(26);                                       // into command mode to set file names,
        SD_LGR.write(26);                                       // directors, etc...
        SD_LGR_STATE=CLEAR;                                     // CLEAR the SD-LoGgeR-STATE.
        SD_LGR_TMR=(millis()+SD_LGR_TME);
        while(millis()<SD_LGR_TMR)                              // Wait until OPENLOG response with a '>' character.
        {
            if(SD_LGR.available())
            {
                if(SD_LGR.read()=='>')                              // Did we get a Command ready response?
                {   
                    SD_LGR_STATE=SET;                               // If so, SET the SD-LoGgeR-STATE.
                    VCP.print("SD Entering Command Mode...\r\n");                                    
                    break;                                          // and exit.
                }                                 
            }    
        }
    }
    
    if(SD_LGR_STATE)
    {
        SD_LGR.print("append SLOG001.csv\r");
        SD_LGR_STATE=CLEAR;                                     // CLEAR the SD-LoGgeR-STATE.        
        SD_LGR_TMR=(millis()+SD_LGR_TME);
        while(millis()<SD_LGR_TMR)                              // Wait until OPENLOG response with a '<' character.
        {
            if(SD_LGR.available())
            {            
                if(SD_LGR.read()=='<')                              // Did we get a Data ready response?
                {
                    SD_LGR_STATE=SET;                               // If so, SET the SD-LoGgeR-STATE.
                    VCP.print("SD Ready to receive data.\r\n");                                    
                    break;                                          // and exit.
                }                    
            }
        }
    }    
#endif

//─────────────────────────────────────────────────────────────────────────────

//─────────────────────── DEFAULT SCREEN INITIALIZATION ───────────────────────

//    DisplayDefault();
#if(DSP_MAIN_SCR)
    PULSE_CNT=CLEAR;
    LCD.drawString("Pulse Rate:",10,10,2);
    LCD.drawString("--   ",85,10,2);
    LCD.drawString("Count:",10,25,2);
    String EventCount=String(PULSE_CNT);            
    LCD.drawString(EventCount+"     ",55,25,2);
    LCD.drawString("Mode:",10,40,2);
    LCD.drawString("--       ",50,40,2);
    PRV_PULSE_CNT=PULSE_CNT;
    bitClear(UnitControl,SAL_WHR_MODE);
    bitClear(UnitControl,SAL_CHR_MODE);
    CHR=CLEAR;
    WHR=CLEAR;
    HR_Value=CLEAR;
    SAL_SIG_DET=CLEAR;
    SAL_ELAPSED_TME=CLEAR;
    if(bitRead(UnitControl,INIT_PWR_UP))
    {   attachInterrupt(SAL_PULSE,SAL_CHK_ISR,RISING);  }       // CHeck SALutron-sPULSE Interrupt input.
    bitClear(UnitControl,INIT_PWR_UP);
    LCD_ON_TMR=LCD_ON_TME;
#endif    

//─────────────────────────────────────────────────────────────────────────────

//───────────────────────── BIT MANIPULATION MACROS ───────────────────────────

#if(BIT_MACROS)    
    #define     BIT_SET(a,b)        ((a) |= (1ULL<<(b)))             // SET-BIT b in register a.                         (Type=_Bool)
    #define     BIT_CLEAR(a,b)      ((a) &= ~(1ULL<<(b)))            // CLEAR-BIT b in register a.                       (Type=_Bool)
    #define     BIT_FLIP(a,b)       ((a) ^= (1ULL<<(b)))             // FLIP-BIT b in register a.                        (Type=_Bool)
    #define     BIT_CHECK(a,b)      ((a) & (1ULL<<(b)))              // CHECK BIT b in register a.                       (Type=_Bool)
#endif    

//─────────────────────────────────────────────────────────────────────────────

}
/*END OF FILE*/

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
    File:       STS.cpp               -SaluTron-Sniffer unit functions.
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    ***** SEE 0121400-REV-X.X.X main.cpp FOR REVISION DETAILS *****

─────────────────────────────────────────────────────────────────────
*/

#include    "Unit.h"


//─────────────────────────────────────────────────────────────────────────────
//                          DEVICE FUNCTIONS LIST
//─────────────────────────────────────────────────────────────────────────────
/*
    Calculate_HR:   
    Display Splash Screen:
    Display Default Screen:
    Display Power Screen:
    Display Data Transfer Screen:
    Unit_ULP_WakeUp:
    Unit_ULP_DeepSleep:
*/

/*
───────────────────────────────────────────────────────────────────────────────
Calculate-HR    Calculates the Heart-Rate based on the value of SALutron ELAPSED
                Time.  This is equal to the period of the pulse train.

Arguments:      None.

Returns:        The Calculated Heart-Rate in BPM.
───────────────────────────────────────────────────────────────────────────────
*/

float    Calculate_HR(void)
{
      HR_Value=(SAL_ELAPSED_TME/1000);
      HR_Value=((1/HR_Value)*60000);
      return HR_Value;
}      

/*
───────────────────────────────────────────────────────────────────────────────
DisplaySplash   Display's the True Fitness logo and the device name, software
                version, and the date.
Arguments:      None.
Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void    DisplaySplash(void)
{
    LCD.begin();
    VCP.println("Display Enabled.");
    delay(500);
    LCD.setRotation(1);
    LCD.fillScreen(BLUE);
    PMIC.setLDO2(LCD_BL_BRT);
    LCD.pushImage(0, 12, logoWidth, logoHeight, (uint16_t *)TF_logo);
    LCD.setTextColor(YELLOW);
    delay(4000); 
    LCD.drawString("M5-STS   REV-1.0.0",10,45,2);  
    LCD.drawString(String(RTC_Date.Month)+"-"+ 
                   String(RTC_Date.Date)+"-" + 
                   String(RTC_Date.Year),10,60,2);
    PMIC.setEXTEN(EXT_5V_ON);
    delay(2000);
    PMIC.setLDO2(LCD_BL_DIM);       
    LCD.fillScreen(BLACK);
    LCD.setTextColor(WHITE,BLACK);
    return;
}


/*
───────────────────────────────────────────────────────────────────────────────
DisplayDefault  Display's the Default screen showing Pulse Rate, number of
                counts, and the current mode of the Salutron.

Arguments:      None.
Returns:        Nothing.
───────────────────────────────────────────────────────────────────────────────
*/

void    DisplayDefault(void)
{
    PULSE_CNT=CLEAR;
    LCD.drawString("Pulse Rate:",10,10,2);
    LCD.drawString("--   ",85,10,2);
    LCD.drawString("Count:",10,25,2);
    String EventCount=String(PULSE_CNT);            
    LCD.drawString(EventCount+"     ",55,25,2);
    LCD.drawString("Mode:",10,40,2);
    LCD.drawString("--       ",50,40,2);
    PRV_PULSE_CNT=PULSE_CNT;

//    CHR=CLEAR;
//    WHR=CLEAR;
    HR_Value=CLEAR;
//    SAL_SIG_DET=CLEAR;
    SAL_ELAPSED_TME=CLEAR;
//    if(DEVICE_MODE.STARTUP_MODE)
    if(bitRead(UnitControl,INIT_PWR_UP))    
    {   attachInterrupt(SAL_PULSE,SAL_CHK_ISR,RISING);  }       // CHeck SALutron-sPULSE Interrupt input.
//    DEVICE_MODE.STARTUP_MODE=CLEAR;    
    bitClear(UnitControl,INIT_PWR_UP);

    return;
}

/*
───────────────────────────────────────────────────────────────────────────────
LPM-WakeUp  Determines the source of the Low-Power-Mode-Wake-Up and displays
            the information on the terminal.

Arguments:      None.

Returns:        Source of Wake-Up.
───────────────────────────────────────────────────────────────────────────────
*/
/*
void    Unit_ULP_WakeUp(void)
{
    esp_sleep_wakeup_cause_t WAKEUP_SOURCE;
    WAKEUP_SOURCE=esp_sleep_get_wakeup_cause();
    switch(WAKEUP_SOURCE)
    {
        case ESP_SLEEP_WAKEUP_EXT0: 
        {   
//            esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_EXT0);
            PWR_INIT=CLEAR;
            pinMode(RED_LED,OUTPUT); 
            digitalWrite(RED_LED,LOW);            
            delay(50);
            digitalWrite(RED_LED,HIGH);                        
            pinMode(RED_LED,INPUT);             
        }
        break;
        
        case ESP_SLEEP_WAKEUP_EXT1:
        {
//            esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_EXT1);
            PWR_INIT=CLEAR; 
            pinMode(RED_LED,OUTPUT);             
            digitalWrite(RED_LED,LOW);            
            delay(50);
            digitalWrite(RED_LED,HIGH);                        
            delay(125);
            digitalWrite(RED_LED,LOW);            
            delay(50);
            digitalWrite(RED_LED,HIGH);         
            pinMode(RED_LED,INPUT);                                        
        }
        break;

        case ESP_SLEEP_WAKEUP_TIMER:
        {
            PWR_INIT=CLEAR; 
            pinMode(RED_LED,OUTPUT);
            if(!digitalRead(PBTN_F))
            {
                digitalWrite(RED_LED,LOW);            
                delay(50);
                digitalWrite(RED_LED,HIGH);                        
                delay(125);
                digitalWrite(RED_LED,LOW);            
                delay(50);
                digitalWrite(RED_LED,HIGH);     
            }
            if(!digitalRead(PBTN_T))
            {
                digitalWrite(RED_LED,LOW);            
                delay(50);
                digitalWrite(RED_LED,HIGH);                        
                delay(125);
                digitalWrite(RED_LED,LOW);            
                delay(50);
                digitalWrite(RED_LED,HIGH);                        
                delay(125);
                digitalWrite(RED_LED,LOW);            
                delay(50);
                digitalWrite(RED_LED,HIGH);                                        
                                   
            }
            pinMode(RED_LED,INPUT);
        }
        break;

        case ESP_SLEEP_WAKEUP_TOUCHPAD: break;
        case ESP_SLEEP_WAKEUP_ULP: break;
        default: break;
    }
}

void    Unit_ULP_DeepSleep(void)
{
    pinMode(0,INPUT);  pinMode(9,INPUT);  pinMode(10,INPUT); pinMode(5,INPUT);  pinMode(13,INPUT);
    pinMode(15,INPUT); pinMode(23,INPUT); pinMode(34,INPUT); pinMode(32,INPUT_PULLUP); pinMode(33,INPUT_PULLUP);
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_32,0); //1 = High, 0 = Low
//    esp_sleep_enable_ext1_wakeup(PBTN_F_WAKEUP,ESP_EXT1_WAKEUP_ALL_LOW); //1 = High, 0 = Low
    adc_power_off();

//    DEVICE_MODE.SLEEP_MODE=SET;
    DS_PULSE_CNT=PULSE_CNT;
    DS_PRV_PULSE_CNT=PRV_PULSE_CNT;
    DS_OP_MODE=0x02;
//    DS_OP_MODE=DEVICE_MODE.SLEEP_MODE;
    esp_sleep_pd_config(ESP_PD_DOMAIN_MAX,ESP_PD_OPTION_AUTO); 
    esp_deep_sleep_start();
    delay(100);
    return;
}
*/





/*END OF FILE*/
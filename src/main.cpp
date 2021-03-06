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
    File:       Main.c
    Software:   0121400               -Software number.
    Board:      M5Stick-C             -Color Display, WiFi, Bluetooth, Three switchs, Red & Ir LEDs, IMU, PMU, RTC, Various I/O.
                                       will include an external 18650 Hat, and a proto Hat with the µSD data logger.  Interface
                                       to the Salutron will be through the "GROVE" header.

    Software Supplement: 0121800 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    01/01/21    0121400-REV-1.0.0.
                -Initial Software build.  Goal is to connect the
                 Salutron to the M5Stick-C board and measure both
                 contact and wireless heart rate and display
                 the value on the OLED.  The RED LED will flash at 
                 the current heart rate.  Write the event to the
                 SD card until the events halt.  The IMU will look
                 for any motion on the machine and ignore the 
                 event recording until the unit is stable.

─────────────────────────────────────────────────────────────────────
*/

#include    "Globals.h"
#include    "Salutron.h"

void loop(void)
{
  while(ON)
  {
    do 
    {
      // Check for No-Salutron Detection.
      // Both the PULSE & MODE lines are HIGH.
      if(NoSalutronInput)
      {
        if((PRVS_PULSE_CNT==CRNT_PULSE_CNT))
        {
          if(SAL_sPULSE_DET)
          {
            LCD.drawString("Pulse Rate:",10,10,2);
            LCD.drawString("--   ",85,10,2);
            LCD.drawString("Count:",10,25,2);
            String EventCount=String(CRNT_PULSE_CNT);            
            LCD.drawString(EventCount+"     ",55,25,2);
            LCD.drawString("Mode:",10,40,2);
            LCD.drawString("--       ",50,40,2);
            PRVS_PULSE_CNT=CRNT_PULSE_CNT;
            SAL_CHR_MODE=CLEAR;
            SAL_WHR_MODE=CLEAR;
            HR_Value=CLEAR;
//            SAL_sPULSE_DET=CLEAR;
            SAL_ELAPSED_TME=CLEAR;
          }
        }  
      }

      // Check for Salutron Contact Detection.
      // Both PULSE & MODE lines are LOW.
      else if(SalutronContact)
        {
          LCD.drawString("Pulse Rate:",10,10,2);
          LCD.drawString("Count:",10,25,2);
          LCD.drawString("Mode:",10,40,2);
/*
          if(WHR)
          {
            LCD.drawString("--   ",85,10,2);
            String EventCount=String(CRNT_PULSE_CNT);                   
            LCD.drawString(EventCount+"     ",55,25,2);
            LCD.drawString("Wireless",50,40,2);
            CHR=SET;  WHR=CLEAR;            
            PRVS_PULSE_CNT=CRNT_PULSE_CNT;                    
          }

          else if(!WHR)
          {
*/            
            String PulseRate=String(HR_Value,0);
            if(!(CRNT_PULSE_CNT>=(PRVS_PULSE_CNT+3)))
              {   LCD.drawString("--   ",85,10,2);   }
            else
              {   LCD.drawString(PulseRate+"   ",85,10,2);  }
            String EventCount=String(CRNT_PULSE_CNT);          
            LCD.drawString(EventCount+"     ",55,25,2);
            LCD.drawString("Contact ",50,40,2);
            if(!SAL_CHR_MODE)      
            {
              SAL_CHR_MODE=SET;  
              SAL_WHR_MODE=CLEAR;        
            }
            
//          }  
        }

        // Check for Salutron Wireless Detection.
        // PULSE line LOW and the MODE line HIGH.
        // Contact Mode has priority.
        else if(SalutronWireless)
        {
          LCD.drawString("Pulse Rate:",10,10,2);
          LCD.drawString("Count:",10,25,2);
          LCD.drawString("Mode:",10,40,2);
          String PulseRate=String(HR_Value,0);
          LCD.drawString("Pulse Rate:",10,10,2);
          if(!(CRNT_PULSE_CNT>=(PRVS_PULSE_CNT+3)))
            {   LCD.drawString("--   ",85,10,2);    }
          else
            {   LCD.drawString(PulseRate+"  ",85,10,2);  }
          LCD.drawString("Count:",10,25,2);
          String EventCount=String(CRNT_PULSE_CNT);
          LCD.drawString(EventCount+"     ",55,25,2);
          LCD.drawString("Mode:",10,40,2);
          LCD.drawString("Wireless",50,40,2);
          if(!SAL_WHR_MODE)      
          {
            SAL_CHR_MODE=CLEAR;  
            SAL_WHR_MODE=SET;        
          }
        }

      Calculate_HR();

//─────────────────────────────────────────────────────────────────────────────    
// COM PORT TEST:     For Debugging whats getting written to the SD Card.
//─────────────────────────────────────────────────────────────────────────────    

#if(VCP_SD_LOG_T)
      if(SAL_sPULSE_DET)
      {
        RTC.GetTime(&RTC_Time);
        if (RTC_Time.Seconds!=PrevSecond)                                         // Have the seconds changed?
        {
          RTC.GetData(&RTC_Date);                                                 // Update all the RTC Date registers.
          if(RTC_Date.Date != PrevDay)                                            // If this is a different day,
          {                                                                       // Log the new day.
            VCP.print(String(RTC_Date.Month)+"-"+ 
                         String(RTC_Date.Date)+"-"+ 
                         String(RTC_Date.Year)+"\r\n");
            PrevDay=RTC_Date.Date;                                               // And set Previous Day to current day.
          }

          VCP.print(String(RTC_Time.Hours)+":");                                  // Print hour.
          if (RTC_Time.Minutes<10)                                                // Are the minutes are < 10?
            { VCP.print('0'); }                                                   // If so, print leading '0' for minutes.
          VCP.print(String(RTC_Time.Minutes)+":");                                // Else, print minutes.
          if (RTC_Time.Seconds<10)                                                // Are the seconds are < 10?
            { VCP.print('0'); }                                                   // Print leading '0' for seconds.
          VCP.print(String(RTC_Time.Seconds)+",");                                // Else, print seconds.
          if(!(CRNT_PULSE_CNT>=(PRVS_PULSE_CNT+3)))
          {   VCP.printf("-,");    }
          else
          {   VCP.printf("%d,",(uint)HR_Value);   }
          VCP.printf("%d,",(uint)CRNT_PULSE_CNT);
          if(SAL_WHR_MODE)
          { VCP.print("WHR\r\n"); }
          if(SAL_CHR_MODE)
          {   VCP.print("CHR\r\n");   }
          else if(!(SAL_CHR_MODE || SAL_WHR_MODE))
          {   VCP.print("-\r\n");   }
          VCP.printf("%d,",LCD_ON_TMR);
          VCP.printf("%d,",LED_ON_TMR);
          VCP.printf("%d,",SAL_HIGH_TMR);
          PrevSecond=RTC_Time.Seconds;
        }  
      }
#endif

//─────────────────────────────────────────────────────────────────────────────    
// SD Card Logging:   Writting the data to the SD Card.
//─────────────────────────────────────────────────────────────────────────────    

#if(SD_LOGGER_T)
      if(SAL_sPULSE_DET)
      {
        RTC.GetTime(&RTC_Time);                                          // Update all the RTC Time registers.
        if (RTC_Time.Seconds != PrevSecond)                                 // If current second and previous second
        {                                                                   // are equal exit.
          RTC.GetData(&RTC_Date);                                        // Update all the RTC Date registers.
          if(RTC_Date.Date != PrevDay)                                      // If this is a different day,
          {                                                                 // Log the new day.
            SD_LGR.print(String(RTC_Date.Month)+"-"+ 
                         String(RTC_Date.Date)+"-"+ 
                         String(RTC_Date.Year)+"\r\n");
            PrevDay=RTC_Date.Date;                                          // And set Previous Day to current day.
          }
          SD_LGR.print(String(RTC_Time.Hours)+":");                         // Log the hour.
          if (RTC_Time.Minutes < 10)                                        // Are the minutes are < 10?
            { SD_LGR.print("0"); }                                          // If so, send leading '0' for minutes.
          SD_LGR.print(String(RTC_Time.Minutes)+":");                       // Else, log the minutes.
          if (RTC_Time.Seconds < 10)                                        // Are the seconds are < 10?
            { SD_LGR.print("0"); }                                          // If so, send out a leading '0' for seconds.
          SD_LGR.print(String(RTC_Time.Seconds)+",");                       // Else, log the seconds.
          SD_LGR.printf("%d,",(uint)HR_Value);                              // Log the current Hear-Rate-Value.
          SD_LGR.printf("%d,",(uint)CRNT_PULSE_CNT);                        // Log the CuRreNT-PULSE-CouNT.
          if(SAL_WHR_MODE)
          { SD_LGR.print("WHR"); }
          if(SAL_CHR_MODE)
          {   SD_LGR.print("CHR");   }
          else if((!SAL_CHR_MODE)||(!SAL_WHR_MODE))
            {   SD_LGR.print("-");   }
          SD_LGR.print("\r\n");
          PrevSecond=RTC_Time.Seconds;                                      // Set previous seconds to current seconds.
        }
      }
#endif      

//─────────────────────────────────────────────────────────────────────────────    
// LCD ON Time Check:    
//─────────────────────────────────────────────────────────────────────────────    

#if(LCD_BL_T)
      if(LCD_ON_TMR==CLEAR)                                                       // Is the LCD-ON-TiMeR CLEAR?
      {
          if(LCD_BL_PWR_FLAG)
          {

              PMIC.setLDO2(LCD_BL_OFF);                                     // If so, Turn the LCD-Back-Light-OFF.
              PMIC.setLDO3(LCD_CTRL_OFF);
              LED_EN_FLAG=CLEAR;
              LCD_BL_PWR_FLAG=CLEAR;                                        // CLEAR the LCD-Back-Light-FLAG.
              LCD_CTRL_PWR_FLAG=CLEAR;                                      // CLEAR the LCD-ConTRoLler-PoWeR-FLAG.              
          }

      }
      if(LCD_ON_TMR!=CLEAR)
      {
        if(!LCD_BL_PWR_FLAG)
        {
          PMIC.setLDO3(LCD_CTRL_ON);                                      // Turn ON the LCD-ConTRoLler.                    
          PMIC.setLDO2(LCD_BL_DIM);       
          LED_EN_FLAG=SET;
          LCD_BL_PWR_FLAG=SET;
          LCD_CTRL_PWR_FLAG=SET;                                           // SET the LCD-ConTRoLler-PoWeR-FLAG.                        
        }
      }
#endif      
    } while(digitalRead(SAL_PULSE)==LOW);    
//    delay(MAX_SAL_SIG_TME);
  }    
}
/*END OF FILE */

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

    Project:    Portable Salutron Reader
    Author:     Mark Doane
    Date:       11/26/20
    File:       Main.c
    Software:   1120400               -Software number.
    Board:      D-STIKE               -OLED Display, Three position switch, Neopixel LED, Various I/O.
    
    Software Supplement: 1120802 REV-1.0.0.XLS.     (Yet to Be Created)
    
───────────────────────── REVISION RECORD ───────────────────────────
    
    11/26/20    1120400-REV-1.0.0.
                -Initial Software build.  Goal is to connect the
                Salutron to the D-STIKE board and measure both
                contact and wireless heart rate and display
                the value on the OLED.  The RED LED will flash at 
                the current heart rate.  Initial build works.

    12/11/20    1120400-REV-1.0.1.
                -All logging works.  Interrupt based pulse measurement
                 if more accurate so this will now be the source of the
                 Pulse rate generation.
                -Moving loop actions into functions for simplicity.  In
                 addition, .cpp & .h files will be created as needed to
                 seperate out the program.
                -Deep sleep is to be added so when no action is detected
                 on either Salutron lines the unit sleeps.  Any change on
                 either of those lines will wake the unit and resume
                 opperation.  This may require testing, but will be required
                 to reduce the unit's power draw.
                -Turning the display off after a set period of time.
                 action on the Navigation switch will turn the display on 
                 for a given time.  The display can be latch on/timed off when
                 commanded to by moving the switch to the right for 5 seconds.

─────────────────────────────────────────────────────────────────────
*/

#include  "Globals.h"
void  setup(void);
void loop() 
{
  do
  {
    // Check Salutron Input.
    do 
    {
      // Check for Navigation Switch center button push.
      ClearAcculatedCounts();                             
      
      // Check for No-Salutron Detection.
      // Both the PULSE & MODE lines are HIGH.
      if(NoSalutronInput)
      {
        if(!SAL_SIG_DET)
        {
          CHR=CLEAR;
          WHR=CLEAR;
          SET_LED(OFF,OFF,OFF,OFF);

          OLED_DSP.clear();
          delay(25);
          OLED_DSP.drawString(0,0,"Pulse Rate:");  
          OLED_DSP.drawString(57,0,"--");
          OLED_DSP.drawString(0,10,"Count:");
          String EventCount=String(PULSE_CNT,0);
          OLED_DSP.drawString(35,10,EventCount);
          OLED_DSP.drawString(0,20,"Mode:");
          OLED_DSP.drawString(32,20,"--");
          
          PRV_PULSE_CNT=PULSE_CNT;        
        }  
      }

      // Check for Salutron Contact Detection.
      // Both PULSE & MODE lines are LOW.
      else if(SalutronContact)
      {
        OLED_DSP.clear();
        OLED_DSP.drawString(0,0,"Pulse Rate:");  
        if(WHR)
        {
          OLED_DSP.drawString(57,0,"--");
          OLED_DSP.drawString(0,10,"Count:");
          String EventCount=String(PULSE_CNT,0);
          OLED_DSP.drawString(35,10,EventCount);
          OLED_DSP.drawString(0,20,"Mode:");
          OLED_DSP.drawString(32,20,"Contact");
          SAL_SIG_DET=SET;
          CHR=SET;
          WHR=CLEAR;            
          PRV_PULSE_CNT=PULSE_CNT;                    
        }
        else if(!WHR)
        {
          String PulseRate=String(HR_Value,0);
          if(!(PULSE_CNT>=(PRV_PULSE_CNT+3)))
            {   OLED_DSP.drawString(57,0,"--");   }
          else
            {   OLED_DSP.drawString(57,0,PulseRate);  }
          OLED_DSP.drawString(0,10,"Count:");
          String EventCount=String(PULSE_CNT,0);
          OLED_DSP.drawString(35,10,EventCount);
          OLED_DSP.drawString(0,20,"Mode:");
          OLED_DSP.drawString(32,20,"Contact");
          SAL_SIG_DET=SET;
          CHR=SET;
          WHR=CLEAR;
        }  
      }

      // Check for Salutron Wireless Detection.
      // PULSE line if LOW and the MODE line is HIGH.
      // Contact Mode has priority.
      else if(SalutronWireless)
      {
        SAL_SIG_DET=SET;
        CHR=CLEAR;
        WHR=SET;
        OLED_DSP.clear();
        delay(25);
        String PulseRate=String(HR_Value,0);
        OLED_DSP.drawString(0,0,"Pulse Rate:");  
        if(!(PULSE_CNT>=(PRV_PULSE_CNT+3)))
          {   OLED_DSP.drawString(57,0,"--");    }
        else
          {   OLED_DSP.drawString(57,0,PulseRate);  }
        OLED_DSP.drawString(0,10,"Count:");
        String EventCount=String(PULSE_CNT,0);
        OLED_DSP.drawString(35,10,EventCount);
        OLED_DSP.drawString(0,20,"Mode:");  
        OLED_DSP.drawString(32,20,"Wireless");      
      }
      OLED_DSP.display();      
//      digitalWrite(GPIO_14,LOW);             
    } while(!digitalRead(SAL_PULSE));

//─────────────────────────── PULSE-LINE IS HIGH ──────────────────────────────

    STOP_TME=micros();
    ELAPSED_TME=(STOP_TME-START_TME);
    START_TME = micros();
//    digitalWrite(GPIO_14,HIGH);    
    PULSE_HIGH_TME=(START_TME+SAL_SIG_TME);

    do
    {
      if(micros()>=PULSE_HIGH_TME)
      {   SAL_SIG_DET=CLEAR;  break;  }
    }
    while(digitalRead(SAL_PULSE));

    if(SAL_SIG_DET)
    {
      SET_LED(RED_LED_ON,OFF,OFF,OFF);
      PULSE_CNT++;
      HR_Value=CLEAR;
      if((PULSE_CNT>=(PRV_PULSE_CNT+3)))
      {
        HR_Value=(ELAPSED_TME/1000);
        HR_Value=((1/HR_Value)*60000);
      }
    }

// COM PORT: For Debugging whats getting written to the SD Card.
#if(VCP_STATE)

  if(SAL_SIG_DET)
  {
    if((PULSE_CNT>=(PRV_PULSE_CNT+3)))
    {
    DateTime CurrentTime=RTC.now();
    if (CurrentTime.second() != PrevSecond)                                     // Have the seconds changed.
      {
        VCP.print(String(CurrentTime.month())+"-");                             // Print month.
        VCP.print(String(CurrentTime.day())+"-");                               // Print date (day of month).
        VCP.print(String(CurrentTime.year())+",");                              // Print date.
        VCP.print(String(CurrentTime.hour())+":");                              // Print hour.
        if (CurrentTime.minute() < 10)                                          // Are the minutes are < 10?
          { VCP.print('0'); }                                                   // If so, print leading '0' for minutes.
        VCP.print(String(CurrentTime.minute())+":");                            // Else, print minutes.
        if (CurrentTime.second() < 10)                                          // Are the seconds are < 10?
          { VCP.print('0'); }                                                   // Print leading '0' for seconds.
        VCP.print(String(CurrentTime.second())+",");                            // Else, print seconds.
        VCP.print(HR_Value,0);
        VCP.print(",");
        VCP.print(PULSE_CNT,0);
        VCP.print(",");        
        if(WHR)
        { VCP.print("WHR"); }
        if(CHR)
        {   VCP.print("CHR");   }
        else if(!(CHR || WHR))
        {   VCP.print("-");   }
        VCP.print(" ");
        float SAL_INT_PERIOD=SAL_ELAPSED_TME;
        SAL_INT_PERIOD=(SAL_INT_PERIOD/1000);
        SAL_INT_HR=((1/SAL_INT_PERIOD)*60000);
        VCP.println(SAL_INT_HR,0);
      }  
   
#endif

// SD Card: Writting the information to the SD Card.
#if(SD_LOGGER)
      if(SAL_SIG_DET)
      {
        DateTime CurrentTime=RTC.now();                                         // Update all the RTC registers.
        if (CurrentTime.second() != PrevSecond)
        {
          if(CurrentTime.day() != PrevDay)
          {
            SD_LGR.print(String(CurrentTime.month())+"-");                        // Print month.
            SD_LGR.print(String(CurrentTime.day())+"-");                          // Print date (day of month).
            SD_LGR.println(String(CurrentTime.year()));                           // Print Year.
            PrevDay=CurrentTime.day();
          }
          SD_LGR.print(String(CurrentTime.hour())+":");                         // Print hour.
          if (CurrentTime.minute() < 10)                                        // Are the minutes are < 10?
            { SD_LGR.print('0'); }                                              // If so, print leading '0' for minutes.
          SD_LGR.print(String(CurrentTime.minute())+":");                       // Else, print minutes.
          if (CurrentTime.second() < 10)                                        // Are the seconds are < 10?
            { SD_LGR.print('0'); }                                              // Print leading '0' for seconds.
          SD_LGR.print(String(CurrentTime.second())+",");                       // Else, print seconds.
          SD_LGR.print(HR_Value,0);
          SD_LGR.print(",");
          SD_LGR.print(PULSE_CNT,0);
          SD_LGR.print(",");        
          if(WHR)
          { SD_LGR.print("WHR"); }
          else if(!WHR)
          { 
            if(CHR)
            {   SD_LGR.print("CHR");   }
            else if(!CHR)
            {   SD_LGR.print("-");   }
          }        
          SD_LGR.println();
          PrevSecond=CurrentTime.second();                                      // Update the Previou-Second.
        }
      }
#endif      
    }
  }
      delay(LED_BLNK_TME);
      SET_LED(OFF,OFF,OFF,OFF);
      ClearAcculatedCounts();
    delay(50);                                                          
  } while(1);
}
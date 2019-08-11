#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <ShiftRegister74HC595.h>
///////////////////////////////////Change this Pin Number here////////////
#define input1 49
#define input2 45
#define input3 53
#define input4 47
#define input5 51
//////////////////////////////////////////////////////////////////////////////////
DateTime now;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
////////////////////////////////////Set the pin number for Mega which ar connected to the Shift Registers//////////
ShiftRegister74HC595 days (4,4,2,3);//Set the Pins
ShiftRegister74HC595 dday (2,43,39,41);//Set the Pins
ShiftRegister74HC595 months (2,16,37,14);//Set the Pins
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void showDate(void);
void showTime(void);
void showDay(void); 
int value=0;
void setup ()
{
  pinMode(input1,INPUT);
  pinMode(input2,INPUT);
  pinMode(input3,INPUT);
  pinMode(input4,INPUT);
  pinMode(input5,INPUT);
  int _month=now.month();
  int _day=now.day();
  int _dday=now.dayOfTheWeek();
  Serial.begin(9600);
  lcd.begin(16,2);
  //delay(2000);
  days.setAllLow();
  
 if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC Module");
    while (1);
  }
/////////////////////////////////////////////////Uncomment the Lines When uploading for first time//////////////////////////
/* if (rtc.lostPower()) 
  {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));*/
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop () 
{      
        now = rtc.now();
        int i1=digitalRead(input1);
        int i2=digitalRead(input2);
        int i3=digitalRead(input3);
        int i4=digitalRead(input4);
        int i5=digitalRead(input5);
         delay(100);
        
         if(i1==HIGH)                         //Pressing the Set Button with a another button of + or - to change paramenters trigger this branch.

         {    
            
              lcd.setCursor(0,0);
              lcd.print("--SET-MODE----");
              lcd.setCursor(0,1); 
               lcd.print("DATE:");
              lcd.setCursor(5,1);
              lcd.print(now.day());
                lcd.print('/');
                lcd.print(now.month());
                lcd.print('/');
                lcd.print(now.year());
            
                    
                
              
              
           if(i1==HIGH&&i2==HIGH)
          {     
               lcd.clear();
               value=now.month()+1;
               rtc.adjust(DateTime(now.year(),value,now.day(),now.hour(),now.minute(),now.second()));
                show();
          }
           else if(i1==HIGH&&i3==HIGH)
          { lcd.clear();
           value=now.day()+1;
             rtc.adjust(DateTime(now.year(),now.month(),value,now.hour(),now.minute(),now.second()));
             show();
          }
           else if(i1==HIGH&&i4==HIGH)
          { lcd.clear();
            value=now.day()-1;
            rtc.adjust(DateTime(now.year(),now.month(),value,now.hour(),now.minute(),now.second()));
           show();
          }
           else if(i1==HIGH&&i5==HIGH)
          { lcd.clear();
             value=now.month()-1;            
             rtc.adjust(DateTime(now.year(),value,now.day(),now.hour(),now.minute(),now.second()));
               show();
          }
          
             }
              
        else
          {  delay(1000);
             lcd.clear();
         
             show();
          }
  
}


   void show()                                    //This Functions shows all the Parameters on the calendar in lcd as well as LEDs.
   {
              showDate();                          //Show date in LCD
              showDay();                           //Show day in LCD
              showTime();                          //Show Time in LCD
              int d=now.day()-1;                    //STORE the date as (-1)decrement is used as shift register o/p starts from number 0 not 1.
              int m=now.month()-1;
              int ddow=now.dayOfTheWeek();
              Serial.println(ddow);
              days.setAllLow();
              months.setAllLow();
              dday.setAllLow();
              if(ddow==0)
              dday.set(7,HIGH);                   
              else
              dday.set(ddow,HIGH);
              days.set(d,HIGH);
              months.set(m,HIGH);
    
   }

 void showDate()                                        //This Functions print the Date on The LCD Montior.
 {
  lcd.setCursor(0,0);
  lcd.print(now.day());
  lcd.print('/');
  lcd.print(now.month());
  lcd.print('/');
  lcd.print(now.year());
  
 }
 void showDay()
 {
  lcd.setCursor(11,0);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);           //This Functions print the Day of the Week on The LCD Montior.
 }
 void showTime()                                          //This Functions print the Time on The LCD Montior.
 {
  lcd.setCursor(0,1);
  lcd.print("Time:");
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second());
  lcd.print("    ");
 } 

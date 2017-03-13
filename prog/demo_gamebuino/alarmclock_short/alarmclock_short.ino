//standart gamebuino stuff
//#define DEMO
#include <SPI.h>
#include <Gamebuino.h>
Gamebuino gb;
#define FPS 20

//I2C and RTC library
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void printtime(const DateTime& dt, uint8_t mode);
void DisplaymainUpdate();
void DisplayalarmUpdate();
void settimeUpdate();
void setalarmUpdate();
void setkeys(DateTime& dt);
void screensaver();

DateTime now(17,3,13,5,59,55);
DateTime alarm(17,3,13,6,0,0);
TimeSpan tag(1,0,0,0);
TimeSpan seconds(1);

//declare all the variables needed to make a menu
#define MENULENGTH 4
const char timeset[] PROGMEM = "Time setting";
const char alarmset[] PROGMEM = "alarm setting";
const char backosition[] PROGMEM = "back";
const char screensavermen[] PROGMEM = "screen off";
//Put all the different items together in a menu (an array of strings actually)
const char* const menu[MENULENGTH] PROGMEM = {
  alarmset,
  screensavermen,
  timeset,
  backosition
};

//some variables to handle events
bool alarmon;
uint8_t settings;
uint8_t setpos;
uint8_t timeout;

void setup(){
   gb.begin();
   gb.titleScreen(F("Alarm Clock"));
   gb.battery.show = true;
   gb.setFrameRate(FPS);
   #ifndef DEMO
   rtc.begin();
   #endif
   alarmon = false;
   settings = MENULENGTH;
   setpos = 0;
   timeout = 0;
}

void loop(){
   if(gb.update()){
      if((gb.frameCount%20) == 0){
         if(settings != 0 && settings != 2){
            #ifndef DEMO
            now = rtc.now();
            #else
            now = now + seconds;
            #endif
         }
         if(   now.day()==alarm.day() && 
               now.hour() == alarm.hour() && 
               now.minute() == alarm.minute() && 
               now.second() == alarm.second()){
            if(timeout >= 121){
               settings = MENULENGTH;
               gb.backlight.automatic = true;
               #ifdef DEMO
               gb.popup(F("saver"),1*FPS);
               #endif
            }
            timeout = 0;
            gb.popup(F("Time up"),5*FPS);
            alarmon = true;
         }
         if(timeout < 120){
            timeout ++;
         }
         else if(timeout == 120){
            timeout ++;
            gb.backlight.automatic = false;
            gb.backlight.set(0);
            screensaver();
            settings = 1;
         }
      }
      if(gb.buttons.pressed(BTN_C)){
         gb.backlight.automatic = true;
         settings = MENULENGTH;
         timeout = 0;
         gb.titleScreen(F("Alarm Clock"));
         gb.battery.show = true;
      }
      if(alarmon == false && (settings==MENULENGTH || settings==1) && gb.buttons.pressed(BTN_A)){
         if(timeout >= 121){
            gb.backlight.automatic = true;
            settings = MENULENGTH;
            #ifdef DEMO
            gb.popup(F("saver"),1*FPS);
            #endif
         }
         timeout = 0;
         settings = gb.menu(menu,MENULENGTH);
      }
      if(alarmon){
         DisplayalarmUpdate();
         #ifndef DEMO
         gb.sound.playOK();
         #endif
         if(gb.buttons.held(BTN_A,FPS*2)){
            if(timeout == 121){
               gb.backlight.automatic = true;
               settings = MENULENGTH;
               #ifdef DEMO
               gb.popup(F("saver"),1*FPS);
               #endif
            }
            timeout = 0;
            alarmon = false;
            alarm = alarm + tag;
            #ifndef DEMO
            gb.sound.playCancel();
            #endif
         }
      }
      else{
         switch(settings){
         case 0:
            setalarmUpdate();
            setkeys(alarm);
            break;
         case 1:
            screensaver();
            if(timeout <=120){
               timeout = 120;
            }
            break;
         case 2: 
            settimeUpdate();
            setkeys(now);
            break;
         case 3:
            settings = MENULENGTH;
            break;
         default:
            DisplaymainUpdate();
            break;
         }
      }
   } 
}


void printtime(const DateTime& dt, uint8_t mode){
  if(mode == 0 || mode == 2){
    if(dt.day()<10){gb.display.print(F("0"));}
    gb.display.print(dt.day(),DEC);
    gb.display.print(F("."));
    if(dt.month()<10){gb.display.print(F("0"));}
    gb.display.print(dt.month(),DEC);
    gb.display.print(F("."));
    if(dt.year()<10){gb.display.print(F("0"));}
    gb.display.print(dt.year()-2000,DEC);
    gb.display.print(F(" "));
  }
  if(mode == 0 || mode == 1)
  {
    if(dt.hour()<10){gb.display.print(F("0"));}
    gb.display.print(dt.hour(),DEC);
    gb.display.print(F(":"));
    if(dt.minute()<10){gb.display.print(F("0"));}
    gb.display.print(dt.minute(),DEC);
    gb.display.print(F(":"));
    if(dt.second()<10){gb.display.print(F("0"));}
    gb.display.print(dt.second(),DEC);
  }
}

void DisplaymainUpdate(){
  gb.display.clear();
  gb.display.println(F("Alarm Clock"));
  gb.display.println(F("-----------"));
  gb.display.println(F("Now: "));
  printtime(now,0);
  gb.display.print(F("\n"));
  gb.display.println(F("Alarmtime: "));
  printtime(alarm,0);
  gb.display.print(F("\n"));
  gb.display.print(F("\n"));
  gb.display.print(F("BAT: "));
  gb.display.print(gb.battery.voltage);
}

void DisplayalarmUpdate(){
  gb.display.clear();
  gb.display.println(F("Alarm on"));
  gb.display.println(F("---------"));
  gb.display.println(F("Now: "));
  printtime(now,0);
  gb.display.print(F("\n"));
  gb.display.print(F("\n"));
  gb.display.print(F("\n"));
  gb.display.print(F("\n"));
  gb.display.print(F("BAT: "));
  gb.display.print(gb.battery.voltage);
}

void settimeUpdate(){
   gb.display.clear();
   gb.display.println(F("Time setting"));
   gb.display.println(F("------------"));
   gb.display.println(F("Time: "));
   printtime(now,0);
   gb.display.print(F("\n"));
   switch(setpos){
   case 5:
      gb.display.println(F("      ^^         "));
      break;
   case 4:
      gb.display.println(F("   ^^            "));
      break;
   case 3:
      gb.display.println(F("^^               "));
      break;
   case 2:
      gb.display.println(F("         ^^      "));
      break;
   case 1:
      gb.display.println(F("            ^^   "));
      break;
   case 0:
      gb.display.println(F("               ^^"));
      break;
   }      
}

void setalarmUpdate(){
   gb.display.clear();
   gb.display.println(F("Alarm setting"));
   gb.display.println(F("------------"));
   gb.display.println(F("Alarm: "));
   printtime(alarm,0);
   gb.display.print(F("\n"));
   switch(setpos){
   case 5:
      gb.display.println(F("      ^^         "));
      break;
   case 4:
      gb.display.println(F("   ^^            "));
      break;
   case 3:
      gb.display.println(F("^^               "));
      break;
   case 2:
      gb.display.println(F("         ^^      "));
      break;
   case 1:
      gb.display.println(F("            ^^   "));
      break;
   case 0:
      gb.display.println(F("               ^^"));
      break;
   }      
}

void screensaver(){
  gb.display.clear();
}

void setkeys(DateTime& dt){
   if(gb.buttons.pressed(BTN_A)){
      setpos++;
      if(setpos >=6){
         if(settings==1){
            #ifndef DEMO
            rtc.adjust(now);
            #endif
         }
         settings = MENULENGTH;
         setpos = 0;
      }
      timeout = 0;
   }
   if(gb.buttons.pressed(BTN_UP)){
      timeout = 0;
      switch(setpos){
      case 5:
         dt = dt + TimeSpan(365,0,0,0);
         break;
      case 4:
         if(dt.month()==1 || dt.month()==3 || dt.month()==5 || dt.month()==7 || dt.month()==8 || dt.month()==10 || dt.month()==12){
            dt = dt + TimeSpan(31,0,0,0);
         }
         else if(dt.month()==4 || dt.month()==6 || dt.month()==9 || dt.month()==11){
            dt = dt + TimeSpan(30,0,0,0);
         }
         else{
            dt = dt + TimeSpan(28,0,0,0);
         }
         break;
      case 3:
         dt = dt + TimeSpan(1,0,0,0);
         break;
      case 2:
         dt = dt + TimeSpan(0,1,0,0);
         break;
      case 1:
         dt = dt + TimeSpan(0,0,1,0);
         break;
      case 0:
         dt = dt + TimeSpan(0,0,0,1);
         break;
      }      
   }
   if(gb.buttons.pressed(BTN_DOWN)){
      timeout = 0;
      switch(setpos){
      case 5:
         dt = dt - TimeSpan(365,0,0,0);
         break;
      case 4:
         if(dt.month()==1 || dt.month()==3 || dt.month()==5 || dt.month()==7 || dt.month()==8 || dt.month()==10 || dt.month()==12){
            dt = dt - TimeSpan(31,0,0,0);
         }
         else if(dt.month()==4 || dt.month()==6 || dt.month()==9 || dt.month()==11){
            dt = dt - TimeSpan(30,0,0,0);
         }
         else{
            dt = dt - TimeSpan(28,0,0,0);
         }
         break;
      case 3:
         dt = dt - TimeSpan(1,0,0,0);
         break;
      case 2:
         dt = dt - TimeSpan(0,1,0,0);
         break;
      case 1:
         dt = dt - TimeSpan(0,0,1,0);
         break;
      case 0:
         dt = dt - TimeSpan(0,0,0,1);
         break;
      }      
   }
}

#include "IRremote.hpp"
#include <LiquidCrystal.h>
#include <time.h>
#define IR_RECEIVE_PIN 9
int onoff=1;
int vol=0;

const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  lcd.begin(16, 2); 
  time_t(100);
}

void loop() {
  
  if (IrReceiver.decode()) {
    uint16_t command = IrReceiver.decodedIRData.command;
    //Serial.println(command);
    switch (command) { 
      case 18: 
        if(onoff==1){
          Serial.println("ON");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ON");
          time_t(100);
          onoff=0;
        }
        else{
          Serial.println("OFF");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("OFF");
          time_t(100);
          onoff=1;
        }
        break;
      case 10:
        Serial.println("SPEED 1");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SPEED 1");
        time_t(100);
        break;
      case 27: 
        Serial.println("SPEED 2"); 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SPEED 2");
        time_t(100);
        break;
      case 31:
        Serial.println("SPEED 3");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SPEED 3");
        time_t(100);
        break;	
      case 12: 
        Serial.println("SPEED 4");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SPEED 4"); 
        time_t(100);
        break;
      case 13: 
        Serial.println("SPEED 5"); 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SPEED 5");
        time_t(100);
        break;
      case 6:
        if(vol<5){
          Serial.println("VOL+");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED: ");
          lcd.setCursor(0,7);
          lcd.print(vol);
          time_t(100);
          vol=vol+1;
         //Serial.println(vol);
        }
        else
        {
         Serial.println("FULL SPEED");
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("FULL SPEED");
         time_t(100);
        }
        break;		
      case 5:
        if(vol>0){
          Serial.println("VOL-");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED: ");
          lcd.setCursor(0,7);
          lcd.print(vol);
          time_t(100);
          vol=vol-1;
          //Serial.println(vol);
        }
       else
       {
         Serial.println("FAN STOPED");
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("FAN STOPPED");
         time_t(100);
        }
      break;
      default:	
        Serial.println("UNDEFINED");	  
    } 	   
		
    delay(100);
    IrReceiver.resume();
  }
}

#include "IRremote.hpp"
#include <LiquidCrystal.h>
#include <time.h>
#include <Servo.h>
Servo esc_signal;
#define IR_RECEIVE_PIN 9
int onoff=1;
int vol=1;
int duty=25;
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int lm35_pin = A0;	/* LM35 O/P pin */
  int temp_adc_val;
  float temp_val;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  lcd.begin(16, 2); 
  lcd.setCursor(0, 0);
  lcd.print("OFF");
  time_t(100);
  esc_signal.attach(8);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  delay(3000);            //ESC initialization delay.
}

void loop() {

  
  esc_signal.write(duty);	  //Vary this between 40-130 to change the speed of motor. Higher value, higher speed.
  delay(15);

  temp_adc_val = analogRead(lm35_pin);	/* Read Temperature */
  temp_val = (temp_adc_val * 4.88);	/* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10);	/* LM35 gives output of 10mv/°C */
  //Serial.print("Temperature = ");
  //Serial.print(temp_val);
 //Serial.print(" Degree Celsius\n");
  //delay(100);
  lcd.setCursor(0, 1);
  lcd.print("Temp = ");
  lcd.setCursor(7,1);
  lcd.print(temp_val);
  lcd.setCursor(13,1);
  lcd.print((char)223);
  lcd.print("C");
  delay(100);
  if (IrReceiver.decode()) {
    uint16_t command = IrReceiver.decodedIRData.command;
    //Serial.println(command);
    switch (command) { 
      case 18: 
        if(onoff==1){
          //Serial.println("ON");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ON");
          time_t(100);
          onoff=0;
          duty=25;
          //vol=0;
          Serial.println(vol);
        }
        else{
          //Serial.println("OFF");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("OFF");
          time_t(100);
          onoff=1;
          duty=25;
          //vol=0
          //Serial.println(vol);
        }
        break;
      case 10:
        if(onoff==0){
          //Serial.println("SPEED 1");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED 1");
          duty=40;
          vol=1;
          //Serial.println(vol);
          time_t(100);
        }
        break;
      case 27: 
        if(onoff==0){
          //Serial.println("SPEED 2"); 
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED 2");
          duty=55;
          vol=2;
          //Serial.println(vol);
          time_t(100);
        }
        break;
      case 31:
        if(onoff==0){
          //Serial.println("SPEED 3");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED 3");
          duty=70;
          vol=3;
          //Serial.println(vol);
          time_t(100);
        }
        break;	
      case 12: 
        if(onoff==0){
          //Serial.println("SPEED 4");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED 4"); 
          duty=85;
          vol=4;
          //Serial.println(vol);
          time_t(100);
        }
        break;
      case 13: 
        if(onoff==0){
        //Serial.println("SPEED 5"); 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SPEED 5");
        duty=100;
        vol=5;
        //Serial.println(vol);
        time_t(100);
      }
        break;
      case 6:
        if(vol<=5 && duty<100 && onoff==0){
          //Serial.println("VOL+");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED");
          lcd.setCursor(7,0);
          lcd.print(vol);
          time_t(100);
          vol=vol+1;
          duty=duty+15;
         //Serial.println(vol);
        }
        else
        {
         //Serial.println("FULL SPEED");
         lcd.clear();s
         lcd.setCursor(0, 0);
         lcd.print("FULL SPEED");
         time_t(100);
        }
        break;		
      case 5:
        if(vol>=1 && duty>0 && onoff==0){
          //Serial.println("VOL-");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("SPEED");
          lcd.setCursor(7,0);
          lcd.print(vol);
          time_t(100);
          vol=vol-1;
          duty=duty-15;
          //Serial.println(vol);
        }
        else
        {
           //Serial.println("FAN STOPED");
           lcd.clear();
           lcd.setCursor(0, 0);
           lcd.print("FAN OFF");
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

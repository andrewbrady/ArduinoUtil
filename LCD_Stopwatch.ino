/*
** Example Arduino sketch for SainSmart I2C LCD Screen 16x2
** based on https://bitbucket.org/celem/sainsmart-i2c-lcd/src/3adf8e0d2443/sainlcdtest.ino
** by
** Edward Comer
** LICENSE: GNU General Public License, version 3 (GPL-3.0)

** This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
** https://bitbucket.org/fmalpartida/new-liquidcrystal 

** Modified - Ian Brennan ianbren at hotmail.com 23-10-2012 to support Tutorial posted to Arduino.cc

** Written for and tested with Arduino 1.0
**
** NOTE: Tested on Arduino Uno whose I2C pins are A4==SDA, A5==SCL

*/
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

int n = 0;
int m = 0;
int h = 0;


const int buttonMin  = 2;
const int buttonHour = 3;

int buttonMinState  = 0;
int buttonHourState = 0;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {

  pinMode(buttonMin,  INPUT);
  pinMode(buttonHour, INPUT);
  
  lcd.begin (16,2); //  <<----- My LCD was 16x2
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home (); // go home
  lcd.print("KD0PBZ-Ctl");
}

void loop(){

 buttonMinState  = digitalRead(buttonMin);
 buttonHourState = digitalRead(buttonHour);

 if(buttonMinState == HIGH){
  m++;
  buttonMinState = 0;
  //goto top;
 }

 if(buttonHourState == HIGH){
  h++;
  buttonHourState = 0;
  //goto top;
 }

 lcd.setCursor (0,1);        // go to start of 2nd line
 
 if(h < 10){
  lcd.print(0,DEC);
 }
 lcd.print(h,DEC);
 
 lcd.print(":");
  
 if(m < 10){
  lcd.print(0,DEC);
 }
 lcd.print(m,DEC);

 lcd.print(":");

 
 if(n < 9){
 lcd.print(0,DEC); 
 }
 lcd.print(n,DEC);
 

  //Counting Mins
  if(n >= 60){
    m++;
    n = 0;
  }

  //Counting Hours
  if(m >= 59){
    h++;
    m = 0;
  }

  // Wait 1 Second this is the resloution of our clock
  n++;
  delay(1000);

}



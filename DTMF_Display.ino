/*
1. SPI Interface Inatruction
      clockPin --> SCK(EN)
      latchPin --> CS(RS)
      dataPin --> SID(RW)
 2. Connection:
    1)Turn the BL_ON Switch to the "ON" side;
    2)Turn the PBS_ON Switch to the "SPI" side

Method1:
      LCD                   Arduino
      EN                 Digital Pin 2
      RS                 Digital Pin 7
      RW                 Digital Pin 10
      VCC                     5V
      GND                     GND;

Method2:
      LCD                          Arduino
      SCK       clockPin(defined in the "initDriverPin" function)
      CS        latchPin(defined in the "initDriverPin" function)
      SID       dataPin (defined in the "initDriverPin" function)
      VCC                            5V
      GND                           GND
      
This sample shows how to use LCD12864 to display integer on the screen, and it uses function itoa() from library stdlib.h
*/

#include "LCD12864RSPI.h"
#include "DFrobot_bmp.h"
#include "DFrobot_char.h"
#include "stdlib.h"
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )


//Global variables-----------------------------------------------------------------------------------------
byte DTMFread;            // The DTMFread variable will be used to interpret the output of the DTMF module.
 const int STQ = 49;        // Attach DTMF Module STQ Pin to Arduino Digital Pin 3
 const int Q4  = 50;        // Attach DTMF Module Q4  Pin to Arduino Digital Pin 4
 const int Q3  = 51;        // Attach DTMF Module Q3  Pin to Arduino Digital Pin 5
 const int Q2  = 52;        // Attach DTMF Module Q2  Pin to Arduino Digital Pin 6
 const int Q1  = 53;        // Attach DTMF Module Q1  Pin to Arduino Digital Pin 7


int i=0;  //counter, initial value is 0

unsigned char wangzhi[]=" www.DFRobot.cn ";

unsigned char en_char1[]="Ok.";

unsigned char en_char2[]="Test, Copyright ";

unsigned char en_char3[]="by DFRobot ---> ";

char DTMF_Output[] = "                ";
const char DTMF_OUTPUT_CLEAR[] = "                ";
int key_stack = 0;


void setup()
{
  LCDA.initDriverPin(2,7,10); //INIT SPI Interface
  LCDA.Initialise(); // INIT SCREEN
  delay(100);
  //LCDA.DrawFullScreen(logo);//LOGO
  randomSeed(0);
  LCDA.CLEAR();
  delay(100);
  LCDA.DisplayString(0,0,en_char1,16);
  delay(1000);

  //Setup the INPUT pins on the Arduino
  pinMode(STQ, INPUT);
  pinMode(Q4, INPUT);
  pinMode(Q3, INPUT);
  pinMode(Q2, INPUT);
  pinMode(Q1, INPUT);
    Serial.begin(9600);
    Serial.println("DTMF Reader");
  LCDA.CLEAR();//clear the screen
  delay(100);  
}

void loop()
{
/*
int number= i; // the interger should be in the range from -32768 ~ 32767
char buf [16];
itoa(number,buf,10); //transform integer into string
unsigned char temp[16];

for (int i=0;i<=15;i++)
{
  if(buf[i]!='0'&&buf[i]!='1'&&buf[i]!='2'&&buf[i]!='3'&&buf[i]!='4'&&buf[i]!='5'&&buf[i]!='6'&&buf[i]!='7'&&buf[i]!='8'&&buf[i]!='9'&&buf[i]!='-')
  {temp[i]=' ';}   // put space into those where no  values are assigned initially
  else
  {temp[i]=buf[i];}
}
//LCDA.DisplayString(0,0,temp,16);//display the counter on the screen
*/

  if(digitalRead(STQ)==HIGH){       //When a DTMF tone is detected, STQ will read HIGH for the duration of the tone.
    DTMFread=0;
    if(digitalRead(Q1)==HIGH){      //If Q1 reads HIGH, then add 1 to the DTMFread variable
      DTMFread=DTMFread+1;
    }
    if(digitalRead(Q2)==HIGH){      //If Q2 reads HIGH, then add 2 to the DTMFread variable
      DTMFread=DTMFread+2;
    }
    if(digitalRead(Q3)==HIGH){      //If Q3 reads HIGH, then add 4 to the DTMFread variable
      DTMFread=DTMFread+4;
    }
    if(digitalRead(Q4)==HIGH){      //If Q4 reads HIGH, then add 8 to the DTMFread variable
      DTMFread=DTMFread+8;
    }
      Serial.println(DTMF_Decode(DTMFread));      
      DTMF_Output[key_stack] = DTMF_Decode(DTMFread);
      LCDA.DisplayString(0,0,DTMF_Output,16);
      key_stack++;
      if(key_stack == 16){
         key_stack = 0;
         
      }
        while (digitalRead(STQ)==HIGH){};
  }
  
  //LCDA.DisplayString(0,0,DTMF_Output,16);
  //delay(500);
  //i++; // counter works every 1 second
}


char DTMF_Decode(byte r) {
  char c = '?';
  if(r ==  1){c = '1';}
  if(r ==  2){c = '2';}
  if(r ==  3){c = '3';}
  if(r ==  4){c = '4';}
  if(r ==  5){c = '5';}
  if(r ==  6){c = '6';}
  if(r ==  7){c = '7';}
  if(r ==  8){c = '8';}
  if(r ==  9){c = '9';}
  if(r ==  10){c = '0';}
  if(r ==  11){c = '*';}
  if(r ==  12){c = '#';}
  if(r ==  13){c = 'A';}
  if(r ==  14){c = 'B';}
  if(r ==  15){c = 'C';}
  if(r ==  0){c = 'D';}
  return c;
}

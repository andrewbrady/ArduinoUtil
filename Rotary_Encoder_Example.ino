/* Rotary encoder read example */
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC

void setup(){
  /*Setup Encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A,HIGH);

  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);

  Serial.begin(115200);
  Serial.println("Encoder Example Start");

  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
}

void loop(){
  static uint8_t counter = 0; //this variable will be changed by encoder input
  int8_t tmpdata;
  /**/
  tmpdata = read_encoder();
  if (tmpdata) {
      Serial.print("Counter Value: ");
      Serial.println(tmpdata, DEC);
      //counter += tmpdata;  
  }
  if(digitalRead(2) == LOW){
    Serial.println("PRESSED");
  }
}

/* returns change in coder state (-1,0,1) */
int8_t read_encoder() {
   static int8_t enc_states[] = {0,-1,1,0,0,-1,-1,0,0,1,0,1,-1,0};
   static uint8_t old_AB = 0;
   /**/
   old_AB <<= 2; //remember previous state
   old_AB |= ( ENC_PORT & 0x03 ); //add current state
   return ( enc_states[( old_AB & 0x0f )]);
}


#include "cubeLeds.h"



void setData(byte data){
  digitalWrite(DATA7, data&0x80); //Disable decoder
  digitalWrite(DATA6, data&0x40);
  digitalWrite(DATA5, data&0x20);
  digitalWrite(DATA4, data&0x10);
  digitalWrite(DATA3, data&0x08);
  digitalWrite(DATA2, data&0x04);
  digitalWrite(DATA1, data&0x02);
  digitalWrite(DATA0, data&0x01);
}


void selectAndLatch(byte num){
  digitalWrite(EN_DECOD, LOW);//Latches data
  PORTC=num&B00000111;
  digitalWrite(EN_DECOD, HIGH);//Enable decoder
  //digitalWrite(EN_DECOD, HIGH);//Enable decoder
  digitalWrite(EN_DECOD, LOW);//Latches data

}

void latchLayerData(){
  digitalWrite(SEL_AN, HIGH); //Data goes through
       delay(1);

  digitalWrite(SEL_AN, LOW);  //Data gets latched
}

void setup() {
  pinMode(DATA0,OUTPUT);
  pinMode(DATA1,OUTPUT);
  pinMode(DATA2,OUTPUT);
  pinMode(DATA3,OUTPUT);
  pinMode(DATA4,OUTPUT);
  pinMode(DATA5,OUTPUT);
  pinMode(DATA6,OUTPUT);
  pinMode(DATA7,OUTPUT);

  pinMode(ADDR0,OUTPUT);
  pinMode(ADDR1,OUTPUT);
  pinMode(ADDR2,OUTPUT);

  pinMode(SEL_AN,OUTPUT);
  pinMode(EN_DECOD,OUTPUT);
  pinMode(EN_LAT,OUTPUT);

    
  digitalWrite(EN_DECOD, LOW); //Disable decoder
  digitalWrite(EN_LAT, LOW);   //Latches output enabled always
  digitalWrite(SEL_AN, LOW);   //Only for layer select, start at null
  
}

void loop() {
  byte i=0;

  //Clear all
  setData(0xFF);
  for (i=0; i<4; i++){
   delay(1);
   selectAndLatch(i);
   delay(1);
   }

  //Select led 13 (5th of 2nd chip) 
  setData(0B11101111); 
     delay(1);

   selectAndLatch(1);

  //Set layer 1
  setData(0B11100000); 
     delay(1);

  latchLayerData();
   
   /*
  for (i=0; i<4; i++){
   delay(1);
   selectAndLatch(i);
  }
     */
     while(1){};
  /*
  while(1){
    selectLatch(i);
    i=(i+1)%4;
    delay(200);
    }
  */

/*
  for (i=0; i<4; i++){
   setData(0x1<<i);
   delay(1);
   selectAndLatch(i);
  }
 */
}

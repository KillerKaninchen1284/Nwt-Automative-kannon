//#include <motor.ino>
#include <bits/stdc++.h>
#include<iostream>
#include<ESP32Servo.h>

#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
  //dec of the queue
//#include <iostream>
#define laenge 30
#include <Stepper.h>
//Motor Ultraschaall
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
//Motor Updown
Servo myservo;
#define IN5 15
#define IN6 2
#define IN7 0
#define IN8 4
//Motor base
#define IN9 32
#define IN10 33
#define IN11 25
#define IN12 26

// the original
/*
Stepper myStepperbase(2048, IN1, IN3, IN2, IN4);
Stepper myStepperupd(2048, IN5, IN6, IN7, IN8);
Stepper myStepperUlti(2048,IN9,IN10,IN11,IN12);*/

Stepper myStepperUlti(2048, IN1, IN3, IN2, IN4);
Stepper myStepperupd(2048, IN5, IN6, IN7, IN8);
Stepper myStepperbase(2048,IN9,IN10,IN11,IN12);
//Ultraschall setup
long dauer=0;
long entfernung=0;
bool amprot=false;
bool ampelGrun=true;
//########################Config###################################
int stepsPerRevolution = 2048;  
int anzahl_steps = 2048;
int stepsperdeg = 10;
int Sichtfeld = 360;
int trigger=27;
int echo=14;
int ecm = 1;
int ecmd =3;
int ubersetzverh= 30;
TaskHandle_t Task1;
TaskHandle_t Task2;
//#################################################################
  //Motor setup
  int now_pos=0; //far left;in grad  
 
  

  long myX[360]= {0};
  long myY[360]={0};
  long myDis[360];
  long myXa[360]= {0};
  long myYa[360]={0};
  long myDisa[360];
  int angle =0;
  bool myErr[360]; 
 //todo eins und 360 grad können nicht funktionieren
void setup() {
  Serial.begin(115200);
  myservo.attach(4);
  randomSeed(analogRead(5));
 pinMode(trigger,OUTPUT);
pinMode(echo,INPUT);

  xTaskCreatePinnedToCore(
                    Task1code,  
                    "Task1",     
                    10000,      
                    NULL,      
                    1,          
                    &Task1,   
                    1);                 
  delay(500); 

 
  xTaskCreatePinnedToCore(
                    Task2code, 
                    "Task2",   
                    100000,    
                    NULL,      
                    1,           
                    &Task2,    
                    0);        
    delay(500); 

}



double readsens(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  //dauer =pulseIn(echo,HIGH);
  dauer = random(0,100);
  vTaskDelay(30);
  return dauer;

  /*
  double b =analogRead(echo);
  return b;
  */
  
}

void genalt(){
for(int i;i<=Sichtfeld;i++){
  myXa[i]= myX[i];
  myYa[i]=myY[i];
  myDisa[i]= myDis[i];
}}


int compan(){
  int count;int counterr;counterr=0;
for(int i;i<Sichtfeld;i++){
if(myDisa[i]== myDis[i] ){
  count++;
        
}
else if((myDis[i]-myDisa[i])>=-(myDis[i]/10) && (myDis[i]-myDisa[i])<=(myDis[i]/10)){count++;}
else{
     Serial.print("erroro at i:");
     Serial.println(i);
     myErr[i]= true;
     counterr++;
     }
if(myErr[i]== true){
  vTaskDelay(10);
    Serial.print(i);Serial.println("seen error");
  myStepperUlti.setSpeed(8);
  myStepperUlti.step(i*stepsperdeg*ubersetzverh);
    Serial.println("activated servo");
    delay(1000);
    myservo.write(-360);
    delay(1000);
    myservo.write(360);
    myStepperUlti.step(-(i*stepsperdeg*ubersetzverh));
    Serial.println("'ve Gone to Err");
    delay(100); // for safety may cause crahses
    myErr[i]=false;
  }//}
}

return counterr;
counterr=0;
}

void Scansfeld(){
  for(int i;i<= Sichtfeld;i++){
    myDis[i] = Ecm(i,0);
    movmot(3,stepsperdeg);
    now_pos++;
   
  }
 
  movmot(3,0-(Sichtfeld*stepsperdeg+stepsperdeg));
 
  now_pos =0;
  for(int i;i<= Sichtfeld;i++){
    myDisa[i] = Ecm(i,3);
    movmot(3,stepsperdeg);
  }
  movmot(3,-(Sichtfeld*stepsperdeg+stepsperdeg));
  now_pos =0;

}


void Task1code( void * pvParameters ){
  for(;;){
  Scansfeld();
  }
}
void Task2code( void * pvParameters ){

  Stepper myStepperUlti(2048, IN9, IN10, IN11, IN12);

  for(;;){
    compan();
   
   } }
  


void loop() {
  Serial.println(xPortGetCoreID());
  vTaskDelay(portMAX_DELAY);
  vTaskDelete(NULL);


}

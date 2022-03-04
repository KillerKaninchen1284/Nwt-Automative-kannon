//#include <motor.ino>
#include <bits/stdc++.h>
#include<iostream>
  //dec of the queue
//#include <iostream>
#define laenge 30
#include <Stepper.h>

#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
//Motor Updown

#define IN5 15
#define IN6 2
#define IN7 0
#define IN8 4
//Motor Ulti
#define IN9 33
#define IN10 32
#define IN11 25
#define IN12 26
Stepper myStepperbase(2048, IN1, IN3, IN2, IN4);
Stepper myStepperupd(2048, IN5, IN6, IN7, IN8);
Stepper myStepperUlti(2048, IN9, IN10, IN11, IN12);
//Ultraschall setup
long dauer=0;
long entfernung=0;
//########################Config###################################
int stepsPerRevolution = 2048;  
int anzahl_steps = 2048;
int stepsperdeg =6;
int Sichtfeld = 40;
int trigger=27;
int echo=14;
int ecm = 1;
int ecmd =3;
//#################################################################
  //Motor setup
  int now_pos=0; //far left;in grad  
 
  

  long myX[360]= {0};
  long myY[360]={0};
  float myDis[360];
  long myXa[360]= {0};
  long myYa[360]={0};
  float myDisa[360];
  int angle =0;
  bool myErr[360]; 
 //todo eins und 360 grad können nicht funktionieren
void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(5));
 pinMode(trigger,OUTPUT);
pinMode(echo,INPUT);
}


void SR(){
  Serial.print("############################################################################");
  Serial.print("in of reading");
  Serial.println();
  Serial.println();
  Serial.println();
  while(Serial.available()){
  String command = Serial.readStringUntil('\n');
  Serial.println(command);
  delay(1000);

}
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("out of reading");
  Serial.print("############################################################################");
 
}
void nImpUpdate(){
  //Search OP queue for high Priority


}


float readsens(){
  digitalWrite(trigger,LOW);
  delay(5);
  digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(trigger,LOW);
  dauer=pulseIn(echo,HIGH);
  //Serial.print("ulti");
  //Serial.print((dauer/2)/29.1);
  //Serial.println("");
  return (dauer/2)/29.1;
}

void declarearray(){
for(int i=-1;i<=Sichtfeld;i++){
  myX[i]=random(1,100);
  myY[i]=random(1,100);
}}

void prntcoor(){
for(int i=-1;i<=Sichtfeld+1;i++){   
  Serial.print("(");Serial.print(myDis[i]);Serial.print(",");Serial.print(myDisa[i]);Serial.print(")");Serial.print(i);

}}

void genalt(){
for(int i;i<=360;i++){
  myXa[i]= myX[i];
  myYa[i]=myY[i];
  myDisa[i]= myDis[i];
}}

int compan(){
  int count;
  int counterr;
  counterr=0;
for(int i;i<360;i++){/*
if(myXa[i]== myX[i]){
if(myYa[i]==myY[i]){  */
if(myDisa[i]== myDis[i] ){
  count++;
        
}
else if((myDis[i]-myDisa[i])>=-(myDis[i]/10) && (myDis[i]-myDisa[i])<=(myDis[i]/10)){count++;}
else{Serial.print("failed Dis= ");Serial.println(myDis[i]);
     Serial.print("at Dis expected");Serial.println(myDisa[i]);
     Serial.println(i);
     myErr[i]== true;
     counterr++;
     }/*
}}
else{Serial.print("failed my Y= ");Serial.println(myY[i]);
     Serial.print("at y expected");Serial.println(myYa[i]);
}}
else{Serial.print("failed my X= ");Serial.println(myX[i]);
     Serial.print("at x expected");Serial.println(myXa[i]);
}}
     Serial.println(count);
if(count == 361){
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("alles gut");
}
else{
  Serial.println("Nope");
  Serial.println("Nope");
  Serial.println("Nope");
  Serial.println("Nope");
  Serial.println("Nope");
}
*/

}
Serial.print("anzahl error :  ");
Serial.println(counterr);
return counterr;
counterr=0;
}
void coordinateur(){
  long x;
  long y;

for(int i;i<=Sichtfeld;i++){
  
  x=cos(i*DEG_TO_RAD)*myDis[i];
  y=sin(i*DEG_TO_RAD)*myDis[i];
  myX[i]=x;
  myY[i]=y;
}}
void Scansfeld(){
  //scan eins
  Serial.println("begin scanning");
  for(int i;i<= Sichtfeld;i++){
    myDis[i] = Ecm(i,1);
    Serial.println(myDis[i]);
    movmot(3,stepsperdeg);
    now_pos++;
    Serial.print(i);
  }
  Serial.println("bigprob");
  movmot(3,0-(Sichtfeld*stepsperdeg+stepsperdeg));
  Serial.println("bigprob");
  now_pos =0;
  for(int i;i<= Sichtfeld;i++){
    myDisa[i] = Ecm(i,3);
    Serial.println("end of ecm 1");
    Serial.println(myDisa[i]);
    movmot(3,stepsperdeg);
    Serial.print(i);
  }
  Serial.println(0);
  movmot(3,-(Sichtfeld*stepsperdeg+stepsperdeg));
  now_pos =0;
  Serial.println("end scanning");
}
void gotoErr(){
for(int i;i<=360;i++){
  if(myErr[i]== true){
    movmot(1,i*stepsperdeg);//got to Error
    //do sth
  }
}

}
void loop() {
  int test =0;
  int an;
  //movmot(1,4096);
  //movmot(1,-4069);
  /*movmot(1,1000);
  movmot(2,-1000);
  movmot(3,2000);
  movmot(3,-2000);
  */
  //SR();
  //oordinateur();
  //declarearray();
  //Serial.println("hi");
  //Serial.println(readsens());
  //delay(10000);
  //prntcoor();
  //genalt();
  //compan();
  //delay(1);
  //genalt();
  //myX[360]=100000;
  //myY[4]=230;
  //myDis[250]=10;
  
  //delay(10000);
  Scansfeld();
  compan();
  /*test = test+compan();
  an++;
  for(int i;i<100;i++){
    Scansfeld();
    test = test+compan();
  an++;
  }*/
  //Serial.print("hfuisfbwuifsduihf");
  //Serial.print(test/an);
  //Serial.println(Ecm(1,1));
  //prntcoor();
  delay(10000);


}

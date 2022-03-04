#include <motor.ino>
#include <bits/stdc++.h>
#include<iostream>
#include<ESP32Servo.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include <iostream>
#define laenge 30
#include <Stepper.h>
//Motor Ultraschaall
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
//Motor Updown

#define IN5 15
#define IN6 2
#define IN7 0
#define IN8 4
//Motor base
#define IN9 33
#define IN10 32
#define IN11 25
#define IN12 26
Servo myservo;
// the original
Stepper myStepperbase(2048, IN1, IN3, IN2, IN4);
Stepper myStepperupd(2048, IN5, IN6, IN7, IN8);
Stepper myStepperUlti(2048,IN9,IN10,IN11,IN12);

//Ultraschall setup

//########################Config###################################
int stepsPerRevolution = 2048;  
int anzahl_steps = 2048;
int stepsperdeg = 10;
int Sichtfeld = 60;
int trigger=27;
int echo=14;
int ecm = 1;
int ecmd =3;
int ubersetzverh= 20;
TaskHandle_t Task1;
TaskHandle_t Task2;
//#################################################################
  //Motor setup
  int now_pos=0; 
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
                    Task1code,   /* name Funktion */
                    "Task1",     /* name  */
                    10000,       /* Stack größe */
                    NULL,        /* parameter */
                    1,           /* priorität */
                    &Task1,      /* egal */
                    1);          /* core*/                  
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

//////////////////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
//#include<ArduinoSTL.h>
//#include<stl_algo.h>
#include<iostream>
float mostFrequent(float arr[], int n)
{
    
    std::sort(arr, arr + n);

    
    float max_count = 1, res = arr[0], curr_count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1])
            curr_count++;
        else {
            if (curr_count > max_count) {
                max_count = curr_count;
                res = arr[i - 1];
            }
            curr_count = 1;
        }
    }

    
    if (curr_count > max_count)
    {
        max_count = curr_count;
        res = arr[n - 1];
    }

    return res;
}
float Ecm(int Grad,int ecm){
  float buffer[ecmd];
  float temp;
  
//Mode0:ein Durchlauf
//Mode1:Jedes mal x Durchläufe
//Mode2:Wenn Ergebnis Großen Unterschied zum vorderen (und Hinteren) hat Nochmal scannen only for myDis not for myDisa
//Mode3:Wenn Disa Unterschied zu Dis mehrmals Durchlaufen, bis öfters das selbe ergebnis kommt only for 2nd run
if(ecm == 0){

  return readsens();
}
else if(ecm ==1){

  for(int i;i<=ecmd;i++){
    buffer[i]= readsens();
   
  }

 // Serial.print("multi run");
return mostFrequent(buffer,sizeof(buffer) / sizeof(buffer[0]));
//return ( (mostFrequent(buffer,sizeof(buffer) / sizeof(buffer[0]))<1000)* mostFrequent(buffer,sizeof(buffer) / sizeof(buffer[0])));
}
else if(ecm ==2){
  
  float temp = readsens();
  //Check auf forderen
   if(((temp-myDis[Grad-1])>=-(myDis[Grad-1]/10) && (temp-myDis[Grad-1])<=(myDis[Grad-1]/10))){
     if(((myDis[Grad-1]-myDis[Grad])>=-(myDis[Grad]/10) && (temp-myDis[Grad])<=(myDis[Grad]/10))){
      return temp;
   }else{Ecm(Grad-1,1);}
   }
   else{Ecm(Grad,1);
   if(((myDis[Grad-1]-myDis[Grad])>=-(myDis[Grad]/10) && (temp-myDis[Grad])<=(myDis[Grad]/10))){
      return temp;
   }else{Ecm(Grad-1,1);}}
    
}
else if(ecm ==3){
  
  float temp = readsens();
  
  if(((temp-myDis[Grad])>=-(myDis[Grad]/10) && (temp-myDis[Grad])<=(myDis[Grad]/10)) ||temp ==myDis[Grad]){return temp;
    
  }
  else if(myDis[Grad]==temp){return temp;}
  else{Ecm(Grad,1);}
}

else{}


//Serial.print("has scanned ");
}
//////////////////////////////////////////////////////////////////////////////////

double readsens(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  
  //dauer = random(0,100);
  vTaskDelay(30);
  return pulseIn(echo,HIGH);

  /*
  double b =analogRead(echo);
  return b;
  */
  
}


void movmot(int Motor, int steps) {
  
 if(Motor == 0 or Motor ==3){
   //ultraschall
   
  
  myStepperbase.setSpeed(5);
  
  myStepperbase.step(steps);
  //delay(10);// Optional
 }
else if(Motor == 2){
  //updown
 
  
  myStepperupd.setSpeed(5);
  
  myStepperupd.step(steps);
  
}
else{

  
  
 // myStepperUlti.setSpeed(5);
  
  //myStepperUlti.step(steps);
 
}//Serial.print("has moved ");
}




void genalt(){
for(int i;i<=Sichtfeld;i++){
  myXa[i]= myX[i];
  myYa[i]=myY[i];
  myDisa[i]= myDis[i];
}}

int compan(){
  int count;
  int counterr;
  counterr=0;
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

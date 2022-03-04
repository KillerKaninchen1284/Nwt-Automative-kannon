int werte [4][4] =
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void myStepperUlti_step(int steps){
if(steps>=0){
while(steps>=0){
for (int i = 0; i < 4; i++)
    {
      digitalWrite(IN1, werte[i][0]);
      digitalWrite(IN2, werte[i][1]);
      digitalWrite(IN3, werte[i][2]);
      digitalWrite(IN4, werte[i][3]);
      delay(10);
    }
  steps--;


}}
else{
while(steps<=0){
for (int i = 4; i >= 0; i--)
    {
      digitalWrite(IN1, werte[i][0]);
      digitalWrite(IN2, werte[i][1]);
      digitalWrite(IN3, werte[i][2]);
      digitalWrite(IN4, werte[i][3]);
      delay(10);
    }
  steps++;


}}
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



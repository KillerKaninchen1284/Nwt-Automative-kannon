

 

void movmot(int Motor, int steps) {
 if(Motor == 0 or Motor ==3){
   //ultraschall
   
  
  myStepperbase.setSpeed(5);
  
  myStepperbase.step(steps);

 }
else if(Motor == 2){
  //updown
 
  
  myStepperupd.setSpeed(5);
  
  myStepperupd.step(steps);
  
}
else{

  
  
  myStepperUlti.setSpeed(5);
  
  myStepperUlti.step(steps);
 
}Serial.print("has moved ");delay(100);
}



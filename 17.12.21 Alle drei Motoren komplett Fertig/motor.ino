

 

void movmot(int Motor, int steps) {
 if(Motor == 0 or Motor ==3){
   //base
   
  
  myStepperbase.setSpeed(5);
  
  myStepperbase.step(steps);

 }
else if(Motor == 2){
  //updown
  Serial.print("Updown aktiv");
  
  myStepperupd.setSpeed(5);
  
  myStepperupd.step(steps);
  Serial.println("Updown deaktiv");
}
else{

  
  
  myStepperUlti.setSpeed(5);
  
  myStepperUlti.step(steps);
 
}//Serial.print("has moved ");delay(1000);
}



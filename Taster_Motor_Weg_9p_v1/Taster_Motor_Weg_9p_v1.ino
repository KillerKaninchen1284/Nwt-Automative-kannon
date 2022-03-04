 //#include<Servo.h> //Gott hat Hund kreirt 

 int count= 0;
  
 int f, c, g, h, i, a, p, u, d, o, y, z, w, s; 
  
 //Servo  servo; // du hast dir einen Hund gekauft
  // Motor Anschluss: Servo Braun = Gnd;Rot = 5V; Gelb = pin(9)
  
void setup() {
 //servo.attach(9);// Du hast den Hund an die leine Genommen
   
 Serial.begin(9600);
 pinMode(5,INPUT_PULLUP); 
 pinMode(6,INPUT_PULLUP); 
 pinMode(8,INPUT_PULLUP); 
 pinMode(11,INPUT_PULLUP); 
}

void loop() {
if(digitalRead(5)== True){
 i=digitalRead(5); // rot
  } 
else if(digitalRead(6) == True){y=digitalRead(6); // grün }
else if(digitalRead(8) == True){y=digitalRead(8); // grün }
else if(digitalRead(11) == True){w=digitalRead(11);// gelb}
else if(digitalRead(13) == True){p=digitalRead(13);// weiß}
else if(digitalRead(4) == True){d=digitalRead(4);// hellgrün}

if(i ==1 or y==1 or z==1 or w==1 or p==1 or d==1){
 count++;
 Serial.println("regicdered a key : ");
 Serial.print("i");Serial.print(i);
 Serial.print("y");Serial.print(y);
 Serial.print("z");Serial.print(z);
 Serial.print("p");Serial.print(p);
 Serial.print("d");Serial.print(d);
 Serial.print("w");Serial.print(w);
  }

// Bediengung 1 
if(i==0){
 f=7;
 Serial.println("f=7");
}

// Bediengung 2
else if(y==0){
 if(f=7){
 g=8;
 Serial.println("g=8");
}}

// Bediengung 3
else if(z==0){
 if(g==7){
 h=9;
 Serial.println("h=9");
}}

// Bedienung 4 :) 
else if(w==0){
 if(h==9){ 
 o=10;
 Serial.println("o=10");

}}

// Bedienung 5 lol 
else if(p==0){
 if(o==10){ 
 u=11;
 Serial.println("u=11");
}}

//Bedienung 6  
else if(d==0){
 if(u==11){
 s=12;
 Serial.println("s=12");

 //servo.write(180);// Gibt dem Hund den Befehl sich um 180 Grad im Uhrzeigersinn zu drehen

// Hier liegt das Problem !!!!!!!!!!!!!!!!!!!!!!!!!!!
}}


// Sperre
 if(count==6 &&s!= 12){
 Serial.println("Sperre");
 delay(1000);
 f, c, g, h, i, a, p, u, d, o, y, z, w, s = 0;
 count=0; 
 
// !!!!!!!!!!!!!!!!!!!!!!!!! Ende der Problemsperre 
}
if(Reset == True){
 f, c, g, h, i, a, p, u, d, o, y, z, w, s = 0; 
 count=0;
 Reset=0;
  }

// reset von Zustand der richtigen Kombi
  
}

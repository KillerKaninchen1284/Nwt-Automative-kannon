
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
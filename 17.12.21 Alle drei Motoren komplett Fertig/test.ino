
#include <bits/stdc++.h>
//#include<ArduinoSTL.h>
//#include<stl_algo.h>
#include<iostream>
float mostFrequent(float arr[], int n)
{
    // Sort the array
    std::sort(arr, arr + n);

    // find the max frequency using linear traversal
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

    // If last element is most frequent
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
//Mode2:Wenn Ergebnis Großen Unterschied zum vorderen (und Hinteren) hat Nochmal scannen
//Mode3:Wenn Disa Unterschied zu Dis mehrmals Durchlaufen, bis öfters das selbe ergebnis kommt only for 2nd run
if(ecm == 0){
  Serial.print("ECM Mode 0 ");
  return readsens();
}
else if(ecm ==1){
  Serial.print("ECM Mode 1 ");
   Serial.print("Buffer :(");
  for(int i;i<=ecmd;i++){
    buffer[i]= readsens();
    Serial.print(buffer[i]); Serial.print(",");
  }
  Serial.print(")  ");
  Serial.println(mostFrequent(buffer,sizeof(buffer) / sizeof(buffer[0])));
  
return mostFrequent(buffer,sizeof(buffer) / sizeof(buffer[0]));
//return ( (mostFrequent(buffer,sizeof(buffer) / sizeof(buffer[0]))<1000)* mostFrequent(buffer,sizeof(buffer) / sizeof(buffer[0])));
}
else if(ecm ==2){
  Serial.print("ECM Mode 2 ");
  float temp = readsens();
   if(((temp-myDis[Grad-1])>=-(myDis[Grad-1]/10) && (temp-myDis[Grad-1])<=(myDis[Grad-1]/10))){
      return temp;
   }
   else{Ecm(Grad,1);}

}
else if(ecm ==3){
  Serial.print("ECM Mode 3 ");
  float temp = readsens();
  
  if(((temp-myDis[Grad])>=-(myDis[Grad]/10) && (temp-myDis[Grad])<=(myDis[Grad]/10)) ||temp ==myDis[Grad]){return temp;
    
  }
  else if(myDis[Grad]==temp){return temp;}
  else{Serial.print("Here was a mistake over 10prozent ");  Serial.println(((temp-myDis[Grad])>=-(myDis[Grad]/10) && (temp-myDis[Grad])<=(myDis[Grad]/10)));
        Ecm(Grad,1);}
}

else{Serial.println("Error in Ecm-mode");}


//Serial.print("has scanned ");delay(100);
}
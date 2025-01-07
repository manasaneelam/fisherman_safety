//Set the LED light to pin 8

int LED = 8;

//Set the float sensor to pin 3
#define Float_Switch 3
#include<SoftwareSerial.h>
SoftwareSerial NEO6M(3,4);

void setup() {
  Serial.begin(115200);

  // initialize digital pin 8 as an output.
  pinMode(LED, OUTPUT);

 
  pinMode(Float_Switch, INPUT_PULLUP);
  Serial.begin(115200);
  NEO6M.begin(9600);
}

void loop() {
 
 if(digitalRead(Float_Switch) == HIGH)
  {
    digitalWrite(LED, HIGH); //Turn LED on
   

    Serial.println("warning!!!!!");
    while(NEO6M.available()>0){
     Serial.write(NEO6M.read());
    }
    
  }

 else
  {
    digitalWrite(LED, LOW); //Turn LED off
  }
}
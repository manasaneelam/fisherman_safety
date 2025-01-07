#include <SPI.h>
#include <LoRa.h>
#include <TinyGPSPlus.h>
const char *gpsStream =
"$GPGSV,3,2,10,14,44,005,22,15,03,305,,17,68,320,25,19,54,254,27*79";
// The TinyGPSPlus object
TinyGPSPlus gps;
//Set the LED light to pin 8
int LED = 8;
//Set the float sensor to pin 3
#define Float_Switch 3
#include<SoftwareSerial.h>
SoftwareSerial NEO6M(4,5);
int counter = 0;
void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
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
    LoRa.print("warning!!!!!");
   // while(NEO6M.available()>0)
   {
     Serial.print("Sending packet: ");
     Serial.println(counter);
  // send packet
     LoRa.beginPacket();
     LoRa.print(gps.location.lat(), 6);
     LoRa.print(gps.location.lng(), 6);
     //LoRa.print(gps.date.month());
     //LoRa.print(gps.date.day());
     //LoRa.print(gps.date.year());

     LoRa.print(counter);
     LoRa.endPacket();
     counter++;
    }
    
  }
 else
  {
    digitalWrite(LED, LOW); //Turn LED off
 }
  Serial.print("Sending packet: ");
  Serial.println(counter);
  delay(1000);
}

#include<ESP8266WiFi.h>

void setup() 
{  
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("mac address: ");
  Serial.println(WiFi.macAddress());
}

void loop() 
{

}

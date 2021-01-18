#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "P7V5V2TgrNBd9wqUiBeLTT3wqyMbiKEb";
char ssid[] = "S9+";  
char pass[] = "ghvb4765"; 

#define DHTPIN 2         
#define DHTTYPE DHT22    
#define buzzerPin 16 

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
int gasSensor;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  gasSensor=analogRead(A0);
  Serial.println(gasSensor);
  if(gasSensor>700)
  {
    digitalWrite(13,LOW);
    digitalWrite(14,HIGH); 
    tone(buzzerPin,800,40);
    Blynk.notify("Smoke Detected!!!");  
  } 
  if(t>40)
  {
      digitalWrite(13,HIGH);
      digitalWrite(14,LOW);
      tone(buzzerPin,800,40);
      Blynk.notify("Temperature is high!!!");    
  }
  Blynk.virtualWrite(V1, gasSensor);
  Blynk.virtualWrite(V5, h);  
  Blynk.virtualWrite(V6, t); 
}

void setup()
{
  Serial.begin(115200); 
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); 
  timer.run();
}

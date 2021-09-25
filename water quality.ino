#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
         // Pass the oneWire reference to Dallas Temperature.
#include <DallasTemperature.h>
#include <OneWire.h>
#define ONE_WIRE_BUS D6                          //D1 pin of nodemcu
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
BlynkTimer timer;
char auth[] = "qbTmzab1z9ADEnsHeuOBj4GAbB6E-8BS";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo 1723";
char pass[] = "244466666";
int ir=D1;
int irval;
WidgetLED R(V4);
WidgetLED G(V5);
int inlet=D2;
int outlet=D3;
int conduct=D5;
int conductval;
void setup()
{
  // Debug console
   
  Serial.begin(9600);
  pinMode(ir,INPUT);
  pinMode(inlet,OUTPUT);
  pinMode(outlet,OUTPUT);
  pinMode(conduct,INPUT);
  timer.setInterval(1000,sen);
  timer.setInterval(3000,temp);
  sensors.begin();
  
Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  timer.run();
}
 void sen()
 {


    irval=digitalRead(ir);
  conductval=digitalRead(conduct);

  
  if(irval==1) 
  {
  digitalWrite(inlet,1);
  digitalWrite(outlet,1);
  Blynk.virtualWrite(V1,"PURE");
  R.off();
  G.off();
  
  
      if(conductval==0)
      {
       Blynk.virtualWrite(V3," SOLUTION IS CONDUCTED"); 
      }
      else 
      {
      Blynk.virtualWrite(V3,"SOLUTION IS NOT CONDUCTED"); 
      }
  }
  else 
  {
           if(conductval==0)
      {
       Blynk.virtualWrite(V3," SOLUTION IS CONDUCTED"); 
      }
      else 
      {
      Blynk.virtualWrite(V3," SOLUTION IS NOT CONDUCTED"); 
      }
  Blynk.notify("Hey,Blynkers! water is polluted");
  digitalWrite(inlet,1);
  digitalWrite(outlet,0);
  Blynk.virtualWrite(V1,"DIRTY");
  R.on();
  G.off();
  delay(10000);
  digitalWrite(inlet,0);
  digitalWrite(outlet,1);
  R.off();
  G.on();
 delay(10000);
  
  
      
  }
  
  
  }
  void temp(void)
{ 
  sensors.requestTemperatures();                // Send the command to get temperatures  
  Serial.println("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0));   // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  delay(500);
  Blynk.virtualWrite(V10,sensors.getTempCByIndex(0));
}
  

  
  
 
 

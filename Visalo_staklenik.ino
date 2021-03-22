#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Data wire is connected to GPIO15
#define ONE_WIRE_BUS 4

const char* ssid     = "Vip WLAN_CF98EB_EXT";
const char* password = "EDC4A5ADED";
int temp_visoka_t1, temp_previsoka_t1, temp_niska_t1, temp_preniska_t1,temp_visoka_t2, temp_previsoka_t2, temp_niska_t2, temp_preniska_t2,temp_visoka_t5, temp_previsoka_t5, temp_niska_t5, temp_preniska_t5;
bool notifikacije_t1,n1t1=0,n2t1=0,n3t1,n4t1,notifikacije_t2,n1t2=0,n2t2=0,n3t2,n4t2,notifikacije_t5,n1t5=0,n2t5=0,n3t5,n4t5;
float temp1,temp2,temp3,temp4,temp5;

char auth[] = "9QeYduHvr8S0b5Ks077EguahjriaGRMX";

BlynkTimer  timer;
// Setup a oneWire instance to communicate with a OneWire device
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

DeviceAddress sensor1 = { 0x28, 0x8D, 0x6E, 0x56, 0xB5, 0x1, 0x3C, 0x8C };
DeviceAddress sensor2 = { 0x28, 0x45, 0xC8, 0x56, 0xB5, 0x1, 0x3C, 0x1D };
DeviceAddress sensor3= { 0x28, 0x2A, 0x19, 0x56, 0xB5, 0x1, 0x3C, 0x69 };
DeviceAddress sensor4= { 0x28, 0x5, 0xF, 0x56, 0xB5, 0x1, 0x3C, 0x1B };
DeviceAddress sensor5= { 0x28, 0xBF, 0x3A, 0x75, 0xD0, 0x1, 0x3C, 0xED };


BLYNK_CONNECTED() 
{
  // Request the latest state from the server
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V6);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V8);
  Blynk.syncVirtual(V9);
  Blynk.syncVirtual(V10);
  Blynk.syncVirtual(V15);
  Blynk.syncVirtual(V16);
  Blynk.syncVirtual(V17);
  Blynk.syncVirtual(V18);
  Blynk.syncVirtual(V19);
  Blynk.syncVirtual(V20);
  Blynk.syncVirtual(V21);
  Blynk.syncVirtual(V22);
  Blynk.syncVirtual(V23);
  Blynk.syncVirtual(V24);
   
  
}
BLYNK_WRITE(V6)
{
  temp_visoka_t1=param.asInt();
}

BLYNK_WRITE(V7)
{
  temp_previsoka_t1=param.asInt();
}
BLYNK_WRITE(V8)
{
  temp_niska_t1=param.asInt();
}

BLYNK_WRITE(V9)
{
  temp_preniska_t1=param.asInt();
}
 BLYNK_WRITE(V10)
{
 notifikacije_t1=param.asInt();
}
BLYNK_WRITE(V15)
{
  temp_visoka_t2=param.asInt();
}


BLYNK_WRITE(V16)
{
  temp_previsoka_t2=param.asInt();
}
BLYNK_WRITE(V17)
{
  temp_niska_t2=param.asInt();
}

BLYNK_WRITE(V18)
{
  temp_preniska_t2=param.asInt();
}
 BLYNK_WRITE(V19)
{
 notifikacije_t2=param.asInt();
}
BLYNK_WRITE(V20)
{
  temp_visoka_t5=param.asInt();
}


BLYNK_WRITE(V21)
{
  temp_previsoka_t5=param.asInt();
}
BLYNK_WRITE(V22)
{
  temp_niska_t5=param.asInt();
}

BLYNK_WRITE(V23)
{
  temp_preniska_t5=param.asInt();
}
 BLYNK_WRITE(V24)
{
 notifikacije_t5=param.asInt();
}

BLYNK_WRITE(V1) 
{//reset botun
 if((param.asInt()==1))
  {
  ESP.restart();
  }
}
void sendSensor()
{
sensors.requestTemperatures();
temp1=sensors.getTempC(sensor1);
temp2=sensors.getTempC(sensor2);
temp3=sensors.getTempC(sensor3);
temp4=sensors.getTempC(sensor4);
temp5=sensors.getTempC(sensor5);
Blynk.virtualWrite(V2,temp1);
Blynk.virtualWrite(V3,temp2);
Blynk.virtualWrite(V4,temp3);
Blynk.virtualWrite(V5,temp4);
Blynk.virtualWrite(V14,temp5);
Blynk.virtualWrite(V13, WiFi.RSSI()); 

}


void setup(){
  Serial.begin(115200);
  sensors.begin();
  
  WiFi.mode(WIFI_STA);//ZA OTA 
  WiFi.begin(ssid, password);    
    while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  // put your setup code here, to run once:
  
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
   ArduinoOTA.setHostname("Temperatura staklenik");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //Blynk.begin(auth, ssid, password);
  
  Blynk.config(auth);
  Blynk.connect();
  timer.setInterval(5000L, sendSensor);
}

void loop(){ 


  ArduinoOTA.handle();

  if(notifikacije_t1==HIGH)
    {
      if ((temp1<temp_visoka_t1))
         n1t1=0;
      if ((temp1<temp_previsoka_t1))
         n2t1=0;
      if ((temp1>temp_niska_t1))
         n3t1=0;
      if ((temp1>temp_preniska_t1))
         n4t1=0;         
         
      if ((temp1>temp_visoka_t1)&&(n1t1==0))
         {
          n1t1=1;
          Blynk.notify("T1 temperatura visoka");
         } 
      
      if ((temp1>temp_previsoka_t1)&&(n2t1==0))
         {
          n2t1=1;
          Blynk.notify("T1 temperatura previsoka !!!");
         }
      if ((temp1<temp_niska_t1)&&(n3t1==0))
         {
          n3t1=1;
          Blynk.notify("T1 temperatura niska");
         } 
      
      if ((temp1<temp_preniska_t1)&&(n4t1==0))
         {
          n4t1=1;
          Blynk.notify("T1 temperatura preniska !!!");
         }   
    }  
   if(notifikacije_t2==HIGH)
    {
      if ((temp2<temp_visoka_t2))
         n1t2=0;
      if ((temp2<temp_previsoka_t2))
         n2t2=0;
      if ((temp2>temp_niska_t2))
         n3t2=0;
      if ((temp2>temp_preniska_t2))
         n4t2=0;         
         
      if ((temp2>temp_visoka_t2)&&(n1t2==0))
         {
          n1t2=1;
          Blynk.notify("T2 temperatura visoka");
         } 
      
      if ((temp2>temp_previsoka_t2)&&(n2t2==0))
         {
          n2t2=1;
          Blynk.notify("T2 temperatura previsoka !!!");
         }
      if ((temp2<temp_niska_t2)&&(n3t2==0))
         {
          n3t2=1;
          Blynk.notify("T2 temperatura niska");
         } 
      
      if ((temp2<temp_preniska_t2)&&(n4t2==0))
         {
          n4t2=1;
          Blynk.notify("T2 temperatura preniska !!!");
         }   
    }  

   if(notifikacije_t5==HIGH)
      {
      if ((temp5<temp_visoka_t5))
         n1t5=0;
      if ((temp5<temp_previsoka_t5))
         n2t5=0;
      if ((temp5>temp_niska_t5))
         n3t5=0;
      if ((temp5>temp_preniska_t5))
         n4t5=0;         
         
      if ((temp5>temp_visoka_t5)&&(n1t5==0))
         {
          n1t5=1;
          Blynk.notify("Vanka temperatura visoka");
         } 
      
      if ((temp5>temp_previsoka_t5)&&(n2t5==0))
         {
          n2t5=1;
          Blynk.notify("Vanka temperatura previsoka !!!");
         }
      if ((temp5<temp_niska_t5)&&(n3t5==0))
         {
          n3t5=1;
          Blynk.notify("Vanka temperatura niska");
         } 
      
      if ((temp5<temp_preniska_t5)&&(n4t5==0))
         {
          n4t5=1;
          Blynk.notify("Vanka temperatura preniska !!!");
         }   
      }  

   if(!Blynk.connected())
    {
      WiFi.begin(ssid, password);
      Serial.println("Not connected to Blynk server"); 
      Blynk.connect(3333);  // timeout set to 10 seconds and then continue without Blynk  
    }
    else 
    Blynk.run();
    timer.run();
 
 
  
}

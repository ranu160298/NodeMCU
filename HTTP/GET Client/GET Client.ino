#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiServer server(80);

int i;
String  httpurl;
HTTPClient http;

void setup()
{
  i = 0;
  
  Serial.begin(9600);

  WiFi.disconnect();
  delay(1000);
  
  WiFi.begin("SSID","Password");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
  }Serial.println("Connected");
}


void loop()
{
  server.begin();
  
  if(i==20){
    i=0;
  }
  
  httpurl = "http://shounaks.cf/put.php?d1=";
  httpurl+=String(i);
  httpurl+="&d2=";
  httpurl+=String(analogRead(A0));
  i++;
  
  http.begin(httpurl);
  http.GET();
  
  String reply=http.getString();
  http.end();
  Serial.println(reply);
  delay(500);
}


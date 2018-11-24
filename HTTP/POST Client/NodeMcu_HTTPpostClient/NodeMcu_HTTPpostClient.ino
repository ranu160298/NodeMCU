#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

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
  
  WiFi.begin("Redmi","hello1234t");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
  }Serial.println("Connected");
}


void loop()
{
  server.begin();
  String postData;
  
  if(i==20){
    i=0;
  }
  postData = "d1=" + String(i) + "&d2=" + String(analogRead(A0)) ;
  httpurl = "http://rohit67.cf/put.php?";
  i++;
  
  http.begin(httpurl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);   //Send the request
  
  String reply=http.getString();
  http.end();
  Serial.println(reply);
  delay(500);
}


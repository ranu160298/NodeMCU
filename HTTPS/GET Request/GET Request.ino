#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;

void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP("SSID", "Password");
}

void loop() {
  int i=5;
  String postData = "d1=" + String(i) + "&d2=" + String(analogRead(A0));
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
  HTTPClient http;
  USE_SERIAL.print("[HTTPS] begin...\n");
  http.begin("https://shounaks.cf/put.php?d1=6&d2=3", "F4:6C:85:31:D4:3E:6A:F8:67:EE:5D:FB:E5:F7:85:65:C6:81:39:41");
  USE_SERIAL.print("[HTTPS] GET...\n");
  int httpCode = http.GET();
  i++;
  // httpCode will be negative on error
  if(httpCode > 0) {
  // HTTP header has been send and Server response header has been handled
  USE_SERIAL.printf("[HTTPS] GET... code: %d\n", httpCode);
  // file found at server
  if(httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    USE_SERIAL.println(payload);
    }
  }
  else {
    USE_SERIAL.printf("[HTTPS] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  http.end();
    }
  delay(10000);
}

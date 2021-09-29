/*
  Date: 24-09-21
  Code written by: Dharmik
  This sketch trys to Connect to the best WiFi network based on a given list
  Find more on www.TechTOnions.com
*/

#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

#define WiFi_timeout 10000  // 10sec Wifi connection timeout

const char* ssid0 = "TechTOnions";
const char* pass0 = "Dtirth123";

const char* ssid1 = "aaaaaaa";
const char* pass1 = "12345678";

const char* ssid2 = "Your SSID 2";
const char* pass2 = "Your Password 2";

const char* ssid3 = "Your SSID 3";
const char* pass3 = "Your Password 3";

void setup()
{
  Serial.begin(115200);
  delay(100);

  //Adding all WiFi credential to WiFi multi class
  wifiMulti.addAP(ssid0, pass0);
  wifiMulti.addAP(ssid1, pass1);
  wifiMulti.addAP(ssid2, pass2);
  wifiMulti.addAP(ssid3, pass3);

  Serial.println("Connecting Wifi...");

  //Connecting to the strongest WiFi connection
  if (wifiMulti.run(WiFi_timeout) == WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  //print IP of the connected WiFi network
  }
  else  // if not WiFi not connected
  {
    Serial.println("WiFi not Connected");
  }
}

void loop()
{
  // if WiFi is not connected try again to connect with default timeout of 5sec
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  }
}

/*
  Date: 11-08-21
  Code is written by: Dharmik
  Configure ESP32 Wi-Fi parameters using SmartConfig
  Find more on www.TechTOnions.com
*/
#include "WiFi.h"
#include "EEPROM.h"
#define LENGTH(x) (strlen(x) + 1)   // length of char string
#define EEPROM_SIZE 200             // EEPROM size
#define WiFi_rst 0                  //WiFi credential reset pin (Boot button on ESP32)
String ssid;                        //string variable to store ssid
String pss;                         //string variable to store password
unsigned long rst_millis;

void setup() {
  Serial.begin(115200);             //Init serial
  pinMode(WiFi_rst, INPUT);
  if (!EEPROM.begin(EEPROM_SIZE)) { //Init EEPROM
    Serial.println("failed to init EEPROM");
    delay(1000);
  }
  else
  {
    ssid = readStringFromFlash(0); // Read SSID stored at address 0
    Serial.print("SSID = ");
    Serial.println(ssid);
    pss = readStringFromFlash(40); // Read Password stored at address 40
    Serial.print("psss = ");
    Serial.println(pss);
  }

  WiFi.begin(ssid.c_str(), pss.c_str());

  delay(3500);   // Wait for a while till ESP connects to WiFi

  if (WiFi.status() != WL_CONNECTED) // if WiFi is not connected
  {
    //Init WiFi as Station, start SmartConfig
    WiFi.mode(WIFI_AP_STA);
    WiFi.beginSmartConfig();

    //Wait for SmartConfig packet from mobile
    Serial.println("Waiting for SmartConfig.");
    while (!WiFi.smartConfigDone()) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("SmartConfig received.");

    //Wait for WiFi to connect to AP
    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi Connected.");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // read the connected WiFi SSID and password
    ssid = WiFi.SSID();
    pss = WiFi.psk();
    Serial.print("SSID:");
    Serial.println(ssid);
    Serial.print("PSS:");
    Serial.println(pss);
    Serial.println("Store SSID & PSS in Flash");
    writeStringToFlash(ssid.c_str(), 0); // storing ssid at address 0
    writeStringToFlash(pss.c_str(), 40); // storing pss at address 40
  }
  else
  {
    Serial.println("WiFi Connected");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  rst_millis = millis();
  while (digitalRead(WiFi_rst) == LOW)
  {
    // Wait till boot button is pressed 
  }
  // check the button press time if it is greater than 3sec clear wifi cred and restart ESP 
  if (millis() - rst_millis >= 3000)
  {
    Serial.println("Reseting the WiFi credentials");
    writeStringToFlash("", 0); // Reset the SSID
    writeStringToFlash("", 40); // Reset the Password
    Serial.println("Wifi credentials erased");
    Serial.println("Restarting the ESP");
    delay(500);
    ESP.restart();            // Restart ESP
  }
}


void writeStringToFlash(const char* toStore, int startAddr) {
  int i = 0;
  for (; i < LENGTH(toStore); i++) {
    EEPROM.write(startAddr + i, toStore[i]);
  }
  EEPROM.write(startAddr + i, '\0');
  EEPROM.commit();
}


String readStringFromFlash(int startAddr) {
  char in[128]; // char array of size 128 for reading the stored data 
  int i = 0;
  for (; i < 128; i++) {
    in[i] = EEPROM.read(startAddr + i);
  }
  return String(in);
}

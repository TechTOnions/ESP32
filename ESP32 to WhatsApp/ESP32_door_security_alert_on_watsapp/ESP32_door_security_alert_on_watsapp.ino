    
/*
  Date: 25-06-21
  Code written by: Dharmik
  ESP32 sending a message to WhatsApp messenger
  Find more on www.TechTOnions.com
*/

#include <WiFi.h>         //Including wifi.h library it will take care of all wifi related task
#include <HTTPClient.h>   //Including HTTPClient.h library to use all api
#include <RCSwitch.h>     //Including RCSwitch.h library to read RF data

RCSwitch mySwitch = RCSwitch();
#define RF_data_pin 23

const char* ssid = "Replace me with your SSID";             //Add your WiFi ssid
const char* password =  "Replace me with your PASSWORD";    //Add your WiFi password

String apiKey = "222222";              //Add your Token number that bot has sent you on WhatsApp messenger
String phone_number = "+917561123123"; //Add your WhatsApp app registered phone number (same number that bot send you in url)
long sensor_address = 16285605;        //Any 433Mhz wirless sensor unique address
String url;                            //url String will be used to store the final generated URL

void setup()
{
  Serial.begin(9600);
  mySwitch.enableReceive(RF_data_pin);

  WiFi.begin(ssid, password);              // Try to connect with the given SSID and PSS
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {  // Wait until WiFi is connected
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to the WiFi network"); // Print wifi connect message
}

void loop()
{
  if (mySwitch.available()) {
    if(sensor_address == mySwitch.getReceivedValue())   // compare the sensor address 
    {
      message_to_whatsapp("Alert!!! Someone Opened Your Door.");  // Sending alert message to WhatsApp
      delay(3000);
    }
    mySwitch.resetAvailable();  // Reset the data received 
  }
}

void  message_to_whatsapp(String message)       // user define function to send meassage to whatsapp app
{
  //adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlencode(message);

  postData(); // calling postData to run the above-generated url once so that you will receive a message.
}

void postData()     //userDefine function used to call api(POST data)
{
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url); // Finaly Post the URL with this function and it will store the http code
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent ok."); // print message sent ok message
  }
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("Error."); // print error message.
  }
  http.end();          // After calling API end the HTTP client object.
}

String urlencode(String str)  // Function used for encoding the url
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}

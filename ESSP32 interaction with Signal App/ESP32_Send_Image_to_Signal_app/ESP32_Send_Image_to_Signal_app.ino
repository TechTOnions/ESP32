/*
  Date: 07-05-21
  Code written by: Dharmik
  ESP32 sending image to Signal messenger
  Find more on www.TechTOnions.com
*/

#include <WiFi.h>        //Including wifi.h library it will take care of all wifi related task
#include <HTTPClient.h>  //Including HTTPClient.h library to use all api

const char* ssid =      "Replace me with your SSID";        //Add your WiFi ssid
const char* password =  "Replace me with your PASSWORD";    //Add your WiFi password

String apiKey = "222222";              //Add your Token number that bot has sent you on signal messenger
String phone_number = "+917561123123"; //Add your signal app registered phone number with country code (the same number that bot send you in url)  
String url;                            //url String will be used to store the final generated URL


void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);             // Try to connect with the given SSID and PSS
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) { // Wait until WiFi is connected
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to the WiFi network");  // Print wifi connect message

  //image_to_signal function will send your image to Signal app
  //Just you have to add your image url
  //it only works for .jpg .gif .png    // not working with .webp image format 
  image_to_signal("https://www.techtonions.com/wp-content/uploads/2021/05/New-Profile-picture-logo-big-250x250-1.jpg");
}

void loop()
{
  //loop will do nothing for this example
}


void image_to_signal(String img_url)  //user define function to send image to Signal App
{
  //adding all number, your api key, your image url into one complete url
  url = "https://api.callmebot.com/signal/send.php?phone="+ phone_number + "&apikey=" + apiKey + "&image=" + urlencode(img_url);
  postData(); // caling postData to run the above generated url once so that you will receive image.
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
  http.end();         // After calling API end the HTTP client object.
}

String urlencode(String str)  // Function used for encoding the url
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}

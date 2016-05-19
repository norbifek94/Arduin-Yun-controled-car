/*
controlling rgb led via http 
gnd - gnd
5v  - 5v
datain  - pin 4

arduinoyun/red
arduinoyun/green
arduinoyun/blue
arduinoyun/random

 http://arduino.cc/en/Tutorial/Bridge

 */

 #define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Adafruit_NeoPixel.h>
// Listen to the default port 5555, the Yún webserver
// will forward there all the HTTP requests you send
YunServer server;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
String a;
String b="first";
void setup() {
  // Bridge startup
    pixels.begin(); 
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(200); // Poll every 50ms
  if(a!=b){
   if(a=="green"){
   // Serial.println("--------"+a+"-----------");
            pixels.setPixelColor(0, pixels.Color(random(255),random(0),random(0))); // Moderately bright green color.
          pixels.show();
      }else if(a=="red"){
    //    Serial.println("--------"+a+"-----------");
            pixels.setPixelColor(0, pixels.Color(random(0),random(255),random(0))); // Moderately bright green color.
          pixels.show();
      }else if(a=="blue"){
      //  Serial.println("--------"+a+"-----------");
            pixels.setPixelColor(0, pixels.Color(random(0),random(0),random(255))); // Moderately bright green color.
        pixels.show();
      }
      b=a;
  }
      if(a=="random"){
      //  Serial.println("--------"+a+"-----------");
            pixels.setPixelColor(0, pixels.Color(random(255),random(255),random(255))); // Moderately bright green color.
           pixels.show();
      }
 
     //Serial.println("test"+a+"test");
}

void process(YunClient client) {
  // read the command
  String command = client.readStringUntil('/');
  
  // is "digital" command?
  Serial.println("'"+command+"'");
 
  if(command=="red\r\n"){
            a="red";   
           // Serial.println("command--------"+a+"-----------");       
      }else if(command=="green\r\n"){
            a="green";    
           //  Serial.println("command--------"+a+"-----------");             
      }else if(command=="blue\r\n"){
            a="blue"; 
           //  Serial.println("command--------"+a+"-----------");                
      }else if(command=="random\r\n"){
            a="random";     
          //   Serial.println("command--------"+a+"-----------");            
      }
  client.print(F("Led D"));
  client.print("is");
  client.print(F(" set to "));
  client.println(a);

  // Update datastore key with the current pin value
  String key = "D";
  key += "13";
  Bridge.put(key, String("valami"));
  
}



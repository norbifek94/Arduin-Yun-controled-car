#include <Process.h>
#include <Bridge.h>
#include <String.h>


#define cs   12
 #define dc   10
 #define rst  11
#define PIN            7

Process pServer;

#define irLedPin 6          // IR Led on this pin
#define irSensorPin0 A0       // IR sensor on this pin
#define irSensorPin1 A1
#define irSensorPin2 A2
#define irSensorPin3 A3




boolean p=false;


const char ENDMESS = '\n';
String IP = "";
String PORT = "";
String PyPort = "1003";

String readFromServer(){
  int c = pServer.read();
  String str="";
  if(c!=-1){
    while(c!=-1){
        if(char(c)=='\n') break;
        str+= char(c);
        c=pServer.read();
    }
  }
  return str;
  
}



void setup() {
  Serial.println("bridge starting");

     Bridge.begin();
     Serial.println("bridge end");
  
   Serial.begin(115200);
  while(!Serial);
 
   
pServer.runShellCommandAsynchronously("python ~/test.py");

  delay(1000);
  
}


void loop() {
  // Serial.println("start loop");
   if(!pServer.running()){
        Serial.println("Server started");
        pServer.runShellCommandAsynchronously("python ~/test.py");
     }

      

        String fromServer=readFromServer();
   if(fromServer!=""){
        //Serial.println(fromServer);
        if(fromServer=="true"){
            digitalWrite(13, HIGH);
        }else{
          digitalWrite(13, LOW);
        }
   }
}








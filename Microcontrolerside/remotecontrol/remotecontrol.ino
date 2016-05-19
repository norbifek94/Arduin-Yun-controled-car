#include <Process.h>
#include <Bridge.h>
#include <String.h>
Process pServer;
// motor one
int enA = 11;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 10;
int in3 = 12;
int in4 = 13;
// distance right motor
int distance1 = 7;
// distance left motor
int distance2 = 6;
int maxSpeed = 220;
int maxSpeed2 = 220;
int rotR=0;
int rotL=0;

const int trigPin = 5;
const int echoPinRightSide = A2;
const int echoPinBack = A1;
const int echoPinFront = A0;

#define OTHERCAR 20
#define CARLENGTH 28
#define CARWIDTH 16
#define CARRADIUS 16

void setup() {
 

   Bridge.begin();
     Serial.println("bridge end");
 pServer.runShellCommandAsynchronously("pyhton ~/server.py");      
 
  Serial.println("shelrun");
   delay(500);
  pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
  pinMode(distance1, INPUT);
 pinMode(distance2, INPUT);

 pinMode(trigPin, OUTPUT);
pinMode(echoPinRightSide, INPUT);
pinMode(echoPinBack , INPUT);
pinMode(echoPinFront, INPUT);

 
 delay(500);
   Serial.begin(250000);
}
void stopp(){
  Serial.println("S");
  analogWrite(enA,0);
  analogWrite(enB,0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  rotR=0;
  rotL=0;
}
bool distanceR=true;
bool distanceL=true;

String fromServer;
void loop() {
 if(!pServer.running()){
        Serial.println("Server started");
                  
        pServer.runShellCommandAsynchronously("python ~/server.py");  
        delay(500);    
        
     }/*
     Serial.println("test");
      if(distanceR != digitalRead(distance1)){
          distanceR = digitalRead(distance1);
          rotR++;
          if(rotR%40==0){
           Serial.print("R ");
           Serial.println(rotR/40);
          }
        }
        if(distanceL != digitalRead(distance2)){
          distanceL = digitalRead(distance2);
          rotL++;
          if(rotL%40==0){
          Serial.print("L ");
           Serial.println(rotL/40);
          }
        }*/
      //  tryPark();
   fromServer=readFromServer();
  //Serial.println("try read");
  //delay(2000);
   if(fromServer!=""){
        Serial.println(fromServer);
        if(fromServer=="forward"){
            forward();
        }else if(fromServer=="backward"){
          backward();
        }else if(fromServer=="leftForward"){
          leftF();
        }else if(fromServer=="rightForward"){
          rightF();
        }else if(fromServer=="leftBackward"){
          leftB();
        }else if(fromServer=="rightBackward"){
          rightB();
        }else if(fromServer=="test"){
          tryPark();
        }else{
          stopp();
        }
   }
     
}
void forward()
{
  stopp();
  Serial.println("F");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enB,maxSpeed2);
  analogWrite(enA,maxSpeed);
}

void backward()
{
  Serial.println("B");
  stopp();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA,maxSpeed);
  analogWrite(enB,maxSpeed2);
}

void leftF()
{
  stopp();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA,maxSpeed);
  analogWrite(enB,maxSpeed2);
}
 
void rightF()
{
  stopp();
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA,maxSpeed);
  analogWrite(enB,maxSpeed2);
}
void leftB()
{
  stopp();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA,maxSpeed);
  analogWrite(enB,maxSpeed2);
}
 
void rightB()
{
  stopp();
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA,maxSpeed);
  analogWrite(enB,maxSpeed2);
}


 int helper;
  bool spaceDetected;
  int startParkingDistance;
  int endParkingDistance;

  
void tryPark(){

 
  Serial.println("startParking");
  delay(5000);
 
  checkRotation(true);
  helper = obstacleDistRight();
  spaceDetected=false;
  startParkingDistance=0;
  endParkingDistance=0;
   forward();
   Serial.print("Helper");
      Serial.println(helper);
  while((rotR+rotL)<180){
    if(!spaceDetected){
       
        if(obstacleDistRight()- helper > 20){
          
          spaceDetected=true; 
          startParkingDistance=(rotR+rotL)/2;

          }
    }else{
 
         if((obstacleDistRight() - helper) < 20) {
            endParkingDistance=(rotR+rotL)/2; 
            break;
        }
    }
    checkRotation(false);
  }
   stopp();
  checkRotation(true);
  Serial.println("VegeMeres");
  Serial.print("STARTspace ");
  Serial.println(startParkingDistance);
  Serial.print("ENDspace ");
  Serial.println(endParkingDistance);
  Serial.print("space in cm ");
  double dist = rotToCm(endParkingDistance-startParkingDistance);
  Serial.println(dist);
//#define CARLENGTH 30
//#define CARWIDTH 18
//#define CARRADIUS 15


  doParking(0,helper + OTHERCAR + (CARWIDTH/2),dist-5, CARRADIUS + (OTHERCAR/2),CARRADIUS);
 
  //-------------
  /*leftB();
  checkRotation(true);
  while(rotR<70){
    checkRotation(false);
  }
  stopp();
  delay(1000);
   leftF();
  checkRotation(true);
  while(rotR<70){
    checkRotation(false);
  }
  
  stopp();
    delay(1000);
  rightB();
  checkRotation(true);
  while(rotL<70){
    checkRotation(false);
  }
  stopp();
  delay(1000);
   rightF();
  checkRotation(true);
  while(rotL<70){
    checkRotation(false);
  }
  stopp();

  stopp();
    delay(1000);
  forward();
  checkRotation(true);
  while(rotL+rotR<120){
    checkRotation(false);
  }
  stopp();
  delay(1000);
   backward();
  checkRotation(true);
  while(rotL+rotR<120){
    checkRotation(false);
  }  
  stopp();*/
  //-------------
  delay(10000);
 /* backward();
  while((rotR+rotL)<150) checkRotation(false);
 
  stopp();
  delay(5000);
 */
}

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

void checkRotation(bool first){
  if(first){rotR=0;rotL=0;}
 
  if(distanceR != digitalRead(distance1)){
 

          distanceR = digitalRead(distance1);
          rotR++;
          if(rotR%40==0){
           Serial.print("R ");
           Serial.println(rotR/40);
          }
        }
        if(distanceL != digitalRead(distance2)){
          distanceL = digitalRead(distance2);
          rotL++;
          if(rotL%40==0){
          Serial.print("L ");
          Serial.println(rotL/40);
          }
        }
}

int obstacleDistFront(){
  return readDistance(echoPinFront);
}

double cmToRot(double cm){
    return cm*1.5;
}

double rotToCm(double cm){
    return cm/1.1;
}

double rotToCmKanyar(double cm){
    return cm/1.9;
}

double cmToRotKanyar(double cm){
      return cm*2.3;
}

/*
const int echoPinRightSide = A2;
const int echoPinBack = A1;
const int echoPinFront = A0;
*/
int obstacleDistBack(){
   return readDistance(echoPinBack);
}

int obstacleDistRight(){
  return readDistance(echoPinRightSide);
}

int distanceInCm =0;
 int d;
int readDistance(int echoPin){

delay(10);
  while(true){

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);
  
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    d=pulseIn(echoPin, HIGH);
    distanceInCm= d / 29 / 2;
    // convert the time into a distance
    if((distanceInCm>2) && (distanceInCm<2000)) break;
  }
 // Serial.println(distanceInCm);
  return distanceInCm;
}

bool doParking(double Ax, double Ay, double Bx, double By, double Ar){
    
        Serial.print("Kor A x =");
        Serial.println(Ax);
        
        Serial.print("Kor A y =");
        Serial.println(Ay);
        
        Serial.print("Kor A r =");
        Serial.println(Ar);


         Serial.print("Kor B x =");
        Serial.println(Bx);
        
        Serial.print("Kor B y =");
        Serial.println(By);
        
        Serial.print("Kor B r =");
        Serial.println(Ar);


        double Kx = ((3*Ax) + Bx) / 4;
        double Ky = ((3*Ay) + By) / 4;
        double Kr = distance(Ax, Ay, Bx, By)/4;

        Serial.print("Kor seged x =");
        Serial.println(Kx);
        
        Serial.print("Kor seged y =");
        Serial.println(Ky);
        
        Serial.print("Kor seged r =");
        Serial.println(Kr);

        double AF = distance(Ax, Ay, Kx, Ky);

        Serial.print("AF =");
        Serial.println(AF);
        
        double AQ = ((pow(Ar,2)) - pow(Kr,2) + pow(AF,2))/(2*AF);

        Serial.print("AQ =");
        Serial.println(AQ);

        

        double Qx = Ax + ((AQ/AF)*(Kx - Ax));
        double Qy = Ay + ((AQ/AF)*(Ky - Ay));
         Serial.print("Qx =");
        Serial.println(Qx);
         Serial.print("Qy =");
        Serial.println(Qy);

        double QD = sqrt(pow(Ar,2)-pow(AQ,2));
        Serial.print("QD =");
        Serial.println(QD);

        double Dx = Qx - ((QD / AF) * (Ky - Ay));        
        double Dy = Qy + ((QD / AF) * (Kx - Ax));

        Serial.print("Dx =");
        Serial.println(Dx);
         Serial.print("Dy =");
        Serial.println(Dy);


        double LD = distance(Ax,Ay+Ar,Dx,Dy);

        Serial.print("LD =");
        Serial.println(LD);
        
        double LAD = angleInRad(Ar,LD,Ar);

        Serial.print("LAD =");
        Serial.println(LAD);

        double p = distanceOnCircle(Ar,LAD);

        Serial.print("p =");
        Serial.println(p);
  
        double DP = distance(Dx, Dy, (Ax+Bx)/2, (Ay+By)/2);

        Serial.print("DP =");
        Serial.println(DP);    

        delay(1000);

        int kanyarRot = cmToRotKanyar(p);
        int egyenesRot = cmToRot(DP);

        Serial.print("kanyarRot =");
        Serial.println(kanyarRot);  
         Serial.print("egyenesRot =");
        Serial.println(egyenesRot);  

        
        
          delay(1000);
             backward();
          checkRotation(true);
          while(rotL+rotR<5){
            checkRotation(false);
          }
          stopp();
           delay(500);
           rightB();
          checkRotation(true);
          while(rotL<kanyarRot){
            checkRotation(false);
          }
          stopp();
        

            delay(500);
          backward();
          checkRotation(true);
          while(rotL+rotR<(egyenesRot*2)){
            checkRotation(false);
          }
          stopp();
          delay(500);


           leftB();
          checkRotation(true);
          while(rotR<kanyarRot){
            checkRotation(false);
          }
          stopp();
}

double distance(double x0, double y0, double x1, double y1){
    return sqrt(pow(x0-x1,2) + pow(y0-y1,2));
}

double angleInRad(double a, double b, double c){
    return  acos((pow(a,2) + pow(c,2) - pow(b,2))/(2*a*c));
}

double distanceOnCircle(double radius, double angleInRadian){
  return radius*angleInRadian;
}




#define CARLENGTH 30
#define CARWIDTH 18
#define CARRADIUS 15
void setup() {
  // put your setup code here, to run once:

Serial.println("start");
}

void loop() {
  // put your main code here, to run repeatedly:
delay(1000);
doParking(0,45 ,40,24,CARRADIUS);
delay(10000);
}
/*
    double Ax = 0;                                  //    KorA x kozep
        double Ay = depth + (CARWIDTH/2) - CARRADIUS;   //    KorA y kozep
        double Ar = CARRADIUS;                               //    KorA r sugar

        Serial.print("A x =");
        Serial.println(Ax);
        
        Serial.print("A y =");
        Serial.println(Ay);
        
        Serial.print("A r =");
        Serial.println(Ar);

        double Bx = endX - startX;                    //    KorA x kozep
        double By = CARRADIUS + CARWIDTH/2;             //    KorA y kozep
        double Br = CARRADIUS;                        //    KorA r sugar

        Serial.print("B x =");
        Serial.println(Bx);
        
        Serial.print("B y =");
        Serial.println(By);
        
        Serial.print("B r =");
        Serial.println(Br);*/

bool doParking(double Ax, double Ay, double Bx, double By, double Ar){
    

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



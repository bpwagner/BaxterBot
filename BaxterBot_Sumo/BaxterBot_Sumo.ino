/*
BaxterBot Test Program

6/23/13
1.0 8/13/13 - includes us,line sensor, motor, led and tone test.

YOU MUST INSTALL THE QTRSensors, NewPing and NewTone libraries!
google it!


10/4/13
So this program is one that will be used for testing and other things
hold USW1 down when it starts to get to the test program
hold USW2 down when it starts to do line following
hold nothing down and the bot will wait for you to hit one of the switches to start it in sumo mode!


*/
#include <QTRSensors.h>
#include <NewPing.h>
#include <NewTone.h>


// pin Definitions
int LED_R = 9;
int LED_G = 10;
int LED_B = 11;

int Buzzer_Servo = 3;

int SW_1 = 2;
int SW_2 = 8;

//Motor Pins
int Mot_EN1 = 5;  
int Mot_EN2 = 6;  
int Mot_IN1 = 4;
int Mot_IN2 = 7; 

//line sensor pins
int Line_Sensor_Left = 13;
int Line_Sensot_Right = 12;

//ultra sonic sensor pins
#define TRIGGER_PIN  14  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     15  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//initialize the line senosrs
QTRSensorsRC qtrrc((unsigned char[]) {Line_Sensor_Left, Line_Sensot_Right},
  2, 2048, QTR_NO_EMITTER_PIN); 
unsigned int sensorValues[2];

//initialize the ultrasonic
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//variables for the push button
int button1=0;
int button2=0;

//sumo mode or line follow mode or test mode?
int mode=0;

//set the forward direction of your sumo here
boolean Mot1Dir = true;
boolean Mot2Dir = false;


int Mot1Speed = 200; 
int Mot2Speed = 200;
int TurnSpeed = 150;
int TurnDelay = 400; 

int LineThreshold = 750;
int PingThreshold = 600;


//****************************************************************************

void h2rgb(float H, int& R, int& G, int& B) {

  int var_i;
  float S=1, V=1, var_1, var_2, var_3, var_h, var_r, var_g, var_b;

  if ( S == 0 )                       //HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      //H must be < 1
    var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if      ( var_i == 0 ) {
      var_r = V     ;
      var_g = var_3 ;
      var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
      var_r = var_2 ;
      var_g = V     ;
      var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
      var_r = var_1 ;
      var_g = V     ;
      var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
      var_r = var_1 ;
      var_g = var_2 ;
      var_b = V     ;
    }
    else if ( var_i == 4 ) {
      var_r = var_3 ;
      var_g = var_1 ;
      var_b = V     ;
    }
    else                   {
      var_r = V     ;
      var_g = var_1 ;
      var_b = var_2 ;
    }

    R = (1-var_r) * 255;                  //RGB results = 0 ÷ 255
    G = (1-var_g) * 255;
    B = (1-var_b) * 255;
  }
}
 
 

 
void Motor1(int pwm, boolean reverse)
        {
          analogWrite(Mot_EN1,pwm); //set pwm control, 0 for stop, and 255 for maximum speed
         if(reverse)
         { 
          digitalWrite(Mot_IN1,HIGH);    
         }
        else
        {
          digitalWrite(Mot_IN1,LOW);    
         }
        }  
         
void Motor2(int pwm, boolean reverse)
        {
          analogWrite(Mot_EN2,pwm);
         if(reverse)
         { 
          digitalWrite(Mot_IN2,HIGH);    
         }
        else
        {
          digitalWrite(Mot_IN2,LOW);    
         }
        }  
        
void RGBLed(int r, int g, int b) {
    analogWrite(LED_R, r);
    analogWrite(LED_G, g);
    analogWrite(LED_B, b);
}

//****************************************************************************
        

void setup() {
  int i;
  int r=0, g=0, b=0;
  float h;
  
  delay(500);
  Serial.begin(9600);
  delay(1000);
  Serial.println("BaxterBot Sumo program");

  
  //set up the user switches...
  pinMode(SW_1, INPUT);    // declare pushbutton as input
  digitalWrite(SW_1,HIGH);  //engages internal pullup resistor
  pinMode(SW_2, INPUT);    // declare pushbutton as input
  digitalWrite(SW_2,HIGH);  //engages internal pullup resistor
  
  button1 = digitalRead(SW_1);  // read input value
  button2 = digitalRead(SW_2);  // read input value
  
  if (button1 == HIGH && button2 == LOW) mode = 1; //test mode
  else if (button1 == LOW && button2 == HIGH) mode = 2; //line follow mode
  else mode = 0; //sumo mode
      
  //motors
    for(i=4;i<=7;i++)  
    pinMode(i, OUTPUT);  //set pin 4,5,6,7 to output mode
  
  RGBLed(0, 0, 0);
  

  
}


void TestMode() {
  
  float h;
  int r=0, g=0, b=0;

  while(1){
        button1 = digitalRead(SW_1);  // read input value
        button2 = digitalRead(SW_2);  // read input value
      
        if (button1 == LOW && button2 == LOW) {  
          NewTone(Buzzer_Servo, 784, 50); 
          //Serial.println("Motor 1 and 2 ON");
      
          Motor1(200, !Mot1Dir);
          Motor2(200, !Mot2Dir);
        
        } else if (button1 == HIGH && button2 == LOW) {
        // Serial.println("Motor 1 ON");
         NewTone(Buzzer_Servo, 294, 50);
         RGBLed(255, 0, 255);
         Motor1(200,Mot1Dir);
         Motor2(0,Mot2Dir);
         
        } else if (button1 == LOW && button2 == HIGH) {
          // Serial.println("Motor 2 ON");
          NewTone(Buzzer_Servo, 392, 50);
      
          Motor1(0,Mot1Dir);
          Motor2(200,Mot2Dir);
          
        } else {
         Motor1(0,Mot1Dir);
         Motor2(0,Mot2Dir);
         // read raw line sensor values
         qtrrc.read(sensorValues);
        
         //read ping sensor
         unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
      
         Serial.print("L: "); 
         Serial.print(sensorValues[0]);
         Serial.print("\tR: "); 
         Serial.print(sensorValues[1]);
         Serial.print("\tP: ");
         Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
         Serial.println("cm");
      
        
         noNewTone(Buzzer_Servo);
         //pretty rgb based upon the sensor valus
         h = ((float)sensorValues[0]+sensorValues[1])/4096;
         h2rgb(h,r,g,b);
         RGBLed(r, g, b);
         delay(uS/4);
         RGBLed(0, 0, 0);
         delay(100);
         
      
        } 
  }
}


void LineFollowMode () {
  float h;
  int r=0, g=0, b=0;
  Serial.println("Line Follow mode");
  //pretty led crossfade  
  while(1){
      for (int val = 0; val <1024; val+=10) {
          h = ((float)val)/1024;
      
          h2rgb(h,r,g,b);
          RGBLed(r, g, b);
          delay(10);
          
     }
  }
  
  
}

void Countdown1(){
  int i = 1;
  //count down 5 seconds
  while (i <= 5) {
    RGBLed(255, 0, 0);
    NewTone(Buzzer_Servo, 784, 50); 
    delay(450);
    RGBLed(0, 0, 0);
    delay(500);
    i++;
  }
}

void Countdown2(){
  int i = 1;
  //count down 5 seconds
  while (i <= 5) {
    RGBLed(0, 255, 0);
    NewTone(Buzzer_Servo, 392, 50); 
    delay(450);
    RGBLed(0, 0, 0);
    delay(500);
    i++;
  }
}


void SumoMode1() {
  int go = 0;
  unsigned int uS;
  
   Serial.println("Sumo Mode");
   while(1){
         //read line sensors
         qtrrc.read(sensorValues);
         //read ping sensor
         uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
           
          //both linesensors triggered, about face
          if (sensorValues[0] <LineThreshold && sensorValues[1] <LineThreshold ) {  
                RGBLed(255, 255, 0);       
                //stop the motors
                Motor1(0,Mot1Dir);
                Motor2(0,Mot2Dir);
		delay(20);
                //back up a little
                Motor1(Mot1Speed,!Mot1Dir);
                Motor2(Mot2Speed,!Mot2Dir);
		delay(400);
                Motor1(TurnSpeed,Mot1Dir);
                Motor2(TurnSpeed,!Mot2Dir);
		delay(TurnDelay);
	  }
	  
          //left sensor triggered, turn right
	  else if (sensorValues[0] <LineThreshold) {
                RGBLed(255, 0, 255);
                //stop the motors
                Motor1(0,Mot1Dir);
                Motor2(0,Mot2Dir);
		delay(20);
                //back up a little
                Motor1(Mot1Speed,!Mot1Dir);
                Motor2(Mot2Speed,!Mot2Dir);
		delay(100);
                Motor1(TurnSpeed,Mot1Dir);
                Motor2(TurnSpeed,!Mot2Dir);
		delay(TurnDelay);
	  }
	  
           //right sensor triggered, turn left
	   else if (sensorValues[1] <LineThreshold) {
                RGBLed(0, 255, 255);
                //stop the motors
                Motor1(0,Mot1Dir);
                Motor2(0,Mot2Dir);
		delay(20);
                //back up a little
                Motor1(Mot1Speed,!Mot1Dir);
                Motor2(Mot2Speed,!Mot2Dir);
		delay(100);
                Motor1(TurnSpeed,!Mot1Dir);
                Motor2(TurnSpeed,Mot2Dir);
		delay(TurnDelay);
	  }
	  else {
           
           if (uS > PingThreshold) {
             RGBLed(255, 0, 0);
             Motor1(Mot1Speed,Mot1Dir);
             Motor2(Mot2Speed,Mot2Dir);
           } else {
             RGBLed(0, 0, 255);
             Motor1(255,Mot1Dir);
             Motor2(255,Mot2Dir);
           }
          }
   }
}


void loop() {
int i;

  Serial.print (mode);
  if (mode == 1) {
    Serial.println(" Test Mode");
    TestMode();

  }
  else if (mode == 2) {
    Serial.println(" Line Follow Mode");
    LineFollowMode();
  }
  else {
    Serial.println(" Sumo Mode");
    
  //wait for button push
     button1 = digitalRead(SW_1);  // read input value
     button2 = digitalRead(SW_2);  // read input value
    
     if (button1 == HIGH && button2 == LOW) { 
       Countdown1();
       SumoMode1();
     }
     else if (button1 == LOW && button2 == HIGH) { 
       Countdown2();  
       SumoMode1();
     }
  }
  
}


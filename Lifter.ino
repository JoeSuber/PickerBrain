#include <AccelStepper.h>
#include <Servo.h>

byte PINST1_SLEEP = 5;
byte PINST1_ST = 7;
byte PINST1_DIR = 6;

byte REDLED = 10;
byte GREENLED = 9;

byte LIMIT_SW = 8;
byte SERV1 = 11;           // 'because he used those special parts to make his robot friends...'
byte CROW = 10;
byte ONRESERVE = 32;      // max byte length of serial-delivered string
boolean DEBUG = true;

byte PROX_PIN = A6;         // unused for now
byte SensorPins[] = {3,4};  // sensor pins unused for now
byte senseHolder = 0;       // global holder of sensor pin states

boolean SWITCHSTATE = HIGH;
String inputString = "";
AccelStepper stepper1(AccelStepper::DRIVER, PINST1_ST, PINST1_DIR);
Servo myserv;

// SLEEP A logic high allows normal operation, as well as start-up

void setup()
{  
    myserv.attach(SERV1); 
    
    stepper1.setMaxSpeed(3000.0);
    stepper1.setAcceleration(100.0);
    
    pinMode(PINST1_SLEEP, OUTPUT);
    //pinMode(PINST1_ST, OUTPUT); // handled in AccelStepper instance?
    //pinMode(PINST1_DIR, OUTPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    pinMode(LIMIT_SW, INPUT);
    digitalWrite(PINST1_SLEEP, SWITCHSTATE);              
    //digitalWrite(PINST1_ST, LOW);
    //digitalWrite(PINST1_DIR, LOW);                
    digitalWrite(REDLED, digitalRead(PINST1_SLEEP));  // glow when stopped for any reason                 
    digitalWrite(GREENLED, digitalRead(LIMIT_SW));  // glow when free. Needs to be in main loop
    
    Serial.begin(115200);
    inputString.reserve(ONRESERVE);
    Serial.println("Setup:  Limit Switch is " + String(digitalRead(LIMIT_SW)));
    stepper1.moveTo(500);
}

void loop() {
    digitalWrite(REDLED, digitalRead(PINST1_SLEEP));  // glow when stopped for any reason                 
    digitalWrite(GREENLED, digitalRead(LIMIT_SW));  // glow when free. Needs to be in main loop
    stepper1.run();
    if ((digitalRead(LIMIT_SW) == LOW) && SWITCHSTATE) {
      stepper1.moveTo(-stepper1.currentPosition() + 20);
      digitalWrite(PINST1_SLEEP, LOW);
      SWITCHSTATE = LOW;
      delay(10);
    }
    else {
      SWITCHSTATE = HIGH;
    }
}

// BrightBounce.pde
// incrementally adding required parts
// -*- mode: C++ -*-

#include <AccelStepper.h>


// outputs:
byte LED_GREEN = 8;
byte LED_RED = 9;
// inputs:
byte LIMITUP = 12;
// storage:
long int limit_hit = 0;

// driver for main, small one uses 4-wire interface
AccelStepper stepper(AccelStepper::DRIVER, 10, 11);
AccelStepper littlestep(AccelStepper::FULL4WIRE, 4, 7, 12, 13);

void setup()
{
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(1200);
  stepper.moveTo(4000);
  littlestep.setMaxSpeed(1000);
  littlestep.setAcceleration(1200);
  littlestep.moveTo(4000);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LIMITUP, INPUT);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  Serial.print("LIMITUP: " + String(digitalRead(LIMITUP)));
}

void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
      
    if (littlestep.distanceToGo() == 0)
      littlestep.moveTo(-stepper.currentPosition());
    
    // light up green when positive, red when negative, avoiding un
    if ((stepper.currentPosition() > 0) && !digitalRead(LED_GREEN)) {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED, LOW);
    }
    else if ((stepper.currentPosition() < 0) && digitalRead(LED_GREEN)) {
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, HIGH);
    }
    littlestep.run(); 
    stepper.run();
}

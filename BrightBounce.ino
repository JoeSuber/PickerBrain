// BrightBounce.pde
// -*- mode: C++ -*-


#include <AccelStepper.h>

int LED_GREEN 8;
int LED_RED 9;


// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, 10, 11); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{  

  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(300);
  stepper.setAcceleration(70);
  stepper.moveTo(500);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
}

void loop()
{
    // If at the end of travel go to the other end
    if (stepper.distanceToGo() == 0)
      stepper.moveTo(-stepper.currentPosition());
    
    // light up green when positive, red when negative, avoiding un
    if ((stepper.currentPosition() > 0) && !digitalRead(LED_GREEN)) {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED, LOW);
    }
    else if ((stepper.currentPosition() < 0) && digitalRead(LED_GREEN)) {
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, HIGH);
    }
      
    stepper.run();
}

#include "motors.h"
#include "traction.h"

#include <Arduino.h>

Traction::Traction(Motor &motorFrontLeft, Motor &motorFrontRight,
   Motor &motorBackLeft, Motor &motorBackRight, int minSpeed, int maxSpeed,
   int baseSpeed, int spinSpeed) :
 motorFrontLeft(motorFrontLeft), motorFrontRight(motorFrontRight),
 motorBackLeft(motorBackLeft), motorBackRight(motorBackRight), minSpeed(minSpeed),
 maxSpeed(maxSpeed), baseSpeed(baseSpeed), spinSpeed(spinSpeed) {}

void Traction::begin() {
   motorFrontLeft.begin();
   motorFrontRight.begin();
   motorBackLeft.begin();
   motorBackRight.begin();
}

void Traction::turnDirection(int direction, int baseSpeed) {
   int motorSpeed[2];

   motorSpeed[0] = baseSpeed + direction;
   motorSpeed[1] = baseSpeed - direction;

   for (uint8_t i = 0; i < 2; i++) {
      motorSpeed[i] = min(maxSpeed, motorSpeed[i]);
      motorSpeed[i] = max(-maxSpeed, motorSpeed[i]);

      motorSpeed[i] = motorSpeed[i] * (maxSpeed - minSpeed) / maxSpeed + 
         (motorSpeed[i] >= 0 ? minSpeed : -minSpeed);
   }

   motorFrontLeft.spin(motorSpeed[0]);
   motorFrontRight.spin(motorSpeed[1]);
   motorBackLeft.spin(motorSpeed[0]);
   motorBackRight.spin(motorSpeed[1]);
}

void Traction::forward(int speed) {
   motorFrontLeft.spin(abs(speed));
   motorFrontRight.spin(abs(speed));
   motorBackLeft.spin(abs(speed));
   motorBackRight.spin(abs(speed));
}

void Traction::backwards(int speed) {
   motorFrontLeft.spin(-abs(speed));
   motorFrontRight.spin(-abs(speed));
   motorBackLeft.spin(-abs(speed));
   motorBackRight.spin(-abs(speed));
}

void Traction::spin(int speed) {
   motorFrontLeft.spin(speed);
   motorFrontRight.spin(-speed);
   motorBackLeft.spin(speed);
   motorBackRight.spin(-speed);
}

void Traction::stop() {
   motorFrontLeft.stop();
   motorFrontRight.stop();
   motorBackLeft.stop();
   motorBackRight.stop();
}

void Traction::brake() {
   motorFrontLeft.brake();
   motorFrontRight.brake();
   motorBackLeft.brake();
   motorBackRight.brake();
}

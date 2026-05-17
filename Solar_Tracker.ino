#include <Servo.h>

Servo servoH;
Servo servoV;

int topLeft = A0;
int topRight = A1;
int bottomLeft = A2;
int bottomRight = A3;

int posH = 90;
int posV = 90;

int threshold = 70;
int stepSize = 3;

int readLDR(int pin) {
  long sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += analogRead(pin);
    delay(1);
  }
  return sum / 5;
}

void setup() {
  servoH.attach(9);
  servoV.attach(10);

  servoH.write(posH);
  servoV.write(posV);

  Serial.begin(9600);
  delay(1000);
}

void loop() {
  int tl = readLDR(topLeft);
  int tr = readLDR(topRight);
  int bl = readLDR(bottomLeft);
  int br = readLDR(bottomRight);

  int leftVal = (tl + bl) / 2;
  int rightVal = (tr + br) / 2;
  int topVal = (tl + tr) / 2;
  int bottomVal = (bl + br) / 2;

  // Horizontal reversed
  if (abs(leftVal - rightVal) > threshold) {
    if (leftVal > rightVal) posH += stepSize;
    else posH -= stepSize;

    posH = constrain(posH, 20, 160);
    servoH.write(posH);
  }

  // Vertical same
  if (abs(topVal - bottomVal) > threshold) {
    if (topVal > bottomVal) posV -= stepSize;
    else posV += stepSize;

    posV = constrain(posV, 20, 160);
    servoV.write(posV);
  }

  delay(20);
}
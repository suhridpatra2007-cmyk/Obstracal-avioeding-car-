
#include <Servo.h>

#define ENA 5
#define IN1 6
#define IN2 9
#define IN3 11
#define IN4 8
#define ENB 10

#define TRIG 4
#define ECHO 3

#define SERVO_PIN 13

Servo myServo;

long duration;
int distance;

void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90);

  Serial.begin(9600);
}

int getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) return 400;

  distance = duration * 0.034 / 2;

  return distance;
}

void forward() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRight() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {

  analogWrite(ENA, 150);
  analogWrite(ENB, 150);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void loop() {

  myServo.write(90);
  delay(300);

  int frontDistance = getDistance();

  Serial.println(frontDistance);

  if (frontDistance > 25) {

    forward();

  } else {

    stopCar();
    delay(300);

    backward();
    delay(400);

    stopCar();
    delay(300);

    myServo.write(30);
    delay(500);

    int rightDistance = getDistance();

    myServo.write(150);
    delay(500);

    int leftDistance = getDistance();

    myServo.write(90);
    delay(300);

    if (rightDistance > leftDistance) {

      turnRight();
      delay(500);

    } else {

      turnLeft();
      delay(500);

    }

    stopCar();
  }
}

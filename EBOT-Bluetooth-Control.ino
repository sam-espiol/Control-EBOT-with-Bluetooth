#include "BluetoothSerial.h"
#include <Arduino.h>

#include <ESP32Servo.h>

BluetoothSerial serialBT;

//Bluetooth signal Store in this variable
char btSignal;

//initial Speed of the Bot
int Speed = 10;
Servo myservo, myservo2;  
int pos = 0; 

//Define in1/in2/in3/in4 pin
int IN1 = 4;
int IN2 = 16;
int IN3 = 5;
int IN4 = 18;

void setup() {
  Serial.begin(115200);

  //Bluetooth Name
  serialBT.begin("CUBIT");
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);  
	myservo.attach(25, 500, 2400);
  myservo2.setPeriodHertz(50);  
	myservo2.attach(26, 500, 2400);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(IN1, 0);
  analogWrite(IN2, 0);

  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void loop() {

  while (serialBT.available()) {
    btSignal = serialBT.read();
    //Serial.println(btSignal);

    if (btSignal == '1') Speed = 25.5;
    if (btSignal == '2') Speed = 51;
    if (btSignal == '3') Speed = 76.5;
    if (btSignal == '4') Speed = 102;
    if (btSignal == '5') Speed = 127.5;
    if (btSignal == '6') Speed = 153;
    if (btSignal == '7') Speed = 178.5;
    if (btSignal == '8') Speed = 204;
    if (btSignal == '9') Speed = 229.5;
    if (btSignal == 'q') Speed = 255;
    if (btSignal == '0') Speed = 0;

    if (btSignal == 'B')  //forward
    {

      analogWrite(IN1, Speed);
      analogWrite(IN2, 0);

      analogWrite(IN3, Speed);
      analogWrite(IN4, 0);

    }

    else if (btSignal == 'F')
    {

      analogWrite(IN1, 0);
      analogWrite(IN2, Speed);

      analogWrite(IN3, 0);
      analogWrite(IN4, Speed);

    }

    else if (btSignal == 'R')  //LEFT
    {

      analogWrite(IN1, 0);
      analogWrite(IN2, 0);

      analogWrite(IN3, 0);
      analogWrite(IN4, Speed);
    }

    else if (btSignal == 'L')  //RIGHT
    {

      analogWrite(IN1, 0);
      analogWrite(IN2, Speed);

      analogWrite(IN3, 0);
      analogWrite(IN4, 0);
    }
    else if(btSignal == 'X'){
      myservo.write(60);
    }
    else if(btSignal == 'x'){
      myservo.write(120);
    }
    else if(btSignal == 'G'){
      moveForwardLeft();
    }
    else if(btSignal == 'I'){
      moveForwardRight();
    }
    else if(btSignal == 'H'){
      moveBackLeft();
    }
    else if(btSignal == 'J'){
      moveBackRight();
    }
    else if(btSignal == 'S'){
      stop();
    }
  }
}
void moveForwardLeft() {
  // Left motor (reduced speed for turning left)
  analogWrite(IN3, 0);
  analogWrite(IN4, Speed/2);

  // Right motor (full speed forward)
  analogWrite(IN1, 0);
  analogWrite(IN2, Speed);
}
void moveForwardRight(){
  analogWrite(IN1, 0);
  analogWrite(IN2, Speed/2);
  analogWrite(IN3, 0);
  analogWrite(IN4, Speed);
}
void moveBackLeft(){
  analogWrite(IN1, Speed);
  analogWrite(IN2,0);
  analogWrite(IN3, Speed/2);
  analogWrite(IN4, 0);
}
void moveBackRight(){
  analogWrite(IN1, Speed/2);
  analogWrite(IN2,0);
  analogWrite(IN3, Speed);
  analogWrite(IN4, 0);
}
void stop(){
    // Left motor (reduced speed for turning left)
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
  // Right motor (full speed forward)
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}
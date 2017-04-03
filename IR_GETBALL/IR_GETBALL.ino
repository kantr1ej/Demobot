/*
SETUP:
  arduino pins
    radio control (5,10)
    motor controller (0)
    navigation IR (A0)
    claw IR (A1)

*/


#include <Sabertooth.h>
#include <Servo.h>

Servo claw;
Sabertooth ST(128);

int counter = 0;
int pos = 60;
int ch6;
int rcClaw;
int horizontal; //ch1 pin 5
int vertical; //ch2 pin 10
int mappedVal;            //horiz
int mappedVal2;           //vert
//IR



void rcClawClose(Servo claw){
    claw.write(92+8);
    delay(800);
    claw.write(92);
}

void clawClose(Servo claw){
    claw.write(92+8);
    delay(400);
    noDrive(ST);
    claw.write(92+8);
    delay(400);
//    delay(800);
    claw.write(92);
    delay(2500);
}

void rcClawOpen(Servo claw){
    claw.write(92-6);
    delay(700);
    claw.write(92);
}

void clawOpen(Servo claw){
    claw.write(92-6);
    delay(800);
    claw.write(92);
    delay(3000);
}

void circle(Sabertooth ST){
  ST.motor(1, 70);
  ST.motor(2, -10);
}

void forward(Sabertooth ST){
  ST.motor(1, 57);
  ST.motor(2, 50);
}

void left(Sabertooth ST){
  ST.motor(1, 50);
  ST.motor(2, -50);
}

void right(Sabertooth ST){
  ST.motor(1, -50);
  ST.motor(2, 50);
}

void backwards(Sabertooth ST){
  ST.motor(1, -50);
  ST.motor(2, -50);
}

void noDrive(Sabertooth ST){
  ST.motor(1, 0);
  ST.motor(2, 0);
}

void setup() {

  claw.attach(3);
  pinMode(5, INPUT);                                                                                   //inputs for remote control
  pinMode(10, INPUT);
  pinMode(6, INPUT);
  
  Serial.begin(9600);
  SabertoothTXPinSerial.begin(9600);
 
}

void loop() {


  int navIR = analogRead(A0);
  int clawIR = analogRead(A1);
  
  horizontal = pulseIn(10, HIGH, 25000);                                                                 //channel 2 for horizontal
  vertical = pulseIn(5, HIGH, 25000);                                                                  //channel 1 for vertical stick
  rcClaw = pulseIn(6, HIGH, 25000);                                                                        //must be plugged in for everything to work, for some reason 
  

mappedVal = map(horizontal ,1100,1900,-127,127);
mappedVal2 = map(vertical,1100,1900,-127,127);
//Serial.print("vertical\n");
//Serial.println(mappedVal);
//Serial.print("horizontal\n");
//Serial.println(mappedVal2);
Serial.print("clawIR");
Serial.println(navIR);

//Serial.println(rcClaw);

if(mappedVal < -300){
    
  if ((navIR < 150 && clawIR < 400) && mappedVal < -300){
     
     forward(ST);
     delay(1000);
     counter += 1;
  }
 
    if (navIR > 150 && mappedVal < -300){
      noDrive(ST);
      delay(500);
      right(ST);
      delay(2000);
    }
  

  if (clawIR > 180 && mappedVal < -300){
//    noDrive(ST);
    clawClose(claw);
//    noDrive(ST);
    delay(800);

    right(ST);
    delay(7400);
    forward(ST);
    delay(1000 * counter);
    noDrive(ST);
    counter = 0;

    clawOpen(claw);
    
    delay(1000);
    right(ST);
    delay(8000);
    noDrive(ST);
    delay(10000);
  }
}

  else{
    if (mappedVal2 > 25){
      right(ST);
    }
    if (mappedVal2 < -25){
      left(ST);
    }
    if (mappedVal < -25){
      forward(ST);
    }
    if (mappedVal > 25){
      backwards(ST);
    }
    if (mappedVal < 20 && mappedVal > -20 && mappedVal2 < 20 && mappedVal2 > -20){
      noDrive(ST);
    }
    if (rcClaw < 1000 && rcClaw > 0){
      rcClawClose(claw);
    }

    if (rcClaw > 2000 && rcClaw > 0){
      rcClawOpen(claw);
    }
      
  }
}



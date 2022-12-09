#include<Servo.h>

int red = 11;
int yellow = 12;
int green = 10;

Servo servo1;
Servo servo2;



int in1 = 3;
int in2 = 2;
int in3 = 8;
int in4 = 7;

int userInput;
int buttonPin = A1;
int buttonPin2 = A0;

int buttonPushCounter = 1;
int buttonState = 0;
int lastButtonState = 0;

int buttonState2 = 0;
int lastButtonState2 = 0;

int buttonValue = 0;
int buttonValue2 = 0;


void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(A1, INPUT);



  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  servo1.attach(5);
  servo1.write(90);
  servo2.attach(6);
  servo2.write(180);

  Serial.begin(9600);

}


void loop() {
  buttonValue = analogRead(A0);
  Serial.println(buttonValue);
  delay(75);

  //for powerlevelbutton
  if (buttonValue >= 300 && buttonValue <= 400) {
    buttonPushCounter++;
    if (buttonPushCounter == 4) {
      buttonPushCounter = 0;
      ledOFF(3);
    }
    ledON(buttonPushCounter);
    Serial.println(buttonPushCounter);
  }
  else if (buttonValue >= 450 && buttonValue <= 550) {
    digitalWrite(in4, HIGH);   //in4  +  in1
    digitalWrite(in3, LOW);    //in3  +  in2
  }

  //for cast button
  else if (buttonValue >= 600 && buttonValue <= 700) {
    //do whatever like the cast button is pressed
    if (buttonPushCounter == 1) {
      ledON(1);
      casting(1800);
      pressButton();
      delay(1000);
      launch();
    }
    else if (buttonPushCounter == 2) {
      ledON(2);
      casting(1800);
      pressButton();
      delay(1000);
      launch();
    }
    else if (buttonPushCounter == 3) {
      ledON(3);
      casting(1800);
      pressButton();
      delay(1000);
      launch();

    }
    else {
      //error message with LEDs
      for (int i = 0; i < 2; i++) {
        digitalWrite(red, HIGH);
        delay(100);
        digitalWrite(yellow, HIGH);
        delay(100);
        digitalWrite(green, HIGH);
        delay(100);
        digitalWrite(red, LOW);
        delay(100);
        digitalWrite(yellow, LOW);
        delay(100);
        digitalWrite(green, LOW);
        delay(100);
      }
    }
    delay(200);
    resetLatch();
  }
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
  delay(30); //to prevent bouncing
}

void casting(int castTime) {


  //this will change slightly depending on which way the motor spins when in1 is open vs when in2 is open

  //initially pull rod in
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(castTime);
  //pause when rod is pulled back to preffered distance
  digitalWrite(in1, LOW);
  delay(1000);
  //since rod is held by the latch, motor turns other way to let out slack
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  delay(castTime-350);
  //rod is now primed for cast, motor turns off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

}

void pressButton() {
  servo1.write(0);
}
void resetLatch() {
  servo2.write(180);
  servo1.write(90);
}
void launch() {
  servo2.write(150);
  delay(1000);
  for (double i = 0; i < 100; i++) {
    int num = 90;        //CASTING SETTINGS!!!!!  Delay # is 87, reel until the lure is in line or just above the second to last loop on rod
    if(i>num){  
    servo1.write((i-num)/2);
    }
    servo2.write(140-(2*i/5));  
    delay(2);

  }
}

void powerAdjust() {
  if (buttonState == HIGH);

}

void ledON(int x) {
  if (x == 1) {
    digitalWrite(red, HIGH);
    delay(100);
  }
  else if (x == 2) {
    digitalWrite(red, HIGH);
    delay(100);
    digitalWrite(yellow, HIGH);
    delay(100);
  }
  else if (x == 3) {
    digitalWrite(red, HIGH);
    delay(100);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(green, HIGH);
    delay(100);
  }
}
void ledOFF(int x) {
  if (x == 1) {
    digitalWrite(red, LOW);
    delay(100);
  }
  else if (x == 2) {
    digitalWrite(red, LOW);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
  }
  else if (x == 3) {
    digitalWrite(red, LOW);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
    digitalWrite(green, LOW);
    delay(100);
  }
}


//in1 HIGH in2 LOW = clockwise
//in1 LOW in2 HIGH = counterclockwise

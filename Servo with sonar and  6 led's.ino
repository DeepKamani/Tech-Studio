Final-Final-Final-Final-Final-Final

//define pin numbers
#include <Servo.h>

const int trigPin = 10;
const int echoPin = 9;
int led1 = 6;
int led2 = 7;
int timer =20;



//define variables
long duration;
int distance;

Servo jawservo;
int pos = 0;

void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin,INPUT);
Serial.begin(9600); // Starts the serial communication
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
for (int thisPin = 2; thisPin < 5; thisPin++) {
 pinMode(thisPin, OUTPUT);
}
jawservo.attach(11);
}

void loop() {
//Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

//Set the trigPin on HIGH state for 10 micro-seconds.
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

//Reads the echoPin, returns the soundwave travel time.
duration = pulseIn(echoPin, HIGH);

//calculate distance
distance = (duration/2)/29.1;

if(distance <=50){     // if ultrasonic sensor detects an obstacle less than 20cm in 90 degree angle.
  jawservo.write(0);    //servo rotates at full speed to the right
  digitalWrite(led1, HIGH);
digitalWrite(led2, HIGH);
 for (int thisPin = 2; thisPin < 5; thisPin++) {
 // turn the pin on:
 digitalWrite(thisPin, HIGH);
 delay(timer);
 // turn the pin off:
 digitalWrite(thisPin, LOW);

}



// loop from the highest pin to the lowest:
for (int thisPin = 5; thisPin >= 2; thisPin--) {
 // turn the pin on:
 digitalWrite(thisPin, HIGH);
 delay(timer);
 // turn the pin off:
 digitalWrite(thisPin, LOW);
 delay(600);
}


}else{
 digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
  jawservo.write(90);   // else servo stays at 90 degree angle.
  delay(600);
}
};

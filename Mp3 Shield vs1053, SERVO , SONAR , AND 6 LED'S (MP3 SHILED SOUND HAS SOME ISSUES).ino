#include <SPI.h>


	Libraries
	#include <SdFat.h>
	#include <SdFatUtil.h>


	//and the MP3 Shield Library
	#include <SFEMP3Shield.h>


	//create and name the library object
	SFEMP3Shield MP3player;
	SdFat sd;
	SdFile file;


	// Define variables that we might use but in this specific example are not needed.
	// See https://github.com/mpflaga/Sparkfun-MP3-Player-Shield-Arduino-Library


	byte temp;
	byte result;


	/* END OF MP3 Shield configuration MP3TF */


	#include <Servo.h>


	#include <NewPing.h>

	#define TRIGGER_PIN  4
	#define ECHO_PIN     3
	#define MAX_DISTANCE 200




	#define switchpin A5


	// Create servo Motor object
	Servo myservo;


	NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


	// Define random variable to determine if an individual has the force
	long randNumber;

	void setup() {
	  Serial.begin(115200);
	  pinMode(switchpin, OUTPUT);
	  myservo.attach(A4);


	  // if analog input pin 0 is unconnected, random analog
	  // noise will cause the call to randomSeed() to generate
	  // different seed numbers each time the sketch runs.
	  // randomSeed() will then shuffle the random function.
	  randomSeed(analogRead(0));


	  //mp3 shield powering in varibles initializing


	  sd.begin(SD_SEL, SPI_HALF_SPEED);

	  //boot up the MP3 Player Shield
	  result = MP3player.begin();

	 MP3player.setVolume(10, 10);


	}

	void loop() {
	  delay(2000);
	  int uS = sonar.ping();
	  long distance,pos=0,i;
	  Serial.print("Ping: ");

	  distance =uS / US_ROUNDTRIP_CM;
	  Serial.print(distance);
	  Serial.println("cm");


	  Serial.println("Hello");
	  Serial.println("Preparing to play a song");


	  // print a random number from 0 to 99
	  randNumber = random(100);
	  Serial.println(randNumber);



	//
	   Serial.print(distance);
	   Serial.println(" cm");




	  //the person has to be within the sensors range and closer than 120cm and farther than 95cm to the installation


	    if(distance > 95 && distance<=120){



	       //It is assumed that only 20% has the force


	      if (randNumber>80) {
	        Serial.println("The force be with you.");

	        //add track for person with the force
	        char trackName[] = "track001.mp3";


	        //tell the MP3 Shield to play that file
	        result = MP3player.playMP3(trackName);

	        //check result, see readme for error codes.
	        if(result != 0) {
	          Serial.print("Error code: ");
	          Serial.print(result);
	          Serial.println(" when trying to play track");
	        }

	        //darth vader turns to look at you if you have the force
	        digitalWrite(switchpin,HIGH);
	        myservo.write(180);


	        // wait 15 seconds
	        delay(15000);


	        myservo.write(0);

	        digitalWrite(switchpin,LOW);


	      }
	      else {


	        Serial.println("I find your lack of faith disturbing.");

	        // add track to person without the force
	        char trackName[] = "track002.mp3";
	        result = MP3player.playMP3(trackName);


	//        // interaction with person without the force should last 10 sec
	          delay(10000);
	//
	      }
	    }else{
	        Serial.println("Out of range");
	        delay(3000);
	    }
	}

#include <OneWire.h>
#include <Time.h>


/*
 * THis Sketch contains a motion sensitive thermostat.
 */
 #define relayPin 2
 #define relayLED 3
 #define motionPin 14
 #define motionLED 13
 #define instaHeatSw 8
 #define highSetTemp 69            //lool 69
 #define lowSetTemp 55
 #define tempHyst 3 
 #define timeoutSec 1800
 #define heatReqPin 4
 
 int lastMotionTime = 0;
 int cycleStartTime = 0;
 int presense = FALSE;
 
 void setup(void){
   Serial.begin(9600);
 }
 
 
 void loop(void){
   cycleStartTime = now();
   //Check to see if there are people to heat
   if(digitalRead(motionPin)){
     lastMotionTime = cycleStartTime;
     presense = TRUE; 
    //Heat timeout
   }else if(cycleStartTime >= lastMotionTime + timeoutSec){
     presense = FALSE;
   }
   
   // Read temp from sensor here
   int curTemp = 0;
   //Run Heater
   if(presense & heatReqPin){
     if(curTemp < highSetTemp - tempHyst){
       //Turn on the heater
       digitalWrite(relayPin, HIGH);
       digitalWrite(relayLED, HIGH);
     }else if(curTemp >= highSetTemp){
       //Turn off the heater
       digitalWrite(relayPin, LOW);
       digitalWrite(relayLED, LOW);
     }
   }else{
     if(curTemp < lowSetTemp - tempHyst){
       //Turn on the heater
       digitalWrite(relayPin, HIGH);
       digitalWrite(relayLED, HIGH);
     }else if(curTemp >= lowSetTemp){
       //Turn off the heater
       digitalWrite(relayPin, LOW);
       digitalWrite(relayLED, LOW);
     }
   }

   //Delay so that we don't flutter the heater on and off
   delay(60);
 }

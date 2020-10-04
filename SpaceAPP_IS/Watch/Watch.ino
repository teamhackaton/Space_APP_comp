
//This code is to use with DS1302 RTC module, it permits you to setup the actual time and date
//And you can visualize them on the serial monitor
//This code is a modified version of the code provided in virtuabotixRTC library




#include <virtuabotixRTC.h> //Library used

#define vibrator_PIN    5

const int WAITTIME = 50;
const int STEP = 5;

const int hour_alarm = 1;
const int minute_alarm = 30;



virtuabotixRTC myRTC(6, 7, 8); //Wiring

void setup() {
 Serial.begin(9600);

 // seconds, minutes, hours, day of the week, day of the month, month, year
 //myRTC.setDS1302Time(00, 29, 1, 7, 4, 10, 2020);
 //Remember to comment this function once you're done
 //The setup is done only one time and the module will continue counting it automatically
}

void loop() {
 // This allows for the update of variables for time or accessing the individual elements.
 myRTC.updateTime();

// Start printing elements as individuals
 Serial.print("Current Date / Time: ");
 Serial.print(myRTC.dayofmonth);
 Serial.print("/");
 Serial.print(myRTC.month);
 Serial.print("/");
 Serial.print(myRTC.year);
 Serial.print(" ");
 Serial.print(myRTC.hours);
 Serial.print(":");
 Serial.print(myRTC.minutes);
 Serial.print(":");
 Serial.println(myRTC.seconds);

 if(myRTC.hours == hour_alarm && myRTC.minutes== minute_alarm){
    int i;

    i = 0;
    while ( i <= 255 ){
        analogWrite( vibrator_PIN, i);
        delay( WAITTIME );
        i = i + STEP;
    }

    i = 255;
    while ( i >= 0 ){
        analogWrite( vibrator_PIN, i );
        delay( WAITTIME );
        i = i - STEP;
    }
  }

// Delay so the program doesn't print non-stop
 delay(1000);
}

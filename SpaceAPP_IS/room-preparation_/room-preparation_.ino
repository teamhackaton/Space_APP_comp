
//This code is to use with DS1302 RTC module, it permits you to setup the actual time and date
//And you can visualize them on the serial monitor
//This code is a modified version of the code provided in virtuabotixRTC library




#include <virtuabotixRTC.h> //Library used

#define TemperatureRegulator_PIN    5
#define Brightness_PIN              6

//depending on the schedule provided and could be modified from the admin interface
const int hour_sleep_pre10min = 00;
const int minute_sleep_pre10min = 00;
const int hour_wake_post10min = 00;
const int minute_wake_post10min = 00;

int flag=0;



virtuabotixRTC myRTC(6, 7, 8); //If you change the wiring change the pins here also

void setup() {
 Serial.begin(9600);

// Set the current date, and time in the following format:
 // seconds, minutes, hours, day of the week, day of the month, month, year
 //myRTC.setDS1302Time(00, 10, 23, 6, 3, 10, 2020); //Here you write your actual time/date as shown above 
 //but remember to "comment/remove" this function once you're done
 //The setup is done only one time and the module will continue counting it automatically
}

void loop() {
 // This allows for the update of variables for time or accessing the individual elements.
 myRTC.updateTime();

// Start printing elements as individuals
 Serial.print("Current Date / Time: ");
 Serial.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
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

 if(flag==0 && myRTC.hours == hour_sleep_pre10min && myRTC.minutes== minute_sleep_pre10min){
    int i,j;
    
    i=255;//to start the temperature regulation program
    j=180;//correct brightness
    
    //analogWrite( TemperatureRegulator_PIN, i);
    analogWrite( Brightness_PIN, j);
    flag=1;
    // Delay so the program doesn't print non-stop
    delay(1000);
 }
 else if(flag ==1 && myRTC.hours == hour_wake_post10min && myRTC.minutes== minute_wake_post10min){
    int i,j;
    
    i=0;//to end the temperature regulation program
    j=0;//shut brightness
    
    //analogWrite( TemperatureRegulator_PIN, i);
    analogWrite( Brightness_PIN, j);
    
    // Delay so the program doesn't print non-stop
    delay(1000);
  }

  if(flag==1){
    
    
  }
}

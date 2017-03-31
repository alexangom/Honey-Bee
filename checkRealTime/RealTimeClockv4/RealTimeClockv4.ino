// Libraries needed for real time clock
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

// Initiators for time clock
tmElements_t tm;
String realTime;
String realDate; 

// --  Real time function -----------
// This function is used to check real time clock store in the DS1307 shield. The function has int input value. If the input is 0 the function will return time, if the input is 1 the function will return date.
String checkRealTime (int timeOrDate) { 
  if (RTC.read(tm)) // check if data can be read from the DS1307
  {
    int hours = tm.Hour; // read hours and store in a variable
    int minutes = tm.Minute;
    int sec = tm.Second;
    realTime = String(hours) + ":" + String(minutes) + ":" + String(sec); // combines the times hr:min:sec
    int Day = tm.Day;
    int Month = tm.Month;
    int Year = tmYearToCalendar(tm.Year);
    realDate = String(Day) + "/" + String(Month) + "/" + String(Year); // combines date into day/month/year
  } else { // if data cannot be read
    if (RTC.chipPresent()) // check if the chip circuit is present
    { // if it is present will retunr error 101
      realTime = "ERROR 101"; 
      realDate = "ERROR 101";
    } else { // if the circuit is not present will return error 102
      realTime = "ERROR 102";
      realDate = "ERROR 102";
    }
  }
  if(timeOrDate == 0){ // if timeOrDate = 0, the function will return time
    return realTime;
  } 
  else if (timeOrDate == 1) { // if timeOrDate = 1, the function will return date
    return realDate;
  }
}

//------ testing ----------------
String checkDate;
String checkTime;

void setup() {
  Serial.begin(9600); // For debugging purposes
  while(!Serial);
}

void loop() {
  checkTime = checkRealTime(0); // reads time from DS1307
  checkDate = checkRealTime(1); // reads date from DS1307
  
  Serial.print("Time = ");
  Serial.print(checkTime);
  Serial.print(" Date = ");
  Serial.print(checkDate);
  Serial.println();
  delay(1000);
}

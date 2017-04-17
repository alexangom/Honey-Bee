void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
   printVolts();
   delay(5000);

}

 
 int printVolts()
{
 
 battery_check:
  int battery_level=0;
  int battery = analogRead(A0); //read the A0 pin value
  double voltage = battery * 0.00488758553; //convert the value to a true voltage (5/1023).
  double battery_percent = (voltage/3.7) *100;

  Serial.println(voltage,9);
  Serial.println(battery_percent,9);

  if (battery_percent <= 78) // 2.8V is the discharge minimum for 3.7V/1000mAH battery; set limit to 2.9V to be safe
  {
    Serial.println("Low Battery");
  
    //goto main;
    // in main we will need impliment code to save all of the data and shut down so files/data does not get corrupted
    battery_level=1;
  }
  else {
    int counter;
      while (counter<200) // creates a timer/counter and will go back to the battery check routine
      counter++;
      battery_level=0;
  }

    return battery_level;
    goto battery_check;
  }


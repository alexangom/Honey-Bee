/*void setup() {
  // put your setup code here, to run once:

}

//void loop() {
   put your main code here, to run repeatedly:
   */
// Checks the temperature. Had to do some heavy duty arithmetic here - it's based on the datasheet
// supplied by Amphenol, the manufacturer of the thermistor. 

int checkTemp() {
    globalTempFileName = "globalTemp" + String(globalTempFileTracker) + ".txt"; // Create file SD card
    flag = globalTempFile.open(globalTempFileName, O_RDWR | O_CREAT | O_AT_END); // Open file
    
    if (flag == 0) { 
        Serial.println("CHECKTEMP(): " + globalTempFileName + " O_RDWR | O_CREAT | O_AT_END failed.");
    }
    
    if (flag == 1) { 
        Serial.println("CHECKTEMP(): " + globalTempFileName + " opened successfully.");
    }

    int invalid = 0; //used to check temperature reading
    long time;
    int stringcheck;
    int temperature;
    int thermistorResistance;
    int R1=10000;
    
 analog_temp: 
    thermistorAnalog = analogRead(A5); // read the raw thermistor analog data
    time= millis();
    //timestamp = analogRead(A6); // RAJA: input to bring in time & date stamp; if we are using arduino look below
     // convert resistance to ohms using voltage divider equation, where R1 = 10k ohms
     // shielded equation from divide by 0 by putting it inside an if statement
    if (thermistorAnalog < 4095) { 
        thermistorResistance = R1*(1-thermistorAnalog/4095)*(4095/thermistorAnalog);
         // calculated temperature by plotting a line of best fit using linear algebra and MATLAB. Error was found to be 3.7998*10^-4 Kelvins using Igor Pro. Compressed some of the math operations to reduce floating point error propagation, which increases as number of operations increase
       temperature = pow((.0011106 + 0.00023724*log(thermistorResistance) + 0.000000074738*pow(log(thermistorResistance), 3)), -1) - 273.15;
    }
    
    else if (thermistorAnalog >= 4095) {
        // if A5 reads 4095, then there is a short and/or the thermistor has failed
        thermistorResistance = 0;
        temperature = 0;
        
        //globalTempFile.write(String(time) + " " + "Temperature = Invalid "+ "ThermistorResistance = (0) Thermistor_Fail" + ";\n"); //writes to SD card
        //goto check_file; //skips temperature calclations and goes to check_file loop
    }
    
   
   
   //checks temp reading. if temperature is < 36 or > 38 it will go back to analog temp loop to get new data otherwise it will continue down the code

   /* if (temperature < 36 || > 38) {
       invalid++;
       if (invalid==5) {
           globalTempFile.write(String(time) + " " + "Temperature = Out_of_Range " + ";\n"); //writes to SD card
           goto check_file;
        } else {
          goto analog_temp;
        }
    } else if (temperature >= 36 || <= 38) {
      invalid = 0;
      Serial.print("temp: "); // for debugging
      Serial.println(time + temperature); //may not need this and can instead write directly to file
    }
    
    
    RAJA: if we are doing it straight on arduino we could use the t=millis() fucntion. will reset after appx. 49 days vs the miroc() fucn whic resets after 70min 
           //Arduino time stamp
              // time= millis(); //use this instead of 
              // Serial.println(temperature + time);
    //RAJA: 
    //in particle i/o "Time.timestr()" func. will write DD MM hh:mm:ss YYYY format. we can imrove accuracy (will also need to connect & may increase power consump by adding allowing to sync with Particle Cloud using:
     
            //ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
        //unsigned long lastSync = millis();

          //void loop() {
            if (millis() - lastSync > ONE_DAY_MILLIS) {
                   Request time synchronization from the Particle Cloud
              Particle.syncTime();
              lastSync = millis();
          }
      }
 */
    globalTempFile.write(String(time) + " " + String(temperature) + "; "); // write sD card; 
    globalTempFile.write("thermistor Resistance: " + String(thermistorResistance) + ";\n");  
 
 check_file:  
    // if the file size exceeds 1MB, on to the next one
    if (globalTempFile.fileSize() > 1000000) { 
        globalTempFileTracker++;
    }
    
    flag = globalTempFile.close(); // this function closes the file as well as returns a bool regarding whether the file closed successfully or not. next few lines are for debugging purposes only
    if (flag == 0) {
        Serial.println("CHECKTEMP(): " + globalTempFileName + " failed to close.");
    }
    
    if (flag == 1) { 
        Serial.println("CHECKTEMP(): " + globalTempFileName + " closed successfully.");
    }
}

return checktemp
}

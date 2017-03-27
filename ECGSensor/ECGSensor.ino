// this is a test
String EKGData;
int stringCheck;
String pseudoFile;
void checkEKG() {
    //globalEKGFileName = "globalEKG" + String(globalEKGFileTracker) + ".txt"; // SD creating file
   //globalEKGFile.open(globalEKGFileName, O_RDWR | O_CREAT | O_AT_END); // Openns the file
  //EKG = analogRead(A4); Reads EKG Data from the Arduino or Particle Photon
  for(int i = 0; i < 100; i++)//Test that will generate random numbers(simulation of numbers received from EKG without actually connecting a device)
  {
    EKG = int(random(0,100));
  }
    EKGData += String(EKG);
    
    // maximum String length is 622 bytes. Let's just be safe and say 616. 
    if (EKGData.length() <= 616) { 
        stringCheck = 0;
         EKGData += "\n"; // go to the next line
    }
    else
    {
      stringCheck = 1;
    }
    
    // Large files are hard to read. Also, opening and writing to large files takes a while. I'm partitioning the files with the next control structure. 
   // if (globalEKGFile.fileSize() > 1000000) // if the EKG file exceeds 1MB, on to the next on on to the next one
   // {
   //     globalEKGFileTracker++;   
   // }
    
    // once again, no error messages because I'll flood the serial monitor. Maybe implement a flashing LED? 
   // globalEKGFile.close(); // close
}

void loop()
{
  if(stringCheck == 1)//Checks to see if EKGData has surpassed 616 bytes
  {
    EKGData += " " + Time.timeStr();//Writes the time next to the data to record Timestamp of completion(Time is a class already defined in Arduino/Particle?)
    //globalEKGFile.write(EKGData); // write the buffer to the card
    pseudoFile = EKG;//Pseudo File write since in this case not actually using a file to write to.
    EKGData = "";//Clears the variable
  }
  while(stringCheck == 0)
  {
    this.checkEKG;
  }
 
}

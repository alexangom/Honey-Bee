long tACC;
void checkACC
{
    //globalAccelFileName = "globalAccel" + String(globalAccelFileTracker) + ".txt";
    //globalAccelFile.open(globalAccelFileName, O_RDWR | O_CREAT | O_AT_END);
    
    int x = analogRead(A0);//3D movement
    int y = analogRead(A1);
    int z = analogRead(A2);
    
    tACC = micros();
    
    //double accelMagnitude = floor(sqrt(pow(analogRead(A0),2) + pow(analogRead(A1),2) + pow(analogRead(A2),2)) + 0.5); 
    //accelData += String(accelMagnitude).remove(4); 
    
    // maximum String length is 622 bytes. Let's just be safe and say 616 so we don't overrun. 
    if (accelData.length() > 616) {
        accelData += " " + Time.timeStr(); 
        //globalAccelFile.write(accelData);
        accelData = "";
    }
    
    if (accelData.length() <= 616) { 
        accelData += " X-Dimension: " + String(x) + " Y-Dimension: " + String(y) + " Z-Dimension: " + String(z) +  " " + tAcc "\n"; // each data point is on its own line
    }
    
   // if (globalAccelFile.fileSize() > 1000000) // if the accel file exceeds 1MB, on to the next one
    //{
     //   globalAccelFileTracker++;
    //}
    
    //globalAccelFile.close(); // don't forget to close the file, otherwise you run the risk of corrupting the file and card. 
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}


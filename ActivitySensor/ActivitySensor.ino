int x;
int y;
int z;
int xVolt;
int yVolt;
int zVolt;
long tACC;
int stringCheck = 0;
int eraseAccel = 0;
String accelData;
int checkACC
{
    //globalAccelFileName = "globalAccel" + String(globalAccelFileTracker) + ".txt";
    //globalAccelFile.open(globalAccelFileName, O_RDWR | O_CREAT | O_AT_END);
    
     x = analogRead(A0);//3D movement
     y = analogRead(A1);
     z = analogRead(A2);
    tACC = micros();
     xVolt = x * 0.000805664;
     yVolt = y * 0.000805664;
     zVolt = z * 0.000805664;
    
    //accelData += "X-Dimension: " + String(xVolt) + " Y-Dimension: " + String(yVolt) + " Z-Dimension: " + String(zVolt) +  " " + tAcc;
    //double accelMagnitude = floor(sqrt(pow(analogRead(A0),2) + pow(analogRead(A1),2) + pow(analogRead(A2),2)) + 0.5); 
    //accelData += String(accelMagnitude).remove(4); 
    
    if(stringCheck == 0)
    {
        accelData += "X-Dimension: " + String(xVolt) + " Y-Dimension: " + String(yVolt) + " Z-Dimension: " + String(zVolt) +  " " + tAcc "\n"; // each data point is on its own line
    }
    else if(stringCheck == 1)
    {
        eraseAccel = 1;
    }
    if(eraseAccel == 1)
    {
        accelData = "";
        eraseAccel = 0;
        stringCheck = 0;
    }
    
    // maximum String length is 622 bytes. Let's just be safe and say 616 so we don't overrun. 
    if (accelData.length() > 308) {
        stringCheck = 1;
    }
    
    if (accelData.length() <= 308) { 
        stringCheck = 0;
    }
    return stringCheck;
    
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


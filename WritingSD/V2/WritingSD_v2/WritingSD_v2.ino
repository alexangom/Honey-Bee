// ----------- Libraries ---------------------------------------------------------
#include <SdFat.h> // This is the Sd library
#include <EEPROM.h> // This library is used to store data in EEPROM

// See SPI configuration section below (comments are for photon).
#define SPI_CONFIGURATION  0
// ******************** I thing Aswhin used configuration 1. Need to confirm this *****************************
// ----------  SPI Arduino configuration for spark fun SD shield ----------------------
//  CD   -  NA
//  DO   -  D12
//  GND  -  GND
//  SCK  -  D14
//  VCC  -  3.3V
//  DI   -  D11
//  CS   -  D10    
//-------------- Setup SPI configuration. (Particle) -------------------------------------------
#if SPI_CONFIGURATION == 0
// Primary SPI with DMA
// SCK => A3, MISO => A4, MOSI => A5, SS => A2 (default)
SdFat sd;
const uint8_t chipSelect = SS;
#elif SPI_CONFIGURATION == 1
// Secondary SPI with DMA
// SCK => D4, MISO => D3, MOSI => D2, SS => D1
SdFat sd(1);
const uint8_t chipSelect = D1;
#elif SPI_CONFIGURATION == 2
// Primary SPI with Arduino SPI library style byte I/O.
// SCK => A3, MISO => A4, MOSI => A5, SS => A2 (default)
SdFatLibSpi sd;
const uint8_t chipSelect = SS;
#elif SPI_CONFIGURATION == 3
// Software SPI.  Use any digital pins.
// MISO => D5, MOSI => D6, SCK => D7, SS => D0
SdFatSoftSpi<D5, D6, D7> sd;
const uint8_t chipSelect = D0;
#endif  // SPI_CONFIGURATION

// -------------- Initializers -----------------------------------------------------
FatFile FileA; // creating object called FileA to match class FatFile

//------------------ Functions --------------------------------------------------------------

// checkTrackers: Looks at the EEPROM memory to define trakers for ECG, activity, and temperature. Then increases all trackers by 1 and stores back to the EEPROM.
// This function was designed so it can be used at the begining of the program and prevent from subwritting files that already exist in the SD memory
void checkTrackers()
{
  byte ECG_1 = EEPROM.read(0); // Integer data are stored in the memory in two memory locations. This is becayse only a byte can be store per memory. 
  byte ECG_2 = EEPROM.read(1);
  int ECGTracker = word(ECG_1, ECG_2); // Combine both bytes and makes an integer
  ECGTracker++;
  EEPROM.write(0,highByte(ECGTracker)); // Updates the tracker
  EEPROM.write(1,lowByte(ECGTracker));
  byte accelerometer_1 = EEPROM.read(2);
  byte accelerometer_2 = EEPROM.read(3);
  int accelerometerTracker = word (accelerometer_1, accelerometer_2);
  accelerometerTracker++;
  EEPROM.write(2,highByte(accelerometerTracker));
  EEPROM.write(3,lowByte(accelerometerTracker));
  byte temp_1 = EEPROM.read(4);
  byte temp_2 = EEPROM.read(5);
  int tempTracker = word (temp_1, temp_2);
  tempTracker++;
  EEPROM.write(4,highByte(tempTracker));
  EEPROM.write(5,lowByte(tempTracker));
}

// writeSDMemory: This function receives Name ("ECG", "accelerometer", "temp") and data that wants to be stored. Read EEPROM to define file tracker and stores data in the SD memory
// This functin will be run every time that data needs to be stored in the SD memory
void writeSDMemory(String Name, String Data)
{
    int highMemory;
    int lowMemory;
    if (Name == "ECG")
    {
      highMemory = 0;
      lowMemory = 1;
    }
    else if (Name == "activity")
    {
      highMemory = 2;
      lowMemory = 3;
    }
    else if (Name == "temp")
    {
      highMemory = 4;
      lowMemory = 5; 
    }

    // Assigning tracker and names
    byte high = EEPROM.read(highMemory); // Integer data are stored in the memory in two memory locations. This is becayse only a byte can be store per memory. 
    byte low = EEPROM.read(lowMemory);
    int FileNameTracker = word(high,low);
    String FileName = Name + String(FileNameTracker) + ".txt"; // A string with the name of the field
    char *FileNameChar = FileName.c_str(); // converts string into chart. FileFat arduini library requires chart
    char *DataChar = Data.c_str();
    
    //Storing in the SD memory
    FileA.open(FileNameChar, O_RDWR | O_CREAT | O_AT_END); // open file with name "FileName"
    FileA.write(DataChar); // write data to SD card
    FileA.close(); // don't forget to close the file, otherwise you run the risk of corrupting the file and card. 
    
    // Checking file size
    if (FileA.fileSize() > 1000000) // if the text file exceeds 1MB, on to the next one
    {
        FileNameTracker++; // increase tracker so data is stored in new file
        EEPROM.write(highMemory,highByte(FileNameTracker));
        EEPROM.write(lowMemory,lowByte(FileNameTracker));
    }
}   

// createData: this function was created for practiacal uses in testing and debuggin. It will not be used in the actual code.
String createData()
{
  String Data;
  int count  = 0; // This will not be needed in the final code
  do // create a big string for testing. This will not be needed in the final code.
  {
    count++;
    Data += "Alexan" + String(count) + "\n"; 
   } while(Data.length() < 350); // Seems that max size of string arduino can handle is about 350 bytes.
   return Data;
}


//-----------------------------------------------
String DataA = createData();

void setup() {
     Serial.begin(9600); // For debugging
     sd.begin(chipSelect, SPI_FULL_SPEED); // init at full speed for best performance
     checkTrackers(); // Check file tracker for ECG, temp, and activity.
     String DataA = createData();
}

void loop() {
  writeSDMemory("activity", DataA);
  writeSDMemory("ECG", DataA);
  writeSDMemory("temp", DataA);
  delay(2);
}


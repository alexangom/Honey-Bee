// Checking GitHub

#include "Timer.h" // This if for Arduino, don't need this for particles since is already included.
#include <SdFat.h> // This is the Sd library

// Pick an SPI configuration.
// See SPI configuration section below (comments are for photon).
#define SPI_CONFIGURATION  0
// ******************** I thing Aswhin used configuration 1. Need to confirm this *****************************
//  Arduino configuration for spark fun SD shield
//  CD   -  NA
//  DO   -  D12
//  GND  -  GND
//  SCK  -  D14
//  VCC  -  3.3V
//  DI   -  D11
//  CS   -  D10    
//------------------------------------------------------------------------------
// Setup SPI configuration.
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
//------------------------------------------------------------------------------

// Initializers
FatFile FileA; // creating object called FileA to match class FatFile
//String FileName;
int FileNameTracker = 1;
//--------------------------------------------------------------------------------

void writeSDMemory(String Name, String Data)
{
    // Need to do this just at the begginign of the program otherwhise is going to cause problems
    
    //String FileName = Name + String(FileNameTracker) + ".txt";
    bool CheckFile = true;
    do{
      String FileName = Name + String(FileNameTracker) + ".txt";
      char *FileNameChar = FileName.c_str();
      CheckFile = FileA.exists(FileNameChar);
      if (CheckFile == true)
      {
        FileNameTracker++;
      }
    } while (CheckFile == true);
    
    
    //Serial.print(Data);
    Serial.println(FileNameTracker);
    //String FileName = Name + String(FileNameTracker) + ".txt"; // A string with the name of the field
    char *FileNameChar = FileName.c_str();
    char *DataChar = Data.c_str();
    
    bool CheckFile = FileA.exists(FileNameChar);
    FileA.open(FileNameChar, O_RDWR | O_CREAT | O_AT_END); // open file with name "FileName"
    FileA.write(DataChar); // write data to SD card
    FileA.close(); // don't forget to close the file, otherwise you run the risk of corrupting the file and card. 
    
    // Checking file size
    if (FileA.fileSize() > 1000000) // if the accel file exceeds 1MB, on to the next one
    {
        FileNameTracker++; // increase tracker so data is stored in new file
    }
}   

//--------------------------------------------
String DataA;
String DataB = "Alexan,Gomez,Casarez";
int count  = 0;

//Timer StoreData; // Object for class Timer
//-----------------------------------------------
void setup() {
     Serial.begin(9600);
     sd.begin(chipSelect, SPI_FULL_SPEED); // init at full speed for best performance
     do
    {
      count++;
      DataA += "Alexan" + String(count) + "\n"; 
    } while(DataA.length() < 350); // Seems that max size of string arduino can handle is about 350 bytes.
     //StoreData.every(2000, writeSDMemory("alexan", "Alexan Gomez Casarez\n")); // // store data every 10s
}

void loop() {
  //StoreData.update();
  //serialPrint();
  //Serial.println("writting");
  //Serial.println(DataA);
  writeSDMemory("alexan", DataA);
  delay(2);
}

//---------------------------------------------------------------------------------

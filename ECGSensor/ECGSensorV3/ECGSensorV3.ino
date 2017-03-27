// ECG initializers
String EKGData;
int stringCheck = 0;
long tECG;
int EKG;
double EKGVolt;
int eraseEKG = 0;

int checkEKG() {
  if (eraseEKG == 1){ // this check if string was already stored in ECG
    EKGData = ""; // erase data in the string
    stringCheck = 0;
    eraseEKG = 0;
  }
  
  EKG = analogRead(2); // read analog input
  //tECG = micros();
  EKGVolt = EKG * 0.004887586; // conver the analog input into voltage value
  EKGData += String(EKGVolt); // stores values in a string
  
  // maximum String length is 622 bytes. Let's just be safe and say 616. 
  if (EKGData.length() <= 616) { 
    stringCheck = 0;
    EKGData += "\n"; // go to the next line
  }
  else
  {
    stringCheck = 1; // when string is full so data is stored in the SD memory
  }
  return stringCheck;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkEKG();
  delay(1000);
}

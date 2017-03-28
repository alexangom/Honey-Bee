//------------------- temp ---------------------------------
// temperature initializers
long tTemp;
int temperature;
int thermistorResistance;
double thermistorVoltage;
int thermistorAnalog;
String tempData;
int flag_temp = 0;
  
int checkTemp() {
  thermistorAnalog = analogRead(A1); // read the raw thermistor analog data
  tTemp = millis(); // store time after the analog read
  thermistorVoltage = thermistorAnalog * 0.000805664; // convert the analog to voltage
  if (thermistorAnalog < 4095) { 
    int R1 = 10000;
    thermistorResistance = (3.3)*(10000/thermistorVoltage) - 10000; // calculates the thermoresisotr resistance
    temperature = pow((.0011106 + 0.00023724*log(thermistorResistance) + 0.000000074738*pow(log(thermistorResistance), 3)), -1) - 273.15; // calculate temp in celcious
  }
  else if (thermistorAnalog >= 4095) {
    // if A5 reads 4095, then there is a short and/or the thermistor has failed
    thermistorResistance = 0;
    temperature = 0;
  }
  tempData = String(temperature) + " " + String(tTemp) + "\n"; // Make data into a single string
  flag_temp = 1; // return 1 when the funciton is finished
  return flag_temp;
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

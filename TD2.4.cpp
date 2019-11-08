#include <Arduino.h>
#include <Wire.h>



int temperatureLSB;
int temperatureMSB;
int humidityLSB;
int humidityMSB;

void showtemperature(double temperature){
  temperature=(( temperature/65536)*165)-40;
  Serial.print("température =");
  Serial.print(temperature);
  Serial.println(" °C");
}

void showhumidite(double humidity){
  humidity=(humidity/65536)*100;
  Serial.print("humidity =");
  Serial.print(humidity);
  Serial.println(" %");
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x40);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(15);// configuration

}

void loop() {
  Serial.println("la température");
  Wire.beginTransmission(0x40);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(15);
  Wire.requestFrom(0x40,2);
  if(Wire.available()){
    temperatureMSB = Wire.read();
    temperatureLSB = Wire.read();
    //Serial.print(temperatureMSB,HEX);
    //Serial.print(temperatureLSB,HEX);
    //Serial.println("");
    showtemperature((temperatureMSB<<8)|temperatureLSB);
  }

  Serial.println("la humidité");
  Wire.beginTransmission(0x40);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(15);
  Wire.requestFrom(0x40,2);
  if(Wire.available()){
    humidityMSB = Wire.read();
    humidityLSB = Wire.read();
    //Serial.print(humidityMSB,HEX);
    //Serial.print(humidityLSB,HEX);
    //Serial.println();
    showhumidite((humidityMSB<<8)|humidityLSB);
  }
  delay(4000);
  Serial.println("fin");
}

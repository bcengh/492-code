#include<Wire.h>
#include "wiring_private.h"; //pinPeripheral() function
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int address = 104;
TwoWire wire2(&sercom1, 11, 13);

int startWire(){

 int out = 0;
  
   Serial.begin(9600);
   Serial1.begin(9600);
   while (!Serial) ;
  // put your setup code here, to run once:
  Wire.begin();
  //code from I2Csetup
  Wire.beginTransmission(address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write((byte) 0);     // set to zero (wakes up the MPU-6050)
  out += Wire.endTransmission(true);
  
  Wire.beginTransmission(address);
  Wire.write(0x1C);  // Accel config register
  Wire.write(0x08);     // Setting range to +-4G
  out += Wire.endTransmission(true);
  
  Wire.beginTransmission(address);
  Wire.write(0x1B);  // Gyro config register
  Wire.write(0x08);     // setting range to +-500 degrees per second
  out += Wire.endTransmission(true);

 Wire.beginTransmission(address + 1);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write((byte) 0);     // set to zero (wakes up the MPU-6050)
  out += Wire.endTransmission(true);
  
  Wire.beginTransmission(address + 1);
  Wire.write(0x1C);  // Accel config register
  Wire.write(0x08);     // Setting range to +-4G
  out += Wire.endTransmission(true);
  
  Wire.beginTransmission(address + 1);
  Wire.write(0x1B);  // Gyro config register
  Wire.write(0x08);     // setting range to +-500 degrees per second
  out += Wire.endTransmission(true);

//--------------  second wire ---------------------

  //Serial.begin(9600);
   wire2.begin(9600);
   while (!Serial) ;
  // put your setup code here, to run once:
  wire2.begin();
  //code from I2Csetup
  wire2.beginTransmission(address);
  wire2.write(0x6B);  // PWR_MGMT_1 register
  wire2.write((byte) 0);     // set to zero (wakes up the MPU-6050)
  out += wire2.endTransmission(true);
  
  wire2.beginTransmission(address);
  wire2.write(0x1C);  // Accel config register
  wire2.write(0x08);     // Setting range to +-4G
  out += wire2.endTransmission(true);
  
  wire2.beginTransmission(address);
  wire2.write(0x1B);  // Gyro config register
  wire2.write(0x08);     // setting range to +-500 degrees per second
  out += wire2.endTransmission(true);

 wire2.beginTransmission(address + 1);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write((byte) 0);     // set to zero (wakes up the MPU-6050)
  out += wire2.endTransmission(true);
  
  wire2.beginTransmission(address + 1);
  wire2.write(0x1C);  // Accel config register
  wire2.write(0x08);     // Setting range to +-4G
  out += wire2.endTransmission(true);
  
  wire2.beginTransmission(address + 1);
  wire2.write(0x1B);  // Gyro config register
  wire2.write(0x08);     // setting range to +-500 degrees per second
  out += wire2.endTransmission(true);
}

int readDataW1(int sensor){
  //code inside of I2CPrint
  Wire.beginTransmission(address);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);                     //int debug = for these two lines
  Wire.requestFrom(address,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  int value = 0;
  value = analogRead(A2);

  Serial.print("EMG = "); Serial.print(value);
  //Serial.print("Debug = "); Serial.print(debug);
  //Serial.print(" | Debug2 = "); Serial.print(debug2);
  Serial.print(" | AcX = "); Serial.print((AcX/8192.0)* 90.0);
  Serial.print(" | AcY = "); Serial.print((AcY/8192.0) * 90.0);
  Serial.print(" | AcZ = "); Serial.print((AcZ/8192.0) * 90.0);
  Serial.print(" | Tmp = "); Serial.print((Tmp/340.00+36.53)*9/5 + 32);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX/65.5);
  Serial.print(" | GyY = "); Serial.print(GyY/65.5);
  Serial.print(" | GyZ = "); Serial.print(GyZ/65.5);
  Serial.println(";");

}


int readDataW2(int sensor){
  //code inside of I2CPrint
  wire2.beginTransmission(address);
  wire2.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  wire2.endTransmission(false);                     //int debug = for these two lines
  wire2.requestFrom(address,14,true);  // request a total of 14 registers
  AcX=wire2.read()<<8|wire2.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=wire2.read()<<8|wire2.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=wire2.read()<<8|wire2.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=wire2.read()<<8|wire2.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=wire2.read()<<8|wire2.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=wire2.read()<<8|wire2.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=wire2.read()<<8|wire2.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  int value = 0;
  value = analogRead(A2);

  Serial.print("EMG = "); Serial.print(value);
  //Serial.print("Debug = "); Serial.print(debug);
  //Serial.print(" | Debug2 = "); Serial.print(debug2);
  Serial.print(" | AcX = "); Serial.print((AcX/8192.0)* 90.0);
  Serial.print(" | AcY = "); Serial.print((AcY/8192.0) * 90.0);
  Serial.print(" | AcZ = "); Serial.print((AcZ/8192.0) * 90.0);
  Serial.print(" | Tmp = "); Serial.print((Tmp/340.00+36.53)*9/5 + 32);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX/65.5);
  Serial.print(" | GyY = "); Serial.print(GyY/65.5);
  Serial.print(" | GyZ = "); Serial.print(GyZ/65.5);
  Serial.println(";");

}
   
void setup() {

  pinPeripheral(11, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);
  
   Serial.println(startWire());
   
  /*Serial.print(" | Debug3 = "); Serial.print(debug3);
  Serial.print(" | Debug4 = "); Serial.print(debug4);
  Serial.print(" | Debug5 = "); Serial.print(debug5);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("IMU1 : ");
  readDataW1(address);
  Serial.print("IMU2 : ");
  readDataW1(address+1);

  Serial.println("Wire 2");
  
  Serial.print("IMU1 : ");
  readDataW2(address);
  Serial.print("IMU2 : ");
  readDataW2(address);

  Serial.println();
  Serial.println();
  delay(220);

}

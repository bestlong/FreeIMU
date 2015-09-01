/**
 * FreeIMU - Raw Data Logger
 * 
 * https://github.com/bestlong/FreeIMU
 * 
 * 將 Raw data 儲存到 SD 卡與輸出到串列埠埠 
 * 總共有 12 個欄位，依序是 millis, ax, ay, az, gx, gy, gz, mx, my, mz, temp, press
 */

#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <SD.h>

#include <I2Cdev.h>
#include <MPU60X0.h>
#include <HMC58X3.h>
#include <MS561101BA.h>

//#define DEBUG
#include "DebugUtils.h"
#include "FreeIMU.h"

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 4;

unsigned long time;
int raw_values[11];
FreeIMU my3IMU = FreeIMU();
File logFile;

void setup() {
  Serial.begin(115200);

  Wire.begin();
  my3IMU.init(true);

  // SD
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // LED
  pinMode(13, OUTPUT);
}

void loop() {
  time = millis();
  // ax, ay, az, gx, gy, gz, mx, my, mz, temp, press
  my3IMU.getRawValues(raw_values);
  if (Serial) {
    Serial.print(time);
    Serial.print(",");
    Serial.print(raw_values[0]);  Serial.print(",");
    Serial.print(raw_values[1]);  Serial.print(",");
    Serial.print(raw_values[2]);  Serial.print(",");
    Serial.print(raw_values[3]);  Serial.print(",");
    Serial.print(raw_values[4]);  Serial.print(",");
    Serial.print(raw_values[5]);  Serial.print(",");
    Serial.print(raw_values[6]);  Serial.print(",");
    Serial.print(raw_values[7]);  Serial.print(",");
    Serial.print(raw_values[8]);  Serial.print(",");
    Serial.print(raw_values[9]);  Serial.print(",");
    Serial.print(raw_values[10]);
    Serial.println("");
  }

  logFile = SD.open("RAWDATA.LOG", FILE_WRITE);
  if (logFile) {
    logFile.print(time);
    logFile.print(",");
    logFile.print(raw_values[0]);  logFile.print(",");
    logFile.print(raw_values[1]);  logFile.print(",");
    logFile.print(raw_values[2]);  logFile.print(",");
    logFile.print(raw_values[3]);  logFile.print(",");
    logFile.print(raw_values[4]);  logFile.print(",");
    logFile.print(raw_values[5]);  logFile.print(",");
    logFile.print(raw_values[6]);  logFile.print(",");
    logFile.print(raw_values[7]);  logFile.print(",");
    logFile.print(raw_values[8]);  logFile.print(",");
    logFile.print(raw_values[9]);  logFile.print(",");
    logFile.print(raw_values[10]);
    logFile.println("");
    logFile.close();
  }
}


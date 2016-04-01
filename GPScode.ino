/*
 This example uses software serial and the TinyGPS++ library by Mikal Hart
 Based on TinyGPSPlus/DeviceExample.ino by Mikal Hart
 Modified by acavis and 2016 Winter Ocean Sensing Class
*/

// import libraries
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

//create file
File myFile;

//file name
#define fileName "gpsTwo.txt"


// Choose two Arduino pins to use for software serial
// The GPS Shield uses D2 and D3 by default when in DLINE mode
int RXPin = 2;
int TXPin = 3;

// The Skytaq EM-506 GPS module included in the GPS Shield Kit
// uses 4800 baud by default
int GPSBaud = 4800;

// Create a TinyGPS++ object called "gps"
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);




void setup() {
     // Start the Arduino hardware serial port at 9600 baud
     Serial.begin(9600);
     while (!Serial) {
          ;
     }

     // Start the software serial port at the GPS's default baud
     gpsSerial.begin(GPSBaud);
     Serial.println(F("DeviceExample.ino"));
     Serial.println(F("A simple demonstration of TinyGPS++ 
               with an attached GPS module"));
     Serial.print(F("Testing TinyGPS++ library v. ")); 
     Serial.println(TinyGPSPlus::libraryVersion());
     Serial.println(F("originally by Mikal Hart and adapted 
               by the 2016 Winter Ocean Sensing Class"));
     Serial.println();

     // Start initilization of of SD card
     Serial.print("Initializing SD card...");
     if (!SD.begin(4)) {
          Serial.println("initialization failed!");
          return;
     }
     Serial.println("initialization done.");
     Serial.println();
}





void loop() {
// This sketch displays information every time a new sentence 
// is correctly encoded.
     while (gpsSerial.available() > 0) {
          if (gps.encode(gpsSerial.read())) {
               displayInfo();
               printInfo();
               delay(1000);
          }
     }
     // If 5000 milliseconds pass and there are no characters coming in
     // over the software serial port, show a "No GPS detected" error
     if (millis() > 5000 && gps.charsProcessed() < 10) {
     Serial.println(F("No GPS detected"));
     }
}




// method to display the information on the serial monotor
void displayInfo() {
     // get and print location
     Serial.print(F("Location: ")); 
     if (gps.location.isValid()) {
          Serial.print(gps.location.lng(), 6);
          Serial.print(F(", "));
          Serial.print(gps.location.lat(), 6);
     } else {
          Serial.print(F("INVALID"));
     }

     // get and print altitude in meters
     Serial.print(F(" Altitude(m): "));
     if (gps.altitude.isValid()) {
          Serial.print(gps.altitude.meters(), 2);
     } else {
          Serial.print(F("INVALID"));
     }

     // get and print date
     Serial.print(F("  Date/Time: "));
     if (gps.date.isValid()) {
          Serial.print(gps.date.month());
          Serial.print(F("/"));
          Serial.print(gps.date.day());
          Serial.print(F("/"));
          Serial.print(gps.date.year());
     } else {
          Serial.print(F("INVALID"));
     }

     // get and print time
     Serial.print(F(" "));
     if (gps.time.isValid()) {
          if (gps.time.hour() < 10) {
               Serial.print(F("0"));
          }
          Serial.print(gps.time.hour());
          Serial.print(F(":"));
          if (gps.time.minute() < 10) {
               Serial.print(F("0"));
          }
          Serial.print(gps.time.minute());
          Serial.print(F(":"));
          if (gps.time.second() < 10) {
               Serial.print(F("0"));
          }
          Serial.print(gps.time.second());
          Serial.print(F("."));
          if (gps.time.centisecond() < 10) {
               Serial.print(F("0"));
          }
          Serial.print(gps.time.centisecond());
     } else {
          Serial.print(F("INVALID"));
     }

     Serial.println();
}


void printInfo() {
     // open file
     myFile = SD.open(fileName, FILE_WRITE); 

     // get and print location in file
     myFile.print(F("Location: "));
     if (gps.location.isValid()) {
          myFile.print(gps.location.lng(), 6);
          myFile.print(F(","));
          myFile.print(gps.location.lat(), 6);
     } else {
          myFile.print(F("INVALID"));
     }

     // get and print altitude in meters in file
     myFile.print(F(" Altitude(m): "));
     if (gps.altitude.isValid()) {
          myFile.print(gps.altitude.meters(), 2);
     } else {
          myFile.print(F("INVALID"));
     }

     // get and print date in file
     myFile.print(F("  Date/Time: "));
     if (gps.date.isValid()) {
          myFile.print(gps.date.month());
          myFile.print(F("/"));
          myFile.print(gps.date.day());
          myFile.print(F("/"));
          myFile.print(gps.date.year());
     } else {
     myFile.print(F("INVALID"));
     }

     // get and print time in file
     myFile.print(F(" "));
     if (gps.time.isValid()) {
          if (gps.time.hour() < 10) {
               myFile.print(F("0"));
          }
          myFile.print(gps.time.hour());
          myFile.print(F(":"));
          if (gps.time.minute() < 10) {
               myFile.print(F("0"));
          }
          myFile.print(gps.time.minute());
          myFile.print(F(":"));
          if (gps.time.second() < 10) {
               myFile.print(F("0"));
          }
          myFile.print(gps.time.second());
          myFile.print(F("."));
          if (gps.time.centisecond() < 10) {
               myFile.print(F("0"));
          }
          myFile.print(gps.time.centisecond());
     } else {
          myFile.print(F("INVALID"));
     }

     myFile.println();
     myFile.close(); // close file
}


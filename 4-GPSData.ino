#include <SoftwareSerial.h>
#include "TinyGPSPlus.h"
#include <math.h>

#define EARTH_RADIUS 6368.061

static const int RXPin = 4, TXPin = 3;                                      // RX-Pin(4) || TX-Pin(3)
static const uint32_t GPSBaud = 9600;                                       // GPS Baurate 9600

int lattitude, longtitude;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);                                                     // Main Baudrate
  ss.begin(GPSBaud);                                                        // GPS Baudrate

  Serial.println(F("Written by Emma\n"));
  Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
  Serial.print(F("TinyGPSPlus library version --->>> "));
  Serial.println(TinyGPSPlus::libraryVersion());


}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)                                                // While baudrate for GPS is available Process is continius
    if (gps.encode(ss.read()))                                              // If Arduino read data from GPS
      displayInfo();                                                        // Display data on Serial Monitor

  if (millis() > 5000 && gps.charsProcessed() < 10)                         // If GPS unavailable
  {
    Serial.println(F("No GPS detected: check wiring."));                    // Display "No GPS detected: check wiring." data to Serial Monitor
    while (true);                                                           // While GPS unavailable stay on this condition
  }
}


/*
  Here we display all data from GPS to Serial Monitor
  Data like Location lattitude and longitude
  And also use Date and Time for displaying Real-Time work
*/
void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())                                               // If LOCATION data from GPS available
  {
    Serial.print(gps.location.lat(), 6);                                    // Display location
    Serial.print("\t");                                                     // lattitude and longitude
    Serial.print(gps.location.lng(), 6);
    Serial.print("\t");

  }
  else
  {
    Serial.print(F("INVALID"));                                             // Else display "Location INVALID"
  }


  Serial.println();
}
